#ifndef _NSLB_COUPLING_STENCIL_H_
#define _NSLB_COUPLING_STENCIL_H_

#include "Stencil.h"
#include "Definitions.h"
#include "CouplingDefinitions.h"
#include "CouplingFunctions.h"
#include "../LBDefinitions.h"
#include "../stencils/LBFunctions.h"
#include "Parameters.h"
#include "../LBField.h"
#include <vector>
/** Stencil to copy information from the NS to the LB domain.
 */

class NSLBCouplingStencil : public GlobalBoundaryStencil<LBField> {


    public:

        /** Constructor of the class with the position of the LB subdomain defined in independent
         * paramenters.
         * @param parameters Parameter structure of the simulation.
         * @param lbField Reference to the LB field
         * @param nsField Reference to the NS flow field.
         * @param nsLowX Index of the first plane of cells in the X direction. These cells are
         * part of the LB subdomain
         * @param nsHighX Index of the last plane of cells in the X direction. These cells are
         * part of the LB subdomain
         * @param nsLowY Index of the first plane of cells in the Y direction. These cells are
         * part of the LB subdomain
         * @param nsHighY Index of the last plane of cells in the Y direction. These cells are
         * part of the LB subdomain
         * @param nsLowZ Index of the first plane of cells in the Z direction. These cells are
         * part of the LB subdomain
         * @param nsHighZ Index of the last plane of cells in the Z direction. These cells are
         * part of the LB subdomain
         */
        NSLBCouplingStencil (const Parameters & parameters,
                             LBField & lbField,
                             int nsLowX, int nsHighX,
                             int nsLowY, int nsHighY,
                             int nsLowZ, int nsHighZ);

        /** Constructor of the transfer class where the position of the LB subdomain is defined
         * inside the parameter structure.
         * @param parameters Parameter structure of the simulation
         * @param lbField Reference to the LB field.
         * @param nsField Reference to the NS flow field.
         */
        NSLBCouplingStencil (const Parameters & parameters, LBField & lbField);

        /** Destructor. Currently does nothing
         */
        ~NSLBCouplingStencil();

        /** Getter for the LB cell length
         * @return Side length of one LB cell
         */
        const FLOAT getDx() const;

        /** Getter for the LB time step
         * @return Time elapsed in one LB update in NS units.
         */
        const FLOAT getDt() const;

        /** Sets the mean pressure, around which the densities of the LB distributions will be set.
         * @param Value of the pressure to which the equivalent of the LB density variations will
         * be added.
         */
        void setMeanPressure(const FLOAT & pressure);

        /** Computes the average in the boundary of the LB domain.
         * It will loop on the corresponding layer in the NS field to find the mean.
         * @return Mean pressure at the boundary of the LB field.
         */
        FLOAT computeBoundaryMeanPressure();
        void reset();
        /** Does the whole operation given the LB indices.
         * @param i Index of the LB cell in the X direction.
         * @param j Index of the LB cell in the Y direction.
         * @param k Index of the LB cell in the Z direction.
         * @param flip Vector stating in which directions the interpolation stencil has been
         * flipped.
         */
        void interpolate (int i, int j, int k, const int * const flip);

        /** Interpolates the value of the pressure from the NS field in the given LB cell.
         * This is an auxiliary function for the function computeBoundaryMeanPressure
         * @param i Index of the cell in the X direction.
         * @param j Index of the cell in the Y direction.
         * @param k Index of the cell in the Z direction.
         * @param flip Vector stating in which directions the interpolation stencil has been
         * flipped.
         */
        FLOAT interpolatePressure (int i, int j, int k, const int * const flip);

        /** Interpolates a given velocity component from the NS field for the given LB cell.
         * @param cell Array with the indices of the NS cell that contains the point.
         * @param position Position of the point in the NS cell.
         * @param component Component to be interpolated
         * @param flip Vector with information of which components should be flipped.
         */
        FLOAT interpolateVelocityComponent (const int * const cell, const FLOAT * const position,
                                            int component, const int * const flip);

        /** Getter for the reciprocal velocity in LB
         * @return Reciprocal of the LB velocity in NS units.
         */
        FLOAT getReciprocalVelocity() const;

        /** Prints the parameters of the coupling from NS to LB
         */
        void printParameters ();

        /** @defgroup 2Dfunctions
         * 2D boundary iterator functions
         * @param lbField Reference to the LB field.
         * @param i Position of the cell in the X direction
         * @param j Position of the cell in the Y direction
         * @{
         */

        /** @brief Function for the left wall */
        void applyLeftWall   ( LBField & lbField, int i, int j );
        void applyRightWall  ( LBField & lbField, int i, int j );
        void applyBottomWall ( LBField & lbField, int i, int j );
        void applyTopWall    ( LBField & lbField, int i, int j );
        /** @} */

        /** @defgroup 3Dfunctions
         * 3D boundary iterator functions
         * @param lbField Reference to the LB field.
         * @param i Position of the cell in the X direction
         * @param j Position of the cell in the Y direction
         * @param k Position of the cell in the Z direction
         * @{
         */
        void applyLeftWall   ( LBField & lbField, int i, int j, int k );
        void applyRightWall  ( LBField & lbField, int i, int j, int k );
        void applyBottomWall ( LBField & lbField, int i, int j, int k );
        void applyTopWall    ( LBField & lbField, int i, int j, int k );
        void applyFrontWall  ( LBField & lbField, int i, int j, int k );
        void applyBackWall   ( LBField & lbField, int i, int j, int k );
        /** @} */
        void setVelocities(const double* velocityX,const double* velocityY,const double* velocityZ,const int velocitySize);
		void setJacobian(const double* jacobian,const int velocitySize);
		void setPressure(const double* pressure,const int velocitySize);
    private:

        LBField & _lbField;

        const int _nsLowX;
        const int _nsHighX;
        const int _nsLowY;
        const int _nsHighY;
        const int _nsLowZ;
        const int _nsHighZ;

        const int _nsSizeX;
        const int _nsSizeY;
        const int _nsSizeZ;

        const int _M;    //! Number of LB cells per NS cells in one dimension
        const FLOAT _floatM;
        const FLOAT _reciprocalM;

        // Variables used for unit conversion
        const FLOAT _dx;
        const FLOAT _dt;
        const FLOAT _reciprocalVelocityLB;  // Ratio instead of velocity. It's faster to multiply

        FLOAT _location[stencilSize];
        FLOAT _derX[stencilSize], _derY[stencilSize], _derZ[stencilSize], _result[stencilSize];
        FLOAT _values[stencilSize];   //! Storage for the adequate values from the field
        FLOAT _meanPressure;    //! Average pressure in the boundary cells

        int _flip[3];
        std::vector<double> _velocities[3];
        std::vector<double>  _pressure;
        std::vector<double>  _jacobian;
		int _velocityIndex;
		int _pressureIndex;
		/** Loads the requested velocity components in the points of the stencil into the private
         * values array.
         * @param i Position of the NS cell containing the point in the X direction.
         * @param j Position of the NS cell containing the point in the Y direction.
         * @param k Position of the NS cell containing the point in the Z direction.
         * @param component Requested component of the velocity (0, 1 or 2 for X, Y or Z resp.)
         * @param offset Array with offsets to translate the interpolation stencil.
         * @param flip Array stating in which directions the stencil has been flipped.
         */
        void loadVelocity(int component);

        /** Loads values of the pressure from the NS field at the points of the stencil into the
         * provate values array.
         * @param i Position of the NS cell in the X direction.
         * @param j Position of the NS cell in the Y direction.
         * @param k Position of the NS cell in the Z direction.
         * @param offset Array with offsets to translate the interpolation stencil.
         * @param flip Array stating in which directions the stencil has been flipped.
         */
        void loadPressure();

        /** From the indexes of a cell in the LB grid, get the indexes and position in the NS grid
         * @param ins Reference of the variable where the x index of the cell NS will be stored.
         * @param jns Reference of the variable where the y index of the cell NS will be stored.
         * @param kns Reference of the variable where the z index of the cell NS will be stored.
         * @param position Array where the position of the LB cell relative to the NS cell are
         * stored. Values are fractions of the length of a NS cell.
         * @param i Index of the LB cell in the LB subdomain in direction x
         * @param j Index of the LB cell in the LB subdomain in direction y
         * @param k Index of the LB cell in the LB subdomain in direction z
         */
        void identifyCellAndPosition (int & ins, int & jns, int & kns,
                                      FLOAT * const position, int i, int j, int k);

        /** @defgroup positionOffsetFunctions
         * These are functions in charge of correctly setting the transformed position and offset
         * vectors required for the interpolation. They set a single component of the vectors.
         * According to the position of the value in the NS cell, the location of the cube [0,1]^3
         * changes and the functions have to consider this. The two functions are used depending on
         * whether the value is centered in the cell in a given direction or not. For example, the
         * pressure values are always centered, since they lie at the center of the cell. In the
         * case of the velocities, two coordinates are centered, and the coordinate where the
         * velocity component points lies on a face instead.
         * We use setRPositionOffset for the centered axes and setRPositionOffsetPrincipal for
         * the axes where the value is in the faces.
         * @{
         */
        /** Sets transformed position and offset vectors.
         * This function decides where the position relative to the non-flipped stencil and the
         * offset.
         * @param flip The vector containing in which directions the stencil will be flipped.
         * @param position Position of the point in the NS cell, as fractions of the length of a
         * NS cell.
         * @param component The component of the velocity to be interpolated.
         * @return transformedPosition The position of the point with respect to the non-flipped
         * representation of the stencil will be stored in this array.
         * @return offset Offset to be applied with the flipped stencil.
         */
        void setRPositionOffset(FLOAT * const transformedPosition, int * const offset,
                                const int * const flip, const FLOAT * const position,
                                int component);

        /** Sets transformed position and offset vectors.
         * This function decides where the position relative to the non-flipped stencil and the
         * offset.
         * @param flip The vector containing in which directions the stencil will be flipped.
         * @param position Position of the point in the NS cell, as fractions of the length of a
         * NS cell.
         * @param component The component of the velocity to be interpolated.
         * @return transformedPosition The position of the point with respect to the non-flipped
         * representation of the stencil will be stored in this array.
         * @return offset Offset to be applied with the flipped stencil.
         */
        void setRPositionOffsetPrincipal (FLOAT * const transformedPosition, int * const offset,
                                          const int * const flip, const FLOAT * const position,
                                          int component);
        /** @} */

        // This functions decides the orientation and position of the stencil as well as the location
        // vector provided a point inside a cell and the required component.
        // The position is provided with respect to the cell and is in [0,1]
        void setArrays (int * const offset, FLOAT * const locationVector,
                        FLOAT * const dxVector, FLOAT * const dyVector, FLOAT * const dzVector,
                        const int * const flip, const FLOAT * const position, int component);
};

#endif
