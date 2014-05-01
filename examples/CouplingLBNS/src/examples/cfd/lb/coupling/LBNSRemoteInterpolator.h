#ifndef _LB_NS_REMOTE_INTERPOLATOR_H_
#define _LB_NS_REMOTE_INTERPOLATOR_H_

#include "Definitions.h"
#include "CouplingDefinitions.h"
#include "CouplingFunctions.h"
#include "../LBDefinitions.h"
#include "Parameters.h"
#include "../LBField.h"
#include <vector>
class LBNSCommunicator;
/** This class only has to deal with interpolating values on the NS field for a given cell
 */
class LBNSRemoteInterpolator {

    private:

        const Parameters & _parameters;
        const LBField & _lbField;

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
        std::vector<LBNSCommunicator*> _communicators;
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
        void loadDensity (int i, int j, int k);

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
        bool convertToLocalCoordinates(
        		const int i_in,
        		const int j_in,
        		const int k_in,
        		int& i_out,
        		int& j_out,
        		int& k_out);
        void getCommunicators(
        			const int i,const int j, const int k,
        			std::vector<LBNSCommunicator*>& coms);
    public:

        /** Constructor of the interpolator class.
         * @param parameters Parameter struccture of the simulation
         * @param lbField Reference to the LB field
         * @param flowField Reference to the NS flow field
         */
        LBNSRemoteInterpolator (const Parameters & parameters, const LBField & lbField);

        /** Interpolate one of the components of the velocity
         */
        void interpolateVelocityComponent (int ins, int jns, int kns, int component);
        void registerNSRegion(LBNSCommunicator *com);
        void flush();
        void initGather();
        /** Interpolate the pressure in a NS cell
         */
        //FLOAT interpolatePressure (int ins, int jns, int kns);
};

#endif
