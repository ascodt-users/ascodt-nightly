#include "ChannelInputStencils.h"

static FLOAT computeVelocity2DStatic (FlowField & flowField, int i, int j, int stepSize,
                         const Parameters & parameters){
        const int inletYSize = parameters.geometry.sizeY;

        const FLOAT y = (double)j + parameters.parallel.firstCorner[1] - 1.5;

        return 6.0 * parameters.walls.vectorLeft[0] /
                     (inletYSize * inletYSize) * y * (inletYSize - y);
}

static FLOAT computeVelocity3DStatic (FlowField & flowField, int i, int j, int k, int stepSize,
                         const Parameters & parameters){
    return computeVelocity2DStatic (flowField, i, j, stepSize, parameters);
}

static FLOAT computeVelocity2DOscillating (FlowField & flowField, int i, int j, int stepSize,
                         const Parameters & parameters){
        const int inletYSize = parameters.geometry.sizeY;

        const FLOAT y = (double)j + parameters.parallel.firstCorner[1] - 1.5;

        return 6.0 * sin (6.283185307179586 * parameters.timeDependency.reciprocalPeriod *
                     parameters.timeDependency.time) *
                     parameters.walls.vectorLeft[0] /
                     (inletYSize * inletYSize) * y * (inletYSize - y);
}

static FLOAT computeVelocity3DOscillating (FlowField & flowField, int i, int j, int k, int stepSize,
                         const Parameters & parameters){
    return computeVelocity2DOscillating (flowField, i, j, stepSize, parameters);
}

ChannelInputVelocityStencil::ChannelInputVelocityStencil (const Parameters & parameters) :
    GlobalBoundaryStencil<FlowField> (parameters),
    // Here, the obstacle size is set to zero if it was set as negative at the configuration
    _stepSize (parameters.bfStep.height > 0 ? parameters.bfStep.height : 0)
{
    if (parameters.timeDependency.period == 0){
        computeVelocity2D = & computeVelocity2DStatic;
        computeVelocity3D = & computeVelocity3DStatic;
    } else {
        computeVelocity2D = & computeVelocity2DOscillating;
        computeVelocity3D = & computeVelocity3DOscillating;
    }
}

// Most of the functions are empty, and they shouldn't be called, assuming that the input is always
// located at the left.

void ChannelInputVelocityStencil::applyLeftWall   ( FlowField & flowField, int i, int j ){
    flowField.getVelocity().getVector(i,j)[0] =
        computeVelocity2D(flowField, i, j, _stepSize, _parameters);
    flowField.getVelocity().getVector(i,j)[1] = -flowField.getVelocity().getVector(i+1,j)[1];
}

void ChannelInputVelocityStencil::applyRightWall  ( FlowField & flowField, int i, int j ){}
void ChannelInputVelocityStencil::applyBottomWall ( FlowField & flowField, int i, int j ){}
void ChannelInputVelocityStencil::applyTopWall    ( FlowField & flowField, int i, int j ){}

void ChannelInputVelocityStencil::applyLeftWall   ( FlowField & flowField, int i, int j, int k ){
    flowField.getVelocity().getVector(i,j,k)[0] =
        computeVelocity3D(flowField, i, j, k, _stepSize, _parameters);
    flowField.getVelocity().getVector(i,j,k)[1] = -flowField.getVelocity().getVector(i+1,j,k)[1];
    flowField.getVelocity().getVector(i,j,k)[2] = -flowField.getVelocity().getVector(i+1,j,k)[2];
}

void ChannelInputVelocityStencil::applyRightWall  ( FlowField & flowField, int i, int j, int k ){}
void ChannelInputVelocityStencil::applyBottomWall ( FlowField & flowField, int i, int j, int k ){}
void ChannelInputVelocityStencil::applyTopWall    ( FlowField & flowField, int i, int j, int k ){}
void ChannelInputVelocityStencil::applyFrontWall  ( FlowField & flowField, int i, int j, int k ){}
void ChannelInputVelocityStencil::applyBackWall   ( FlowField & flowField, int i, int j, int k ){}


ChannelInputFGHStencil::ChannelInputFGHStencil(const Parameters & parameters) :
    GlobalBoundaryStencil<FlowField> (parameters),
    _stepSize (parameters.bfStep.height > 0 ? parameters.bfStep.height : 0)
{
    if (parameters.timeDependency.period == 0){
        computeVelocity2D = & computeVelocity2DStatic;
        computeVelocity3D = & computeVelocity3DStatic;
    } else {
        computeVelocity2D = & computeVelocity2DOscillating;
        computeVelocity3D = & computeVelocity3DOscillating;
    }
}

void ChannelInputFGHStencil::applyLeftWall   ( FlowField & flowField, int i, int j ){
    flowField.getFGH().getVector(i,j)[0] =
        computeVelocity2D(flowField, i, j, _stepSize, _parameters);
}

void ChannelInputFGHStencil::applyRightWall  ( FlowField & flowField, int i, int j ){}
void ChannelInputFGHStencil::applyBottomWall ( FlowField & flowField, int i, int j ){}
void ChannelInputFGHStencil::applyTopWall    ( FlowField & flowField, int i, int j ){}

void ChannelInputFGHStencil::applyLeftWall  ( FlowField & flowField, int i, int j, int k ){
    flowField.getFGH().getVector(i,j,k)[0] =
        computeVelocity3D (flowField, i, j, k, _stepSize, _parameters);
}

void ChannelInputFGHStencil::applyRightWall  ( FlowField & flowField, int i, int j, int k ){}
void ChannelInputFGHStencil::applyBottomWall ( FlowField & flowField, int i, int j, int k ){}
void ChannelInputFGHStencil::applyTopWall    ( FlowField & flowField, int i, int j, int k ){}
void ChannelInputFGHStencil::applyFrontWall  ( FlowField & flowField, int i, int j, int k ){}
void ChannelInputFGHStencil::applyBackWall   ( FlowField & flowField, int i, int j, int k ){}
