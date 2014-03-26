#ifndef _LBNS_FGH_CORRECTION_ITERATOR_H_
#define _LBNS_FGH_CORRECTION_ITERATOR_H_

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

class LBNSFGHCorrectionIterator {

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

        /** Sets one of the components of the FGH vector to the value of the velocity in that
         * position.
         * @param i Position of the cell in x
         * @param j Position of the cell in y
         * @param k Position of the cell in z
         * @param component The component to be set (0, 1 or 2 for x, y or z respectivelly)
         */
        void setComponent (int i, int j, int k, int component);

    public:

        /** Constructor for the FGH corrector class
         * @param parameters Parameter structure of the simulation
         * @param flowField Reference to the NS flow field
         */
        LBNSFGHCorrectionIterator(const Parameters & parameters, FlowField & flowField);

        /** Performs the correction
         */
        void iterate();
};

#endif
