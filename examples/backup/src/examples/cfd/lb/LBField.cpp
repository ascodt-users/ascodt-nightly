#include "LBField.h"
#include "stencils/LBFunctions.h"

LBField::LBField(const Parameters & parameters):
_parameters(parameters),
_dim (parameters.geometry.dim),
_Q (_dim==2 ? Q2D : Q3D),
_Nx (parameters.coupling.set ? parameters.coupling.sizeNS[0] * parameters.coupling.ratio - 1 :
	parameters.parallel.localSize[0]),
_Ny (parameters.coupling.set ? parameters.coupling.sizeNS[1] * parameters.coupling.ratio - 1 :
	parameters.parallel.localSize[1]),
_Nz (_dim==2 ? 1 : (parameters.coupling.set ? parameters.coupling.sizeNS[2] *
	parameters.coupling.ratio - 1 :
	parameters.parallel.localSize[2])),
_cellsX (_Nx+2),
_cellsY (_Ny+2),
_cellsZ (_dim==2 ? 1 : _Nz+2),
_nofCellsWithBoundaries (_cellsX * _cellsY * _cellsZ),
_latticeVelocities (_dim == 2 ? latticeVelocities2D : latticeVelocities3D),
_latticeWeights (_dim == 2 ? latticeWeights2D : latticeWeights3D),
_fIn(NULL),
_fOut(NULL),
_flags(NULL)
{

}

void LBField::allocate(){
	_fIn =  new FLOAT[_Q * _nofCellsWithBoundaries];
	_fOut = new FLOAT[_Q * _nofCellsWithBoundaries];
	_flags = new char[_nofCellsWithBoundaries];

	// Here, the indexing function is used to initialize the array discarding any possibly faster
	// method. However, this function is called once, and this accounts for possible changes in
	// indexing and the layout of the arrays
	double dist=0.0;
	double dz=1.0/(double)_cellsZ;
	double dx=1.0/(double)_cellsX;
	double dy=1.0/(double)_cellsY;
	for (int k = 0; k < _cellsZ; k++){
		for (int j = 0; j < _cellsY; j++){
			for (int i = 0; i < _cellsX; i++){
				dist=((double)i*dx-0.5)*((double)i*dx-0.5)+
						((double)j*dy-0.5)*((double)j*dy-0.5)+
						((double)k*dz-0.5)*((double)k*dz-0.5);
//				if(dist<=0.15){
//
//					_flags[getIndexCell( i, j, k)]= 1;
//				}else
				if(isInside(i,j,k))
					_flags[getIndexCell( i, j, k)]= 1;
				else
					_flags[getIndexCell( i, j, k)]= 0;
				for (int a = 0; a < _Q; a++){
					_fIn[getIndexF(a, i, j, k)] = _latticeWeights[a];
					_fOut[getIndexF(a, i, j, k)] = _latticeWeights[a];

				}
			}
		}
	}
}

//LBField::LBField(int cellsX, int cellsY, int cellsZ):
//    						_dim (3),
//    						_Q (Q),
//    						_Nx (cellsX - 2),
//    						_Ny (cellsY - 2),
//    						_Nz (cellsZ - 2),
//    						_cellsX (cellsX),
//    						_cellsY (cellsY),
//    						_cellsZ (cellsZ),
//    						_nofCellsWithBoundaries (_cellsX * _cellsY * _cellsZ),
//    						_latticeVelocities (latticeVelocities3D),
//    						_latticeWeights (latticeWeights3D),
//    						_fIn(NULL),
//    						_fOut(NULL),
//    						_flags(NULL)
//{
//
//}

const bool LBField::isInside(int i,int j,int k) const{
	double dist=0.0;
	double pos[3];
//	if(	i==0||j==0||k==0||
//			i==_cellsX-1||j==_cellsY-1||k==_cellsZ-1)
//		return false;
	double dx=1.0/(double)(_parameters.coupling.sizeNS[0] * _parameters.coupling.ratio - 1);
	double dy=1.0/(double)(_parameters.coupling.sizeNS[1] * _parameters.coupling.ratio - 1);
	double dz=1.0/(double)(_parameters.coupling.sizeNS[2] * _parameters.coupling.ratio - 1);

	pos[0]= ((_parameters.parallel.firstCorner[0]+(i-1))
					*dx)+dx/2.0;

	pos[1]= ((_parameters.parallel.firstCorner[1]+(j-1))
					*dy)+dy/2.0;

	pos[2]= ((_parameters.parallel.firstCorner[2]+(k-1))
					*dz)+dz/2.0;
	for(unsigned int g_i=0;g_i<_geometries.size();g_i++){
		//_parameters.parallel.firstCorner*parameters.geometry.dx
		if(
			((-pos[0]+_geometries[g_i].x)*(-pos[0]+_geometries[g_i].x))+
			((-pos[1]+_geometries[g_i].y)*(-pos[1]+_geometries[g_i].y))+
			((-pos[2]+_geometries[g_i].z)*(-pos[2]+_geometries[g_i].z))<=_geometries[g_i].r*_geometries[g_i].r)
				return true;
	}
	return false;
}
const FLOAT LBField::getDensity (const FLOAT* const f, int i, int j, int k) const{
	FLOAT density = 0;
	for (int a = 0; a < _Q; a++){
		density += f[getIndexF(a, i, j, k)];
	}
	return density;
}

void LBField::getVelocity (const FLOAT density, FLOAT * const velocity, const FLOAT* const f, int i, int j, int k) const {

#ifdef D3Q19
	// Assume that the lattice velocities are indexed such that C_{i} = -C_{Q-i-1}, and C_{9} = 0,
	// then, rho * u = sum_1^Q f_i C_i = sum_1^8 (f_i - f_{Q-i-1}) C_i. There shouldn't be
	// ADDITIONAL conditioning problems, since this subtraction of close values is done anyway if
	// performing the complete sum. This should help performance a little.

	velocity[0] = (f[getIndexF(17, i, j, k)] - f[getIndexF(1, i, j, k)] +
			f[getIndexF(3, i, j, k)] - f[getIndexF(15, i, j, k)] +
			f[getIndexF(13, i, j, k)] - f[getIndexF(5, i, j, k)] +
			f[getIndexF(7, i, j, k)] - f[getIndexF(11, i, j, k)] +
			f[getIndexF(10, i, j, k)] - f[getIndexF(8, i, j, k)]) / density;

	velocity[1] = (f[getIndexF(18, i, j, k)] - f[getIndexF(0, i, j, k)] +
			f[getIndexF(4, i, j, k)] - f[getIndexF(14, i, j, k)] +
			f[getIndexF(13, i, j, k)] - f[getIndexF(5, i, j, k)] +
			f[getIndexF(12, i, j, k)] - f[getIndexF(6, i, j, k)] +
			f[getIndexF(11, i, j, k)] - f[getIndexF(7, i, j, k)]) / density;

	velocity[2] = (f[getIndexF(18, i, j, k)] - f[getIndexF(0, i, j, k)] +
			f[getIndexF(17, i, j, k)] - f[getIndexF(1, i, j, k)] +
			f[getIndexF(16, i, j, k)] - f[getIndexF(2, i, j, k)] +
			f[getIndexF(15, i, j, k)] - f[getIndexF(3, i, j, k)] +
			f[getIndexF(14, i, j, k)] - f[getIndexF(4, i, j, k)]) / density;

	// All these modifications make harder to select 2D or 3D mode without using macros.
#endif

#if (defined (D3Q15)) or (defined (D3Q27))  // All the sets that don't have an optimization
	velocity[0] = 0.0;
	velocity[1] = 0.0;
	velocity[2] = 0.0;
	for (int l = 0; l < _Q; l++){
		velocity[0] += _latticeVelocities[l][0] * f[getIndexF(l, i, j, k)];
		velocity[1] += _latticeVelocities[l][1] * f[getIndexF(l, i, j, k)];
		velocity[2] += _latticeVelocities[l][2] * f[getIndexF(l, i, j, k)];
	}
	velocity[0] /= density;
	velocity[1] /= density;
	velocity[2] /= density;
#endif
}

void LBField::getVelocityComponent (const FLOAT density, FLOAT & velocity, const FLOAT* const f, int i, int j, int k,int component) const {

#ifdef D3Q19
	// Assume that the lattice velocities are indexed such that C_{i} = -C_{Q-i-1}, and C_{9} = 0,
	// then, rho * u = sum_1^Q f_i C_i = sum_1^8 (f_i - f_{Q-i-1}) C_i. There shouldn't be
	// ADDITIONAL conditioning problems, since this subtraction of close values is done anyway if
	// performing the complete sum. This should help performance a little.
   if(component==0)
	velocity = (f[getIndexF(17, i, j, k)] - f[getIndexF(1, i, j, k)] +
			f[getIndexF(3, i, j, k)] - f[getIndexF(15, i, j, k)] +
			f[getIndexF(13, i, j, k)] - f[getIndexF(5, i, j, k)] +
			f[getIndexF(7, i, j, k)] - f[getIndexF(11, i, j, k)] +
			f[getIndexF(10, i, j, k)] - f[getIndexF(8, i, j, k)]) / density;
   else if(component==1)
	velocity = (f[getIndexF(18, i, j, k)] - f[getIndexF(0, i, j, k)] +
			f[getIndexF(4, i, j, k)] - f[getIndexF(14, i, j, k)] +
			f[getIndexF(13, i, j, k)] - f[getIndexF(5, i, j, k)] +
			f[getIndexF(12, i, j, k)] - f[getIndexF(6, i, j, k)] +
			f[getIndexF(11, i, j, k)] - f[getIndexF(7, i, j, k)]) / density;
   else
	velocity = (f[getIndexF(18, i, j, k)] - f[getIndexF(0, i, j, k)] +
			f[getIndexF(17, i, j, k)] - f[getIndexF(1, i, j, k)] +
			f[getIndexF(16, i, j, k)] - f[getIndexF(2, i, j, k)] +
			f[getIndexF(15, i, j, k)] - f[getIndexF(3, i, j, k)] +
			f[getIndexF(14, i, j, k)] - f[getIndexF(4, i, j, k)]) / density;

	// All these modifications make harder to select 2D or 3D mode without using macros.
#endif
/*
#if (defined (D3Q15)) or (defined (D3Q27))  // All the sets that don't have an optimization
	velocity[0] = 0.0;
	velocity[1] = 0.0;
	velocity[2] = 0.0;
	for (int l = 0; l < _Q; l++){
		velocity[0] += _latticeVelocities[l][0] * f[getIndexF(l, i, j, k)];
		velocity[1] += _latticeVelocities[l][1] * f[getIndexF(l, i, j, k)];
		velocity[2] += _latticeVelocities[l][2] * f[getIndexF(l, i, j, k)];
	}
	velocity[0] /= density;
	velocity[1] /= density;
	velocity[2] /= density;
#endif
*/
}


void LBField::getPressureAndVelocity(FLOAT & pressure, FLOAT* const velocity, int i, int j) const {
	pressure = getDensity(_fOut, i, j);
	getVelocity(pressure, velocity, _fOut, i, j);
}

void LBField::getPressureAndVelocity(FLOAT & pressure, FLOAT* const velocity, int i, int j, int k) const {

#ifdef D3Q19    // In this case, use the optimized version
	// Load the distribution for the cell
	FLOAT f[Q];
	for (int a = 0; a < _Q; a++){
		f[a] = _fOut[getIndexF(a, i, j, k)];
	}

	// These are parts for the computation of the velocity, but will also be used for computation
	// of the pressure to reduce the number of operations. At the end, velocity is found as linear
	// combinations of the distributions with coefficients 1 or -1, so we can add up all the
	// positive and negative parts.

	const FLOAT x_add = f[3] + f[7] + f[10] + f[13] + f[17];
	const FLOAT x_sub = f[1] + f[5] + f[8] + f[11] + f[15];

	const FLOAT z_add = f[14] + f[15] + f[16] + f[17] + f[18];
	const FLOAT z_sub = f[0] + f[1] + f[2] + f[3] + f[4];

	FLOAT y_add = f[11] + f[12] + f[13];
	FLOAT y_sub = f[5] + f[6] + f[7];

	// The name PRESSURE is bad, but it helps to mantain consistent names between methods
	pressure = f[8] + f[9] + f[10] + y_add + y_sub + z_add + z_sub;

	y_add += f[4] + f[18];
	y_sub += f[0] + f[14];

	velocity[0] = (x_add - x_sub) / pressure;
	velocity[1] = (y_add - y_sub) / pressure;
	velocity[2] = (z_add - z_sub) / pressure;
#endif

#if (defined (D3Q15)) or (defined (D3Q27))
	pressure = getDensity(_fOut, i, j, k);
	getVelocity(pressure, velocity, _fOut, i, j, k);
#endif
}


void LBField::getSecondMoment (FLOAT * const moment, int i, int j, int k) const {
	FLOAT feq[_Q];
	FLOAT fneq[_Q];
	FLOAT velocity[3];
	FLOAT density;

	getPressureAndVelocity (density, velocity, i, j, k);

	computeEquilibrium (feq, density, velocity);
	for (int a = 0; a < _Q; a++){
		fneq[a] = _fOut[getIndexF(a, i, j, k)] - feq[a];
	}

	for (int a = 0; a < 6; a++){
		moment[a] = 0.0;
	}

	for (int a = 0; a < _Q; a++){
		moment[0] += fneq[a] * _latticeVelocities[a][0] * _latticeVelocities[a][0];
		moment[1] += fneq[a] * _latticeVelocities[a][0] * _latticeVelocities[a][1];
		moment[2] += fneq[a] * _latticeVelocities[a][1] * _latticeVelocities[a][1];
		moment[3] += fneq[a] * _latticeVelocities[a][0] * _latticeVelocities[a][2];
		moment[4] += fneq[a] * _latticeVelocities[a][1] * _latticeVelocities[a][2];
		moment[5] += fneq[a] * _latticeVelocities[a][2] * _latticeVelocities[a][2];
	}
}


LBField::~LBField(){
	if(_fIn)
		delete[] _fIn;
	if(_fIn)
		delete[] _fOut;
	if(_flags)
		delete[] _flags;
}

const int LBField::getNx() const{
	return _Nx;
}

const int LBField::getNy() const{
	return _Ny;
}

const int LBField::getNz() const{
	return _Nz;
}

const int LBField::getCellsX() const{
	return _cellsX;
}

const int LBField::getCellsY() const{
	return _cellsY;
}

const int LBField::getCellsZ() const{
	return _cellsZ;
}

const int LBField::getQ() const {
	return _Q;
}

const int LBField::getIndexCell(int i, int j, int k) const {
	return getIndexF(0, i, j, k);
}
void LBField::registerSphere(double x,double y,double z,double r){
	Sphere s;
	s.x=x;
	s.y=y;
	s.z=z;
	s.r=r;
	std::cout<<"sphere reg:"<<x<<","<<y<<","<<z<<std::endl;
	_geometries.push_back(s);
}

void LBField::swap(){
	FLOAT * swap;
	swap = _fIn;
	_fIn = _fOut;
	_fOut = swap;
}
