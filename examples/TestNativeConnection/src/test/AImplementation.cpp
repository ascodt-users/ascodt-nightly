#include "test/AImplementation.h"

test::AImplementation::AImplementation(){

}

test::AImplementation::~AImplementation(){

}
/*
uncomment for remote applications
extern "C" void main_loop_();
int main(){
     main_loop_();
}
*/
void test::AImplementation::bar(){
    if(_foo)
    	_foo->bar();
}
