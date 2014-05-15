#include "examples/BImplementation.h"

examples::BImplementation::BImplementation(){

}

examples::BImplementation::~BImplementation(){

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

void examples::BImplementation::bar(const int a,const int b){
    std::cout<<"sum a,b:"<<(a+b)<<std::endl;
}
