#include "de/tum/ExampleComponentImplementation.h"

de::tum::ExampleComponentImplementation::ExampleComponentImplementation(){
	_data=NULL;
}

de::tum::ExampleComponentImplementation::~ExampleComponentImplementation(){
	if(_data){
		delete []_data;
		_data=NULL;
	}
}
void de::tum::ExampleComponentImplementation::reset(){
	if(_data){
			delete []_data;
			_data=NULL;
		}
}
void de::tum::ExampleComponentImplementation::foo(const double* data, const int data_len){
    if(_data==NULL)
    	_data=new double[data_len];
	for(int i=0;i<data_len;i++)
    	_data[i]=data[i];
}
void de::tum::ExampleComponentImplementation::bar(double* data, const int data_len){
	for(int i=0;i<data_len;i++)
	    	data[i]=_data[i];
}
extern "C" void main_loop_();
int main(){
	main_loop_();
}
