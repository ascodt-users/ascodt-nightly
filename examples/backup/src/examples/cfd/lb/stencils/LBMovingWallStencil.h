#ifndef _LB_MOVING_WALL_STENCIL_H_
#define _LB_MOVING_WALL_STENCIL_H_

#include "Parameters.h"
#include "../LBDefinitions.h"
#include "Stencil.h"
#include "../LBField.h"

class LBMovingWallStencil : public GlobalBoundaryStencil<LBField> {

    public:

        LBMovingWallStencil ( const Parameters & parameters );

        void applyLeftWall   ( LBField & field, int i, int j );
        void applyRightWall  ( LBField & field, int i, int j );
        void applyBottomWall ( LBField & field, int i, int j );
        void applyTopWall    ( LBField & field, int i, int j );

        void applyLeftWall   ( LBField & field, int i, int j, int k );
        void applyRightWall  ( LBField & field, int i, int j, int k );
        void applyBottomWall ( LBField & field, int i, int j, int k );
        void applyTopWall    ( LBField & field, int i, int j, int k );
        void applyFrontWall  ( LBField & field, int i, int j, int k );
        void applyBackWall   ( LBField & field, int i, int j, int k );
};

#endif
