#ifndef _LB_COLLIDE_STENCIL_H_
#define _LB_COLLIDE_STENCIL_H_

#include "Stencil.h"
#include "../LBField.h"
#include "LBFunctions.h"

class LBCollideStencil : public FieldStencil<LBField> {

    private:

        FLOAT _equilibrium[Q];
        FLOAT _f[Q];
        FLOAT _velocity[3];

        FLOAT _density;


    public:

        LBCollideStencil(const Parameters & parameters);

        void apply(LBField & field, int i, int j);
        void apply(LBField & field, int i, int j, int k);
};

#endif
