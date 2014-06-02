#ifndef _STENCIL_H_
#define _STENCIL_H_

//#include "DataStructures.h"
//#include "FlowField.h"
#include "Parameters.h"


/** Stencil class
 *
 * Abstrat class for the definition of stencils and operations on the grids
 */
template<class FlowField>
class FieldStencil {

    protected:

        const Parameters & _parameters;  //! Reference to the parameters

    public:

        FieldStencil ( const Parameters & parameters );
        virtual ~FieldStencil(){}

        /** Performs the operation in 2D in a given position
         * @param flowField Flow field data
         * @param parameters Parameters of the problem
         * @param i Position in the x direction
         * @param j Position in the y direction
         */
        virtual void apply ( FlowField & flowField, int i, int j) = 0;

        /** Performs the operation in 3D in a given position
         * @param flowField Flow field data
         * @param parameters Parameters of the problem
         * @param i Position in the x direction
         * @param j Position in the y direction
         * @param k Position in the z direction
         */
        virtual void apply ( FlowField & flowField, int i, int j, int k) = 0;

};


/** Interface for operations on the global boundary
 */
template<class FlowField>
class GlobalBoundaryStencil {

    protected:

        const Parameters & _parameters;  //! Reference to the parameters

    public:

        GlobalBoundaryStencil ( const Parameters & parameters );
        virtual ~GlobalBoundaryStencil(){}

        /** Represents an operation in the left wall of a 2D domain.
         *
         * @param flowField State of the flow field
         * @param i Index in the x direction
         * @param j Index in the y direction
         */
        virtual void applyLeftWall   (FlowField & flowField, int i, int j) = 0;

        /** Represents an operation in the right wall of a 2D domain.
         *
         * @param flowField State of the flow field
         * @param i Index in the x direction
         * @param j Index in the y direction
         */
        virtual void applyRightWall  (FlowField & flowField, int i, int j) = 0;

        /** Represents an operation in the bottom wall of a 2D domain.
         *
         * @param flowField State of the flow field
         * @param i Index in the x direction
         * @param j Index in the y direction
         */
        virtual void applyBottomWall (FlowField & flowField, int i, int j) = 0;

        /** Represents an operation in the top wall of a 2D domain.
         *
         * @param flowField State of the flow field
         * @param i Index in the x direction
         * @param j Index in the y direction
         */
        virtual void applyTopWall    (FlowField & flowField, int i, int j) = 0;


        /** Represents an operation in the left wall of a 3D domain.
         *
         * @param flowField State of the flow field
         * @param i Index in the x direction
         * @param j Index in the y direction
         * @param k Index in the z direction
         */
        virtual void applyLeftWall   (FlowField & flowField, int i, int j, int k) = 0;

        /** Represents an operation in the right wall of a 3D domain.
         *
         * @param flowField State of the flow field
         * @param i Index in the x direction
         * @param j Index in the y direction
         * @param k Index in the z direction
         */
        virtual void applyRightWall  (FlowField & flowField, int i, int j, int k) = 0;

        /** Represents an operation in the bottom wall of a 3D domain.
         *
         * @param flowField State of the flow field
         * @param i Index in the x direction
         * @param j Index in the y direction
         * @param k Index in the z direction
         */
        virtual void applyBottomWall (FlowField & flowField, int i, int j, int k) = 0;

        /** Represents an operation in the top wall of a 3D domain.
         *
         * @param flowField State of the flow field
         * @param i Index in the x direction
         * @param j Index in the y direction
         * @param k Index in the z direction
         */
        virtual void applyTopWall    (FlowField & flowField, int i, int j, int k) = 0;

        /** Represents an operation in the front wall of a 3D domain.
         *
         * @param flowField State of the flow field
         * @param i Index in the x direction
         * @param j Index in the y direction
         * @param k Index in the z direction
         */
        virtual void applyFrontWall  (FlowField & flowField, int i, int j, int k) = 0;

        /** Represents an operation in the back wall of a 3D domain.
         *
         * @param flowField State of the flow field
         * @param i Index in the x direction
         * @param j Index in the y direction
         * @param k Index in the z direction
         */
        virtual void applyBackWall   (FlowField & flowField, int i, int j, int k) = 0;
};

template<class FlowField>
class SmartGlobalBoundaryStencil {

    protected:

        const Parameters & _parameters;  //! Reference to the parameters

    public:

        SmartGlobalBoundaryStencil ( const Parameters & parameters );
        virtual ~SmartGlobalBoundaryStencil(){}

        /** Represents an operation in the left wall of a 3D domain.
         *
         * @param flowField State of the flow field
         * @param i Index in the x direction
         * @param j Index in the y direction
         * @param k Index in the z direction
         */
        virtual bool applyLeftWall   (FlowField & flowField, int i, int j, int k) = 0;

        /** Represents an operation in the right wall of a 3D domain.
         *
         * @param flowField State of the flow field
         * @param i Index in the x direction
         * @param j Index in the y direction
         * @param k Index in the z direction
         */
        virtual bool applyRightWall  (FlowField & flowField, int i, int j, int k) = 0;

        /** Represents an operation in the bottom wall of a 3D domain.
         *
         * @param flowField State of the flow field
         * @param i Index in the x direction
         * @param j Index in the y direction
         * @param k Index in the z direction
         */
        virtual bool applyBottomWall (FlowField & flowField, int i, int j, int k) = 0;

        /** Represents an operation in the top wall of a 3D domain.
         *
         * @param flowField State of the flow field
         * @param i Index in the x direction
         * @param j Index in the y direction
         * @param k Index in the z direction
         */
        virtual bool applyTopWall    (FlowField & flowField, int i, int j, int k) = 0;

        /** Represents an operation in the front wall of a 3D domain.
         *
         * @param flowField State of the flow field
         * @param i Index in the x direction
         * @param j Index in the y direction
         * @param k Index in the z direction
         */
        virtual bool applyFrontWall  (FlowField & flowField, int i, int j, int k) = 0;

        /** Represents an operation in the back wall of a 3D domain.
         *
         * @param flowField State of the flow field
         * @param i Index in the x direction
         * @param j Index in the y direction
         * @param k Index in the z direction
         */
        virtual bool applyBackWall   (FlowField & flowField, int i, int j, int k) = 0;
};

template<class FlowField>
class ParallelBoundaryStencil {

    protected:

        const Parameters & _parameters;  //! Reference to the parameters

    public:

        ParallelBoundaryStencil ( const Parameters & parameters );
        virtual ~ParallelBoundaryStencil(){}

        /** Represents an operation in the left wall of a 2D domain.
         *
         * @param flowField State of the flow field
         * @param i Index in the x direction
         * @param j Index in the y direction
         */
        virtual void applyLeftWall   (FlowField & flowField, int i, int j) = 0;

        /** Represents an operation in the right wall of a 2D domain.
         *
         * @param flowField State of the flow field
         * @param i Index in the x direction
         * @param j Index in the y direction
         */
        virtual void applyRightWall  (FlowField & flowField, int i, int j) = 0;

        /** Represents an operation in the bottom wall of a 2D domain.
         *
         * @param flowField State of the flow field
         * @param i Index in the x direction
         * @param j Index in the y direction
         */
        virtual void applyBottomWall (FlowField & flowField, int i, int j) = 0;

        /** Represents an operation in the top wall of a 2D domain.
         *
         * @param flowField State of the flow field
         * @param i Index in the x direction
         * @param j Index in the y direction
         */
        virtual void applyTopWall    (FlowField & flowField, int i, int j) = 0;


        /** Represents an operation in the left wall of a 3D domain.
         *
         * @param flowField State of the flow field
         * @param i Index in the x direction
         * @param j Index in the y direction
         * @param k Index in the z direction
         */
        virtual void applyLeftWall   (FlowField & flowField, int i, int j, int k) = 0;

        /** Represents an operation in the right wall of a 3D domain.
         *
         * @param flowField State of the flow field
         * @param i Index in the x direction
         * @param j Index in the y direction
         * @param k Index in the z direction
         */
        virtual void applyRightWall  (FlowField & flowField, int i, int j, int k) = 0;

        /** Represents an operation in the bottom wall of a 3D domain.
         *
         * @param flowField State of the flow field
         * @param i Index in the x direction
         * @param j Index in the y direction
         * @param k Index in the z direction
         */
        virtual void applyBottomWall (FlowField & flowField, int i, int j, int k) = 0;

        /** Represents an operation in the top wall of a 3D domain.
         *
         * @param flowField State of the flow field
         * @param i Index in the x direction
         * @param j Index in the y direction
         * @param k Index in the z direction
         */
        virtual void applyTopWall    (FlowField & flowField, int i, int j, int k) = 0;

        /** Represents an operation in the front wall of a 3D domain.
         *
         * @param flowField State of the flow field
         * @param i Index in the x direction
         * @param j Index in the y direction
         * @param k Index in the z direction
         */
        virtual void applyFrontWall  (FlowField & flowField, int i, int j, int k) = 0;

        /** Represents an operation in the back wall of a 3D domain.
         *
         * @param flowField State of the flow field
         * @param i Index in the x direction
         * @param j Index in the y direction
         * @param k Index in the z direction
         */
        virtual void applyBackWall   (FlowField & flowField, int i, int j, int k) = 0;
};
#include "Stencil.cpph"

#endif
