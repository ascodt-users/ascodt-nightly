#include "FGHStencil.h"
#include "StencilFunctions.h"
#include "Definitions.h"

FGHStencil::FGHStencil ( const Parameters & parameters ) : FieldStencil<FlowField> ( parameters ) {}


void FGHStencil::apply ( FlowField & flowField,  int i, int j ){

    // Load local velocities into the center layer of the local array

    loadLocalVelocity2D(flowField, _localVelocity, i, j);

    // Now the localVelocity array should contain lexicographically ordered elements around the
    // given index

    _values [0] = computeF2D(_localVelocity, _parameters, _parameters.timestep.dt);
    _values [1] = computeG2D(_localVelocity, _parameters, _parameters.timestep.dt);

    flowField.getFGH().setVector( _values, i, j );

}


void FGHStencil::apply ( FlowField & flowField, int i, int j, int k ){
    // The same as in 2D, with slight modifications

    const int obstacle = flowField.getFlags().getValue(i, j, k);

    _values[0] = 0.0;
    _values[1] = 0.0;
    _values[2] = 0.0;

    if ((obstacle & OBSTACLE_SELF) == 0){   // If the cell is fluid

        loadLocalVelocity3D(flowField, _localVelocity, i, j, k);

        if ((obstacle & OBSTACLE_RIGHT) == 0) { // If the right cell is fluid
            _values [0] = computeF3D(_localVelocity, _parameters, _parameters.timestep.dt);
        }
        if ((obstacle & OBSTACLE_TOP) == 0) {
            _values [1] = computeG3D(_localVelocity, _parameters, _parameters.timestep.dt);
        }
        if ((obstacle & OBSTACLE_BACK) == 0) {
            _values [2] = computeH3D(_localVelocity, _parameters, _parameters.timestep.dt);
        }
    }
    flowField.getFGH().setVector( _values, i, j, k );
}
