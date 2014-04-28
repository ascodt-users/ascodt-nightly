#ifndef _PARAMETERS_H_
#define _PARAMETERS_H_

#include "Definitions.h"
#include <petscsys.h>
#include <string>

//! Classes for the parts of the parameters
//@{
class TimestepParameters{
    public:
        FLOAT dt; //! Timestep
        FLOAT tau;  //! Security factor
};

class SimulationParameters{
    public:
        FLOAT finalTime;  //! Final time for the simulation
        std::string type; //! type of the simulation (DNS vs. turbulence)
        std::string scenario;   //! If channel or cavity, for example
};

class EnvironmentalParameters{
    public:
        // Gravity components
        FLOAT gx;
        FLOAT gy;
        FLOAT gz;
};

class FlowParameters{
    public:
        FLOAT Re;  //! Reynolds number
};

class SolverParameters{
    public:
        FLOAT gamma;  //! Donor cell balance coefficient
        int maxIterations;  //! Maximum number of iterations in the linear solver

};

class GeometricParameters{
    public:
        // Dimensions
        int dim;

        // Number of cells
        int sizeX;
        int sizeY;
        int sizeZ;

        // Cell sizing
        FLOAT dx;
        FLOAT dy;
        FLOAT dz;
};

class WallParameters{
    public:
        // Scalar value definition. Used to define the pressure, for example
        FLOAT scalarLeft;
        FLOAT scalarRight;
        FLOAT scalarBottom;
        FLOAT scalarTop;
        FLOAT scalarFront;
        FLOAT scalarBack;

        // Vector values at the boundaries, to define, for example, the velocities
        FLOAT vectorLeft [3];
        FLOAT vectorRight [3];
        FLOAT vectorBottom [3];
        FLOAT vectorTop [3];
        FLOAT vectorFront [3];
        FLOAT vectorBack [3];

        // Define wether there are periodic boundaries in a direction
        bool periodicX;
        bool periodicY;
        bool periodicZ;

        // Define how will the boundary behave
        BoundaryType typeLeft;
        BoundaryType typeRight;
        BoundaryType typeTop;
        BoundaryType typeBottom;
        BoundaryType typeFront;
        BoundaryType typeBack;
};

class VTKParameters{
    public:
        FLOAT interval;     //! Time interval for file printing
        std::string prefix;   //! Output filename
};

class StdOutParameters{
    public:
        int interval;
};

class ParallelParameters{
    public:

        int rank;               //! Rank of the current processor

        int numProcessors[3];     //! Array with the number of processors in each direction

        //@brief Ranks of the neighbors
        //@{
        int leftNb;
        int rightNb;
        int bottomNb;
        int topNb;
        int frontNb;
        int backNb;
        //@}

        int indices[3];           //! 3D indices to locate the array
        int localSize[3];       //! Size for the local flow field
        int firstCorner[3];     //! Position of the first element. Used for plotting

        PetscInt * sizes[3];         //! Arrays with the sizes of the blocks in each direction.
};

class LBParameters{
    public:
        FLOAT tau;
        FLOAT reciprocalTau;
        FLOAT viscosity;
};

class BFStepParameters{
    public:
        FLOAT xRatio;
        FLOAT yRatio;
        int width;
        int height;
};

class CouplingParameters{
    public:
        bool set;           //! Is the coupling set? Will change the way the LB field is created
        int offsetNS[3];     //! First corner (or offset) of the mixed region
        int sizeNS[3];    //! Size of the mixed region
        int ratio;  //! Number of LB cells per NS elements in one direction
        int overlap;    //! Overlap parameter
        FLOAT refLength;    //! Reference length for the coupling. Length of the NS cell
};

class TimeDependencyParameters{
    public:
        FLOAT period;
        FLOAT reciprocalPeriod;
        FLOAT time;     //! Workaround to deal with passing th time to the time dependent input
};

//@}

/** A class to store and pass around the parameters
 */
class Parameters {
    public:
        SimulationParameters     simulation;
        TimestepParameters       timestep;
        EnvironmentalParameters  environment;
        FlowParameters           flow;
        SolverParameters         solver;
        GeometricParameters      geometry;
        WallParameters           walls;
        VTKParameters            vtk;
        ParallelParameters       parallel;
        StdOutParameters         stdOut;
        LBParameters             lb;
        BFStepParameters         bfStep;
        CouplingParameters       coupling;
        TimeDependencyParameters timeDependency;

};

#endif
