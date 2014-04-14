#ifndef _MAX_U_STENCIL_H_
#define _MAX_U_STENCIL_H_

#include "Stencil.h"
#include "Parameters.h"
#include "../FlowField.h"


class MaxUStencil : public FieldStencil<FlowField>, public GlobalBoundaryStencil<FlowField> {

    private:

        FLOAT _maxValues[3];  //! Stores the maximum module of every component

    public:

        /** Constructor
         *
         * @param parameters Parameters of the problem
         */
        MaxUStencil (const Parameters & parameters);

        //@ brief Body iterations
        //@{
        void apply (FlowField & flowField, int i, int j);
        void apply (FlowField & flowField, int i, int j, int k);
        //@}

        //@ brief Boundary iterations for the 2D problem
        //@param flowField Flow field with the state of the fluid
        //@param i Position in the X direction
        //@param j Position in the Y direction
        //@{
        void applyLeftWall   ( FlowField & flowField, int i, int j );
        void applyRightWall  ( FlowField & flowField, int i, int j );
        void applyBottomWall ( FlowField & flowField, int i, int j );
        void applyTopWall    ( FlowField & flowField, int i, int j );
        //@}

        //@ brief Boundary iterations for the 3D problem
        //@param flowField Flow field with the state of the fluid
        //@param i Position in the X direction
        //@param j Position in the Y direction
        //@param k Position in the Z direction
        //@{
        void applyLeftWall   ( FlowField & flowField, int i, int j, int k );
        void applyRightWall  ( FlowField & flowField, int i, int j, int k );
        void applyBottomWall ( FlowField & flowField, int i, int j, int k );
        void applyTopWall    ( FlowField & flowField, int i, int j, int k );
        void applyFrontWall  ( FlowField & flowField, int i, int j, int k );
        void applyBackWall   ( FlowField & flowField, int i, int j, int k );
        //@}

        /** Sets the maximum value arrays to the value of the cell if it surpasses the current one.
         *
         * 2D version of the function
         * @param flowField Flow field
         * @param i Position in the X direction.
         * @param j Position in the Y direction.
         */
        void cellMaxValue(FlowField & flowField, int i, int j);

        /** Sets the maximum value arrays to the value of the cell if it surpasses the current one.
         *
         * 3D version of the function
         * @param flowField Flow field
         * @param i Position in the X direction.
         * @param j Position in the Y direction.
         * @param k Position in the Z direction.
         */
        void cellMaxValue(FlowField & flowField, int i, int j, int k);

        /** Resets the maximum values to zero before computing the timestep
         */
        void reset ();

        /** Returns the array with the maximum modules of the components of the velocity
         */
        const FLOAT * getMaxValues() const;
};

#endif