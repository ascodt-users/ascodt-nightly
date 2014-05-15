#include "examples/AImplementation.h"

examples::AImplementation::AImplementation(){

}

examples::AImplementation::~AImplementation(){

}

extern "C" void
#ifdef _WIN32
MAIN_LOOP(bool joinable);
#else
main_loop_(bool joinable);
#endif

int main(){
#ifdef _WIN32
  MAIN_LOOP(false);
#else
  main_loop_(false);
#endif
}

void examples::AImplementation::go(){
    if(_fooHandler)
    	_fooHandler->bar(2,3);
}
