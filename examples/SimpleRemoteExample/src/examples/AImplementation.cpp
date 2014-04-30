#include "examples/AImplementation.h"

examples::AImplementation::AImplementation(){

}

examples::AImplementation::~AImplementation(){

}

#ifdef _WIN32
extern "C" void MAIN_LOOP();
#else
extern "C" void main_loop_();
#endif


int main(){
#ifdef _WIN32
MAIN_LOOP();
#else
main_loop_();
#endif
}

void examples::AImplementation::go(){
    if(_fooHandler)
    	_fooHandler->bar(2,3);
}
