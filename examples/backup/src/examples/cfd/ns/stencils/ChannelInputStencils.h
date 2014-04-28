#ifndef _CHANNEL_INPUT_VELOCITY_STENCIL_H_
#define _CHANNEL_INPUT_VELOCITY_STENCIL_H_

#include "Stencil.h"
#include "Parameters.h"
#include "../FlowField.h"

/**
 * A stencil to set the input velocity in channel flows.
 */
class ChannelInputVelocityStencil : public GlobalBoundaryStencil<FlowField> {

    public:
        ChannelInputVelocityStencil (const Parameters & parameters);

        void applyLeftWall   ( FlowField & flowField, int i, int j );
        void applyRightWall  ( FlowField & flowField, int i, int j );
        void applyBottomWall ( FlowField & flowField, int i, int j );
        void applyTopWall    ( FlowField & flowField, int i, int j );

        void applyLeftWall   ( FlowField & flowField, int i, int j, int k );
        void applyRightWall  ( FlowField & flowField, int i, int j, int k );
        void applyBottomWall ( FlowField & flowField, int i, int j, int k );
        void applyTopWall    ( FlowField & flowField, int i, int j, int k );
        void applyFrontWall  ( FlowField & flowField, int i, int j, int k );
        void applyBackWall   ( FlowField & flowField, int i, int j, int k );

    private:
        const int _stepSize; //! fixes the size of the step. If zero, is just channel flow
        FLOAT (*computeVelocity2D) (FlowField & flowField, int i, int j, int stepSize,
                                  const Parameters & parameters);
        FLOAT (*computeVelocity3D) (FlowField & flowField, int i, int j, int k, int stepSize,
                                  const Parameters & parameters);
};

class ChannelInputFGHStencil : public GlobalBoundaryStencil<FlowField> {

    public:
        ChannelInputFGHStencil (const Parameters & parameters);

        void applyLeftWall   ( FlowField & flowField, int i, int j );
        void applyRightWall  ( FlowField & flowField, int i, int j );
        void applyBottomWall ( FlowField & flowField, int i, int j );
        void applyTopWall    ( FlowField & flowField, int i, int j );

        void applyLeftWall   ( FlowField & flowField, int i, int j, int k );
        void applyRightWall  ( FlowField & flowField, int i, int j, int k );
        void applyBottomWall ( FlowField & flowField, int i, int j, int k );
        void applyTopWall    ( FlowField & flowField, int i, int j, int k );
        void applyFrontWall  ( FlowField & flowField, int i, int j, int k );
        void applyBackWall   ( FlowField & flowField, int i, int j, int k );

    private:
        const int _stepSize; //! fixes the size of the step. If zero, is just channel flow
        FLOAT (*computeVelocity2D) (FlowField & flowField, int i, int j, int stepSize,
                                  const Parameters & parameters);
        FLOAT (*computeVelocity3D) (FlowField & flowField, int i, int j, int k, int stepSize,
                                  const Parameters & parameters);
};

#endif
