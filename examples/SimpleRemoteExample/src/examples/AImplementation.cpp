#include "examples/AImplementation.h"

examples::AImplementation::AImplementation(){

}

examples::AImplementation::~AImplementation(){

}

extern "C" void main_loop_();
int main(){
     main_loop_();
}

void examples::AImplementation::go(){
    if(_fooHandler)
    	_fooHandler->bar(2,3);
}
