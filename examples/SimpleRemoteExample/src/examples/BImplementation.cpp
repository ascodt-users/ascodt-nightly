#include "examples/BImplementation.h"

examples::BImplementation::BImplementation(){

}

examples::BImplementation::~BImplementation(){

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
void examples::BImplementation::bar(const int a,const int b){
    std::cout<<"sum a,b:"<<(a+b)<<std::endl;
}
