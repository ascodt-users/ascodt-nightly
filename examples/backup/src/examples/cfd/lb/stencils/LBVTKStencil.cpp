#include "LBVTKStencil.h"

// TODO Correct performance issues for big matrices still required

void writeVTKHeader ( std::ostream & file, const LBField & field ) {

	file << "# vtk DataFile Version 2.0" << std::endl
			<< "I need something to put here" << std::endl
			<< "ASCII" << std::endl << std::endl;
}


void writePoints (std::ostream & file, const LBField & field,
		const Parameters & parameters){

	// Number of points in every direction
	int px = field.getNx() + 1;
	int py = field.getNy() + 1;
	int pz = field.getDim()==2 ? 1 : field.getNz() + 1;
	// int px = field.getNx() + 1;
	// int py = field.getNy() + 1;
	// int pz = field.getDim()==2 ? 1 : field.getNz() + 1;

	std::string grid;
	char buffer[256];

	grid.reserve ( ( file.precision() + 6 ) * px * py * pz * 3 );

	sprintf ( buffer, "DATASET STRUCTURED_GRID\nDIMENSIONS %d %d %d\nPOINTS %d float\n",
			px, py, pz, px * py * pz);
	grid.append ( buffer );
	int count=0;
//	double dx=1.0/(_parameters.coupling.sizeNS[0] * _parameters.coupling.ratio - 1);
//	double dy=1.0/(_parameters.coupling.sizeNS[1] * _parameters.coupling.ratio - 1);
//	double dz=1.0/(_parameters.coupling.sizeNS[2] * _parameters.coupling.ratio - 1);

	for ( int k = parameters.parallel.firstCorner[2]; k < parameters.parallel.firstCorner[2]+ pz; k++ ){
		for ( int j = parameters.parallel.firstCorner[1]; j < parameters.parallel.firstCorner[1] + py; j++ ){
			for ( int i = parameters.parallel.firstCorner[0]; i < parameters.parallel.firstCorner[0] + px; i++ ){
				sprintf (buffer, "%f %f %f\n", i * parameters.geometry.dx/(double)parameters.coupling.ratio,
						j * parameters.geometry.dy/(double)parameters.coupling.ratio,
						k * parameters.geometry.dz/(double)parameters.coupling.ratio);
				grid.append ( buffer );
				count++;
			}
		}
	}
	grid.append ("\n");
	std::cout<<"points:"<<count<<""<<std::endl;
	count=0;
	file << grid;
}


LBVTKStencil::LBVTKStencil (const Parameters & parameters) :
    		FieldStencil<LBField> ( parameters ), _prefix(parameters.vtk.prefix), _written(false) {

	//    _prefix = parameters.vtk.prefix;
	//    _written = false;
	count=0;
}


void LBVTKStencil::apply ( LBField & field, int i, int j ) {

	assertion ( field.getDim() == 2 );

	const FLOAT density = field.getDensity(field.getFOut(), i, j);
	field.getVelocity(density, _velocity, field.getFOut(), i, j);

	pressureStream << density << std::endl;

	velocityStream << _velocity[0] << " "
			<< _velocity[1] << " "
			<< 0 << std::endl;

}


void LBVTKStencil::apply ( LBField & field, int i, int j, int k ) {

	assertion ( field.getDim() == 3 );

	const FLOAT density = field.getDensity(field.getFOut(), i, j, k);
	field.getVelocity(density, _velocity, field.getFOut(), i, j, k);
	count++;
	pressureStream << density << std::endl;

	velocityStream << _velocity[0] << " "
			<< _velocity[1] << " "
			<< _velocity[2] << std::endl;

	field.getSecondMoment (_secondMoment, i, j, k);

	xxStream << _secondMoment[0] << std::endl;
	xyStream << _secondMoment[1] << std::endl;
	yyStream << _secondMoment[2] << std::endl;
	xzStream << _secondMoment[3] << std::endl;
	yzStream << _secondMoment[4] << std::endl;
	zzStream << _secondMoment[5] << std::endl;
}


void LBVTKStencil::openFile ( const LBField & field, FLOAT time ){

	// This relates to openning the file with the correct name
	_written = false;
	std::stringstream namestream;
	std::string name;
	namestream.precision (4);
	namestream << _prefix << "." << _parameters.parallel.rank << "." << time << ".vtk";
	name = namestream.str ();
	_ofile.open ( name.c_str() );
	namestream.str("");

	writeVTKHeader ( _ofile, field );

	writePoints ( _ofile, field, _parameters );
}


void LBVTKStencil::write ( LBField & field ){

	if (field.getDim() == 2){
		// Write pressure
		_ofile << "CELL_DATA " << field.getNx() * field.getNy() << std::endl
				<< "SCALARS density float 1" << std::endl
				<< "LOOKUP_TABLE default" << std::endl;
		_ofile << pressureStream.str() << std::endl;
		pressureStream.str("");

		// Write velocity
		// _ofile << "CELL_DATA " << field.getNx() * field.getNy() << std::endl
		_ofile << "VECTORS velocity float" << std::endl;
		_ofile << velocityStream.str() << std::endl;
		velocityStream.str("");
	}

	if (field.getDim() == 3){
		// Write pressure
		// _ofile << "CELL_DATA " << field.getNx() * field.getNy() * field.getNz()
		_ofile << "CELL_DATA " << (field.getNx()) * (field.getNy()) * (field.getNz())
            		<< std::endl
            		<< "SCALARS density float 1" << std::endl
            		<< "LOOKUP_TABLE default" << std::endl;
		_ofile << pressureStream.str() << std::endl;
		pressureStream.str("");

		// Write velocity
		_ofile << "VECTORS velocity float" << std::endl;
		_ofile << velocityStream.str() << std::endl;
		velocityStream.str("");

		_ofile << "SCALARS Mxx float 1" << std::endl
				<< "LOOKUP_TABLE default" << std::endl;
		_ofile << xxStream.str() << std::endl;
		xxStream.str("");

		_ofile << "SCALARS Mxy float 1" << std::endl
				<< "LOOKUP_TABLE default" << std::endl;
		_ofile << xyStream.str() << std::endl;
		xyStream.str("");

		_ofile << "SCALARS Myy float 1" << std::endl
				<< "LOOKUP_TABLE default" << std::endl;
		_ofile << yyStream.str() << std::endl;
		yyStream.str("");

		_ofile << "SCALARS Mxz float 1" << std::endl
				<< "LOOKUP_TABLE default" << std::endl;
		_ofile << xzStream.str() << std::endl;
		xzStream.str("");

		_ofile << "SCALARS Myz float 1" << std::endl
				<< "LOOKUP_TABLE default" << std::endl;
		_ofile << yzStream.str() << std::endl;
		yzStream.str("");

		_ofile << "SCALARS Mzz float 1" << std::endl
				<< "LOOKUP_TABLE default" << std::endl;
		_ofile << zzStream.str() << std::endl;
		zzStream.str("");
	}
	std::cout<<"cnt:"<<count<<std::endl;
	_written = true;
}


void LBVTKStencil::closeFile () {
	_ofile. close ();
}

void LBVTKStencil::setPrefix (const std::string prefix){
	_prefix = prefix;
}
