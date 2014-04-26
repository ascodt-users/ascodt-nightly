#ifndef _LB_NS_REMOTE_INTERPOLATOR_H_
#define _LB_NS_REMOTE_INTERPOLATOR_H_

#include "Definitions.h"
#include "CouplingDefinitions.h"
#include "CouplingFunctions.h"
//#include "../LBDefinitions.h"
#include "Parameters.h"
#include <hash_map>
#include <vector>
#include "examples/cfd/lb/LBField.h"
#include <fstream>
/** This class only has to deal with interpolating values on the NS field for a given cell
 */
struct LBNSData{
	int offset[3];
	int flip[3];
	double value;
};
class LBNSRemoteInterpolator {

private:

	const Parameters & _parameters;
	// Limits for the cells where we can interpolate
	const int _lowerX;
	const int _upperX;
	const int _lowerY;
	const int _upperY;
	const int _lowerZ;
	const int _upperZ;

	const int _M;       //! Number of LB cells per NS cell in one direction
	const int _halfM;   //! Half of M. Division is expensive, so just compute it here.
	const int _modulo;  //! 1 if M is odd
	const FLOAT _reciprocalRatio;   //! 1 / M

	const FLOAT _dx;
	const FLOAT _dt;
	const FLOAT _referenceVelocity;

	int _flip [3];
	int _offset [3];
	FLOAT _weights [stencilSize];  //! Intermediate step during the interpolation
	FLOAT _locationVector [stencilSize];
	FLOAT _regularizedPosition[3];
	FLOAT _values[stencilSize];
	__gnu_cxx::hash_map<int, std::vector<LBNSData> > _velocities[3];
	std::ofstream _logComm;
	bool _open;
	/** Obtain the coordinates of a value in a NS cell in the LB grid.
	 *
	 * Since an integer number of LB cells fit in a NS cell, the value will lie either in the
	 * center or the edge of the LB cell (All of this in one direction), therefore, we can use
	 * integer values to represent these instead of lating having to compare floating point
	 * values.
	 *
	 * @return position Cell where the value is located
	 * @return middle Whether the value is in the middle. Otherwise, it would be in the lower
	 *                end. To represent the upper end, use the next cell
	 */
	void locateInLBGrid (int * const lbPosition, int * const middle,
			int ins, int jns, int kns, int component);

	/** Checks if the given position is within the region that can be interpolated.
	 */
	bool checkIfValid (const int * const lbPosition, const int * const middle);

	/** Gets stencil offset, flip and position ready. If the position arrays are provided,
	 * there's no need for information about the component, since in LB, everything is in the
	 * center of the cell
	 */
	void setArrays (const int * const lbPosition, const int * const middle);

	/** Load the density values into the values array
	 * @param i First index of the LB cell
	 * @param j Second index of the LB cell
	 * @param k Third index of the LB cell
	 * @param offset Array of offsets for the stencil
	 * @param flip Array of flips for the stencil
	 */


	/** Load one of the components of the velocity into the values array
	 * @param i First index of the LB cell
	 * @param j Second index of the LB cell
	 * @param k Third index of the LB cell
	 * @param offset Array of offsets for the stencil
	 * @param flip Array of flips for the stencil
	 * @param component value (0, 1 or 2) determining what component of the velocity
	 */
	void loadVelocityComponent (int i, int j, int k,const int & component);

	void printParameters();
	const double  getVelocity(
			const int i, const int j, const int k,const int l,
			const int component,
			const int* offset,
			const int* flip,
			const int index);
	inline int index2array ( int i, int j, int k, int component, int stencil ) const;
	void open();
public:
	void setVelocity(
			const int key,
			const int offsetX,
			const int offsetY,
			const int offsetZ,
			const int flipsX,
			const int flipsY,
			const int flipsZ,
			const int component,
			const double value);
	void clear();
	/** Constructor of the interpolator class.
	 * @param parameters Parameter struccture of the simulation
	 * @param lbField Reference to the LB field
	 * @param flowField Reference to the NS flow field
	 */
	LBNSRemoteInterpolator (const Parameters & parameters);

	/** Interpolate one of the components of the velocity
	 */
	FLOAT interpolateVelocityComponent (int ins, int jns, int kns, int component);

};

#endif
