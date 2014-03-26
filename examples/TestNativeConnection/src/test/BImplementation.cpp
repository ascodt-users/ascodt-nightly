#include "test/BImplementation.h"

test::BImplementation::BImplementation(){

}

test::BImplementation::~BImplementation(){

}
/*
uncomment for remote applications
extern "C" void main_loop_();
int main(){
     main_loop_();
}
*/
void test::BImplementation::bar(){
     // @todo Insert your code here
	std::cout<<"calling bar"<<std::endl;
}
