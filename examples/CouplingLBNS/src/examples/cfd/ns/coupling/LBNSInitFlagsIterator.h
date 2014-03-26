#ifndef _LBNS_INIT_FLAGS_ITERATOR_H_
#define _LBNS_INIT_FLAGS_ITERATOR_H_

#include "CouplingDefinitions.h"
#include "CouplingFunctions.h"
#include "../FlowField.h"
#include "Parameters.h"

/** An interpolator to correct the values of FGH on the boundary. It only replaces the value of
 *  F, G or H by the value of the velocity at the coupling boundary of NS.
 *
 *  It should be applied after velocity has been interpolated and FGH has been computed, and before
 *  the right hand side is computed.
 */

class LBNSInitFlagsIterator {

    private:
        FlowField & _flowField;
        const Parameters & _parameters;

        const int _offset;  // How many cells away from the boundary

        const int _lowerX;
        const int _upperX;
        const int _lowerY;
        const int _upperY;
        const int _lowerZ;
        const int _upperZ;



    public:

        /** Constructor for the FGH corrector class
         * @param parameters Parameter structure of the simulation
         * @param flowField Reference to the NS flow field
         */
        LBNSInitFlagsIterator(const Parameters & parameters, FlowField & flowField);

        /** Performs the correction
         */
        void iterate();
};

#endif
