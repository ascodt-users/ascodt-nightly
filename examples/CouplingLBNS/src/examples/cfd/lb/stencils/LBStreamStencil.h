#ifndef _LB_STREAM_STENCIL_H_
#define _LB_STREAM_STENCIL_H_

#include "Stencil.h"
#include "../LBField.h"

// To be applied before the collision

class LBStreamStencil : public FieldStencil<LBField> {

    public:

        LBStreamStencil(const Parameters & parameters);

        void apply(LBField & field, int i, int j);
        void apply(LBField & field, int i, int j, int k);
};

#endif
