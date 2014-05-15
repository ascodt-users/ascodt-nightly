#ifndef _ITERATORS_H_
#define _ITERATORS_H_

#include "Stencil.h"
//#include "FlowField.h"
#include "Parameters.h"


/** Iterator class
 *
 * Applies operations to a flow field
 */
template<class FlowField>
class Iterator {

protected:

	FlowField & _flowField;     //! Reference to the flow field

public:

	/** Constructor for the iterator
	 *
	 * Creates an iterator, given a flow field and a stencil instance
	 *
	 * @param flowField Flow field with the state of the flow
	 * @param stencil Stencil defining an operation to be applied
	 */
	Iterator ( FlowField & flowfield ): _flowField(flowfield){}

	/** Perform the stencil operation on inner, non-ghost cells
	 */
	virtual void iterate () = 0;
};

template<class FlowField>
class FieldIterator : public Iterator<FlowField> {

private:

	FieldStencil<FlowField> & _stencil;         //! Reference to a stencil

	//@brief Define the iteration domain to include more or less layers
	// Added since the ability to select the iteration domain provides more flexibility
	//@{
	const int _lowOffset;
	const int _highOffset;
	//@}

public:

	FieldIterator (FlowField & flowField, FieldStencil<FlowField> & stencil,
			int lowOffset = 0, int highOffset = 0);

	/** Volume iteration over the field.
	 *
	 * Volume iteration. The stencil will be applied to all cells in the domain plus the upper
	 * boundaries. Lower boundaries are not included.
	 */
	void iterate ();
};


template<class FlowField>
class GlobalBoundaryIterator : public Iterator<FlowField> {

private:

	const Parameters & _parameters;

	const int _lowOffset;
	const int _highOffset;

	// This iterator has a reference to a stencil for each side, and will call its methods
	GlobalBoundaryStencil<FlowField> & _leftWallStencil;   //! Stencil used on the left wall
	GlobalBoundaryStencil<FlowField> & _rightWallStencil;  //! Stencil used on the right wall
	GlobalBoundaryStencil<FlowField> & _bottomWallStencil; //! Stencil used on the bottom wall
	GlobalBoundaryStencil<FlowField> & _topWallStencil;    //! Stencil used on the top wall
	GlobalBoundaryStencil<FlowField> & _frontWallStencil;  //! Stencil used on the front wall
	GlobalBoundaryStencil<FlowField> & _backWallStencil;   //! Stencil used on the back wall

public:

	/** Constructor for a single stencil in all faces
	 * @param flowField The flowfield information
	 * @param stencil Stencil for all faces
	 */
	GlobalBoundaryIterator (FlowField & flowField, const Parameters & parameters,
			GlobalBoundaryStencil<FlowField> & stencil,
			int lowOffset = 0, int highOffset = 0);

	/** Constructor with different stencils for each face. For the 2D case.
	 * @param flowField Flow field information
	 * @param <some>WallStencil Stencil used on <some> wall
	 */
	GlobalBoundaryIterator ( FlowField & flowField, const Parameters & parameters,
			GlobalBoundaryStencil<FlowField> & leftWallStencil,
			GlobalBoundaryStencil<FlowField> & rightWallStencil,
			GlobalBoundaryStencil<FlowField> & bottomWallStencil,
			GlobalBoundaryStencil<FlowField> & topWallStencil,
			int lowOffset = 0, int highOffset = 0);

	/** Constructor with different stencils for each face. For the 3D case.
	 * @param flowField Flow field information
	 * @param <some>WallStencil Stencil used on <some> wall
	 */
	GlobalBoundaryIterator ( FlowField & flowField, const Parameters & parameters,
			GlobalBoundaryStencil<FlowField> & leftWallStencil,
			GlobalBoundaryStencil<FlowField> & rightWallStencil,
			GlobalBoundaryStencil<FlowField> & bottomWallStencil,
			GlobalBoundaryStencil<FlowField> & topWallStencil,
			GlobalBoundaryStencil<FlowField> & frontWallStencil,
			GlobalBoundaryStencil<FlowField> & backWallStencil,
			int lowOffset = 0, int highOffset = 0);

	/** Surface iterator
	 *
	 * Iterates on the boundary cells. Only upper corners and edges are iterated.
	 */
	void iterate ();
};

template <class FlowField>
class ParallelBoundaryIterator : public Iterator<FlowField> {

private:
	const Parameters & _parameters;
	ParallelBoundaryStencil<FlowField> & _stencil;

	const int _lowOffset;
	const int _highOffset;

public:
	ParallelBoundaryIterator(FlowField & flowField,
			const Parameters & parameters,
			ParallelBoundaryStencil<FlowField> & stencil,
			int lowOffset = 0, int highOffset = 0);
	void iterate();
};

template <class FlowField>
class XParallelBoundaryIterator : public Iterator<FlowField> {

private:
	const Parameters & _parameters;
	ParallelBoundaryStencil<FlowField> & _stencil;

	int _lowOffset[3];
	int _highOffset[3];

public:
	XParallelBoundaryIterator(FlowField & flowField,
			const Parameters & parameters,
			ParallelBoundaryStencil<FlowField> & stencil,
			int lowOffsetX = 0, int highOffsetX = 0,int lowOffsetY = 0, int highOffsetY = 0,int lowOffsetZ = 0, int highOffsetZ = 0);
	void iterate();
};

template <class FlowField>
class YParallelBoundaryIterator : public Iterator<FlowField> {

private:
	const Parameters & _parameters;
	ParallelBoundaryStencil<FlowField> & _stencil;

	int _lowOffset[3];
	int _highOffset[3];

public:
	YParallelBoundaryIterator(FlowField & flowField,
			const Parameters & parameters,
			ParallelBoundaryStencil<FlowField> & stencil,
			int lowOffsetX = 0, int highOffsetX = 0,int lowOffsetY = 0, int highOffsetY = 0,int lowOffsetZ = 0, int highOffsetZ = 0);
	void iterate();
};

template <class FlowField>
class ZParallelBoundaryIterator : public Iterator<FlowField> {

private:
	const Parameters & _parameters;
	ParallelBoundaryStencil<FlowField> & _stencil;

	int _lowOffset[3];
	int _highOffset[3];
public:
	ZParallelBoundaryIterator(FlowField & flowField,
			const Parameters & parameters,
			ParallelBoundaryStencil<FlowField> & stencil,
			int lowOffsetX = 0, int highOffsetX = 0,int lowOffsetY = 0, int highOffsetY = 0,int lowOffsetZ = 0, int highOffsetZ = 0);
	void iterate();
};
#include "Iterators.cpph"

#endif
