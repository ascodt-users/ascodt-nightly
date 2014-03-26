#ifndef _LBFIELD_H_
#define _LBFIELD_H_

#include "Definitions.h"
#include "Parameters.h"
#include "LBDefinitions.h"

class LBField{

public:
	LBField(const Parameters & parameters);

	// Constructs an LBField out of its size
	LBField(int cellsX, int cellsY, int cellsZ);
	~LBField();

	const int getNx() const;
	const int getNy() const;
	const int getNz() const;

	const int getCellsX() const;
	const int getCellsY() const;
	const int getCellsZ() const;

	inline const int getDim() const {
		return _dim;
	}
	const int getQ() const;

	inline const int (*const getLatticeVelocities() const)[3] {
		return _latticeVelocities;
	}

	inline const FLOAT* const getLatticeWeights() const {
		return _latticeWeights;
	}

	inline FLOAT* const getFIn() const {
		return _fIn;
	}

	inline FLOAT* const getFOut() const {
		return _fOut;
	}

	inline char * const getFlags() const{
		return _flags;
	}


	const FLOAT getDensity (const FLOAT* const f, int i, int j, int k = 0) const;
	void getVelocity (const FLOAT density, FLOAT* const velocity, const FLOAT* const f, int i, int j, int k = 0) const;

	virtual void getPressureAndVelocity(FLOAT & pressure, FLOAT* const velocity, int i, int j) const;

	virtual void getPressureAndVelocity(FLOAT & pressure, FLOAT* const velocity, int i, int j, int k) const;

	// As xx, xy, yy, xz, yz, zz
	void getSecondMoment (FLOAT * const moments, int i, int j, int k) const;

	inline const int getIndexF (int a, int i, int j, int k = 0) const {
		return i + _cellsX * (j + _cellsY * (k + _cellsZ * a));
	}

	const int getIndexCell (int i, int j, int k = 0) const;

	const int getInverse (int a) const {
		return _Q - a - 1;
	}

	void swap();
	void allocate();
private:
	const int _dim;
	const int _Q;
	const int _Nx, _Ny, _Nz;
	const int _cellsX;
	const int _cellsY;
	const int _cellsZ;
	const int _nofCellsWithBoundaries;

	const int (*const _latticeVelocities)[3];
	const FLOAT * const _latticeWeights;

	FLOAT * _fIn;
	FLOAT * _fOut;
	char * _flags;
};

#endif
