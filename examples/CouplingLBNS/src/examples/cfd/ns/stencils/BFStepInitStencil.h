#ifndef _BF_STEP_INIT_STENCIL_H_
#define _BF_STEP_INIT_STENCIL_H_

#include "Stencil.h"
#include "../FlowField.h"
#include "Definitions.h"

class BFStepInitStencil : public FieldStencil<FlowField> {
    public:

        BFStepInitStencil (const Parameters & parameters);

        void apply(FlowField & flowField, int i, int j);
        void apply(FlowField & flowField, int i, int j, int k);

    private:

        const int xLimit;   //! Cells up to and including this will be set as obstacles
        const int yLimit;   //! Same as for x
};

#endif
