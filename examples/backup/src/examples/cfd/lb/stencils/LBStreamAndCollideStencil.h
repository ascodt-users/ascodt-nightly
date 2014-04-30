#ifndef LB_STREAM_AND_COLLIDE_STENCIL_H_
#define LB_STREAM_AND_COLLIDE_STENCIL_H_

#include "Parameters.h"
#include "Stencil.h"
#include "LBFunctions.h"
#include "../LBField.h"

class LBStreamAndCollideStencil : public FieldStencil<LBField> {

    public:

        LBStreamAndCollideStencil(const Parameters & parameters);

        void apply(LBField & field, int i, int j);
        void apply(LBField & field, int i, int j, int k);

    private:

        const FLOAT _reciprocalTau;

        FLOAT _f[Q];
        FLOAT _feq[Q];
        FLOAT _density;
        FLOAT _velocity[3];
};

#endif
