#ifndef _LB_NS_COUPLING_ITERATOR_H_
#define _LB_NS_COUPLING_ITERATOR_H_

#include "../FlowField.h"
#include "examples/cfd/lb/LBField.h"
#include "Parameters.h"
#include "LBNSRemoteInterpolator.h"
#include <vector>
//#include "LBNSInterpolator.h"


// This class exists because it was not trivial to use the already existing iterator to perform
// this operation.
struct Contribution{
		int x;
		int y;
		int z;
		int component;
	};
class LBNSCouplingIterator {

    private:
	    LBNSRemoteInterpolator _interpolator;
        FlowField & _flowField;

        const Parameters & _parameters;
        const int _offset;  // How many cells away from the boundary
        std::vector<Contribution> _localContributions;
        int _lowerX;
        int _upperX;
        int _lowerY;
        int _upperY;
        int _lowerZ;
        int _upperZ;

        int _offsets[3], _cell[3], _middle[3];
        int _normalVector[3];
        /** Interpolates the component for the given NS cell.
         * @param i Index of the NS cell in the X direction
         * @param j Index of the NS cell in the Y direction
         * @param k Index of the NS cell in the Z direction
         * @param component Component to be interpolated. Pressure is the component of index 4.
         */
        inline void interpolateComponent (int i, int j, int k, int component);

        inline bool toLocalIndex(const int i,const int j, const int k,int& i_out,int& j_out, int& k_out) const;
        /** Sets the unitary normal vector pointing outside of the LB box
         * @parmaeter nx Component in x
         * @parameter ny Component in y
         * @parameter nz Component in z
         */
        inline void setNormalVector(int nx, int ny, int nz);

    public:

        /** Constructor for the LB->NS coupling class
         * @parameter parameters Parameter structure for the simulation
         * @parameter flowField Reference to the NS flow field
         * @parameter lbField Reference to the LB field
         */
        LBNSCouplingIterator (const Parameters & parameters,FlowField & flowField);
        void setVelocity(
        		const int key,
        		const int offsetX,
        		const int offsetY,
        		const int offsetZ,
        		const int flipsX,
        		const int flipsY,
        		const int flipsZ,
        		const double value);
        void iterateInner();
        void swap(){
        	_interpolator.swap();
        }
        void clear();
        std::vector<double>& getCouplingData(){
        	return _interpolator.getCouplingData();
        }
        /** Performs the interpolation of values from the LB to the NS field
         */
        void iterateBoundary();
        void setLBVelocities(double* velocityX,double* velocityY, double* velocityZ,int sizeX,int sizeY,int sizeZ);
};

#endif
