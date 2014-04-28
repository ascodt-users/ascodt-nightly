#ifndef _PETSC_PARALLEL_MANAGER_H_
#define _PETSC_PARALLEL_MANAGER_H_

#include <petscksp.h>
#include <petscdmda.h>

#include "Parameters.h"
#include "../LBField.h"
#include "ParallelManager.h"
#include "BufferStencils.h"
#include "Iterators.h"

/** Class dedicated to the transfer of boundary information between subdomains
 */
class LBParallelManager : public ParallelManager<LBField>  {

private:

	// Location of the elements of the subdomain
	//PetscInt _firstX, _lengthX, _firstY, _lengthY, _firstZ, _lengthZ;

	// Input and output buffers
	FLOAT *_leftBufferIn, *_rightBufferIn,
	*_bottomBufferIn, *_topBufferIn,
	*_frontBufferIn, *_backBufferIn;

	FLOAT *_leftBufferOut, *_rightBufferOut,
	*_bottomBufferOut, *_topBufferOut,
	*_frontBufferOut, *_backBufferOut;

	int _bufferSize;     //! Sizes of the buffers in each direction. Components are x, y, z
	int _numRequests;
	//! @brief Functions to fill and read the buffers
	//! @{
	LBBufferFillStencil _extractPdfsStencil;
	LBBufferReadStencil _injectPdfsStencil;

	XParallelBoundaryIterator<LBField> _extractPdfsIteratorX;
	YParallelBoundaryIterator<LBField> _extractPdfsIteratorY;
	ZParallelBoundaryIterator<LBField> _extractPdfsIteratorZ;
	XParallelBoundaryIterator<LBField> _injectPdfsIteratorX;
	YParallelBoundaryIterator<LBField> _injectPdfsIteratorY;
	ZParallelBoundaryIterator<LBField> _injectPdfsIteratorZ;


	MPI_Status _mpiStatus;  //! For the MPI functions


public:
	void communicatePdfs();

	/* Constructor
	 * @param parameters An instance of the parameters
	 */
	LBParallelManager (LBField & flowField, const Parameters & parameters);

	/** Destructor */
	~LBParallelManager();

};

#endif
