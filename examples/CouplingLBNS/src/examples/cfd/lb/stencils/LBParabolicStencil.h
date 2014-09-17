#ifndef _LB_PARABOLIC_STENCIL_H_
#define _LB_PARABOLIC_STENCIL_H_

#include "Stencil.h"
#include "Parameters.h"
#include "../LBField.h"

/** Class used to generate boundaries that contain pressures, velocities and shears corresponding
 * to parabolic channel flow.
 */
class LBParabolicStencil : public GlobalBoundaryStencil<LBField> {

    private:

        const FLOAT _angle;
        const FLOAT _gradRho;

        const FLOAT _cosAngle;
        const FLOAT _sinAngle;

        // This is the factor to the z*(z-d), where d is the distance between the plates.
        const FLOAT _speedFactor;

        // Parameters for the linear functions for the pressure on the walls, in the form
        // P = 1 + L*a*t+v. The 1 to center the pressure there and the L representing side length

        const FLOAT _al;
        const FLOAT _ar;
        const FLOAT _ab;
        const FLOAT _at;

        const FLOAT _bl;
        const FLOAT _br;
        const FLOAT _bb;
        const FLOAT _bt;

        FLOAT _velocity[3];

        FLOAT _equilibrium[19];
        FLOAT _nequilibrium[19];

    public:

        LBParabolicStencil (const Parameters & parameters, FLOAT angle, FLOAT gradRho);

        void applyLeftWall   (LBField & field, int i, int j);
        void applyRightWall  (LBField & field, int i, int j);
        void applyBottomWall (LBField & field, int i, int j);
        void applyTopWall    (LBField & field, int i, int j);

        void applyLeftWall   (LBField & field, int i, int j, int k);
        void applyRightWall  (LBField & field, int i, int j, int k);
        void applyBottomWall (LBField & field, int i, int j, int k);
        void applyTopWall    (LBField & field, int i, int j, int k);
        void applyFrontWall  (LBField & field, int i, int j, int k);
        void applyBackWall   (LBField & field, int i, int j, int k);
};
#endif
