#ifndef _LB_BOUNCE_BACK_STENCIL_H_
#define _LB_BOUNCE_BACK_STENCIL_H_

#include "Parameters.h"
#include "../LBDefinitions.h"
#include "Stencil.h"
#include "../LBField.h"

class LBBounceBackStencil : public FieldStencil<LBField> {

    public:

	LBBounceBackStencil ( const Parameters & parameters );

        void apply(LBField & field, int i, int j);
        void apply(LBField & field, int i, int j, int k);
};

#endif
