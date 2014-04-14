#include "examples/BImplementation.h"

examples::BImplementation::BImplementation(){

}

examples::BImplementation::~BImplementation(){

}
extern "C" void main_loop_();
int main(){
     main_loop_();
}
void examples::BImplementation::bar(const int a,const int b){
    std::cout<<"sum a,b:"<<(a+b)<<std::endl;
}
