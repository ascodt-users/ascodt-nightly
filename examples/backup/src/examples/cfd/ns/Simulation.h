#ifndef _SIMULATION_H_
#define _SIMULATION_H_

#include <petscksp.h>
#include <float.h>
#include "FlowField.h"
#include "stencils/FGHStencil.h"
#include "stencils/MovingWallStencils.h"
#include "stencils/RHSStencil.h"
#include "stencils/VelocityStencil.h"
#include "stencils/VTKStencil.h"
#include "stencils/MaxUStencil.h"
#include "stencils/PeriodicBoundaryStencils.h"
#include "stencils/BFStepInitStencil.h"
#include "stencils/NeumannBoundaryStencils.h"
#include "stencils/BFInputStencils.h"
#include "Factories.h"
#include "Iterators.h"
#include "Definitions.h"
#include "Functions.h"
#include "parallelManagers/PetscParallelManager.h"
#include "coupling/LBNSFGHCorrectionIterator.h"
#include "LinearSolver.h"
#include "solvers/SORSolver.h"
#include "solvers/PetscSolver.h"



class Simulation {
protected:
	Parameters &_parameters;

	FlowField &_flowField;

	MaxUStencil _maxUStencil;
	FieldIterator<FlowField> _maxUFieldIterator;
	GlobalBoundaryIterator<FlowField> _maxUBoundaryIterator;

	// Set up the boundary conditions
	GlobalBoundaryFactory _globalBoundaryFactory;
	GlobalBoundaryIterator<FlowField> _wallVelocityIterator;
	GlobalBoundaryIterator<FlowField> _wallFGHIterator;
	LBNSFGHCorrectionIterator _lbnsFGHCorrectionIterator;
	FGHStencil _fghStencil;
	FieldIterator<FlowField> _fghIterator;

	RHSStencil _rhsStencil;
	FieldIterator<FlowField> _rhsIterator;

	VelocityStencil _velocityStencil;
	FieldIterator<FlowField> _velocityIterator;

	PetscParallelManager _parallelManager;

	PetscSolver _solver;


public:
	Simulation(Parameters &parameters, FlowField &flowField):
		_parameters(parameters),
		_flowField(flowField),
		_maxUStencil(parameters),
		_maxUFieldIterator(_flowField,_maxUStencil),
		_maxUBoundaryIterator(_flowField,parameters,_maxUStencil),
		_globalBoundaryFactory(parameters),
		_wallVelocityIterator(_globalBoundaryFactory.getGlobalBoundaryVelocityIterator(_flowField)),
		_wallFGHIterator(_globalBoundaryFactory.getGlobalBoundaryFGHIterator(_flowField)),
		_lbnsFGHCorrectionIterator(parameters,_flowField),
		_fghStencil(parameters),
		_fghIterator(_flowField,_fghStencil),
		_rhsStencil(parameters),
		_rhsIterator(_flowField,_rhsStencil),
		_velocityStencil(parameters),
		_velocityIterator(_flowField,_velocityStencil),
		_parallelManager(_flowField,parameters),
		_solver(_flowField,parameters) // Has to cover also the boundaries
		{
		}

	virtual ~Simulation(){}

	virtual void solveTimestepPhaseOne(){
		// Get the time step
		_maxUStencil.reset();    // Not that nice
		_maxUFieldIterator.iterate();
		_maxUBoundaryIterator.iterate();
		setTimeStep();

		// compute fgh
		_fghIterator.iterate();

		// set global boundary values
		_wallFGHIterator.iterate();


	}

	virtual void solveTimestepPhaseTwo(){

		// Set FGH in coupling boundaries
		_lbnsFGHCorrectionIterator.iterate();
		// compute the right hand side
		_rhsIterator.iterate();

		_solver.solve();

		_parallelManager.communicatePressure();

		// compute velocity
		_velocityIterator.iterate();

		_parallelManager.communicateVelocity();

		// Iterate for velocities on the boundary
		_wallVelocityIterator.iterate();

	}
	/** plots the flow field. TODO CARLOS: INCLUDE THIS IN SOLVER ALGORITHM (PLOT PER X TIME STEPS OR TIME INTERVAL, RESPECTIVELY) */
	virtual void plotVTK(int timeStep){
		 VTKStencil vtkStencil( _parameters );
		      FieldIterator<FlowField> vtkIterator( _flowField, vtkStencil, 1, 0 );

		      vtkStencil.openFile ( _flowField, timeStep);
		      vtkIterator.iterate();
		      vtkStencil.write( _flowField );
		      vtkStencil.closeFile();
	}

protected:
	/** sets the time step*/
	void setTimeStep(){

		FLOAT localMin, globalMin;

		assertion(_flowField.getDim() == 2 || _flowField.getDim() == 3);
		FLOAT factor = 1/(_parameters.geometry.dx * _parameters.geometry.dx) +
				1/(_parameters.geometry.dy * _parameters.geometry.dy);
		if (_flowField.getDim() == 3) {
			factor += 1/(_parameters.geometry.dz * _parameters.geometry.dz);
			_parameters.timestep.dt = _parameters.geometry.dz / _maxUStencil.getMaxValues()[2];
		} else {
			_parameters.timestep.dt = _parameters.flow.Re / 2 / factor;
		}

		localMin = std::min(_parameters.timestep.dt,
				std::min(std::min(_parameters.flow.Re/(2*factor),
						_parameters.geometry.dx / _maxUStencil.getMaxValues()[0]),
						_parameters.geometry.dy / _maxUStencil.getMaxValues()[1]));

		// Here, we select the type of operation before compiling. This allows to use the correct
		// data type for MPI. Not a concern for small simulations, but useful if using heterogeneous
		// machines.

		globalMin = MY_FLOAT_MAX;
		MPI_Allreduce(&localMin, &globalMin, 1, MY_MPI_FLOAT, MPI_MIN, PETSC_COMM_WORLD);

		_parameters.timestep.dt = globalMin;
		_parameters.timestep.dt *= _parameters.timestep.tau;
	}

};

#endif // _SIMULATION_H_

