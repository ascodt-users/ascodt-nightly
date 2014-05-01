#ifndef _LB_NS_COUPLING_ITERATOR_H_
#define _LB_NS_COUPLING_ITERATOR_H_

#include "../LBField.h"
#include "Parameters.h"
#include "LBNSRemoteInterpolator.h"
#include <vector>

// This class exists because it was not trivial to use the already existing iterator to perform
// this operation.
class LBNSCommunicator;
class LBNSCouplingIterator {

    private:
        LBField & _lbField;
        const Parameters & _parameters;
        LBNSRemoteInterpolator _interpolator;
        const int _offset;  // How many cells away from the boundary

        const int _lowerX;
        const int _upperX;
        const int _lowerY;
        const int _upperY;
        const int _lowerZ;
        const int _upperZ;

        int _offsets[3], _cell[3], _middle[3];
        int _normalVector[3];

        std::vector<double> _lbVelocityX;
        std::vector<double> _lbVelocityY;
        std::vector<double> _lbVelocityZ;
        /** Interpolates the component for the given NS cell.
         * @param i Index of the NS cell in the X direction
         * @param j Index of the NS cell in the Y direction
         * @param k Index of the NS cell in the Z direction
         * @param component Component to be interpolated. Pressure is the component of index 4.
         */
        inline void interpolateComponentX (int i, int j, int k);
        inline void interpolateComponentY (int i, int j, int k);
        inline void interpolateComponentZ (int i, int j, int k);

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
        LBNSCouplingIterator (const Parameters & parameters,LBField & lbField);

        /** Performs the interpolation of values from the LB to the NS field
         */
        void iterateBoundary();
        void iterateInner();
        void initGather();
        void flush();
        int getVelocitySizeX();
        int getVelocitySizeY();
        int getVelocitySizeZ();
        double* getVelocityX();
        double* getVelocityY();
        double* getVelocityZ();
        void registerNSRegion(LBNSCommunicator* com);
};

#endif
