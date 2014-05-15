#ifndef _PARALLEL_MANAGER_H_
#define _PARALLEL_MANAGER_H_


#include "Parameters.h"


/** Iterface for parallel managers, which should take care of communication between processes
 */
template <class FlowField>
class ParallelManager{

    protected:

        FlowField & _flowField;     //! A reference to the flow field
        const Parameters & _parameters;     //! Reference to the parameters

    public:

        ParallelManager(FlowField & flowField, const Parameters & parameters):
            _flowField(flowField), _parameters(parameters)
        {}


};

#endif
