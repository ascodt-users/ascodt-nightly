#include "de/tum/DriverComponentImplementation.h"
#include <math.h>
#include <iostream>
#include <fstream>
#include <sys/time.h>
de::tum::DriverComponentImplementation::DriverComponentImplementation(){

}

de::tum::DriverComponentImplementation::~DriverComponentImplementation(){

}

void de::tum::DriverComponentImplementation::go(){
	std::cout<<"Driver component test empty call started"<<std::endl;
    std::cout<<"Driver component test started"<<std::endl;
    double time = 0.0;
    timeval t1, t2;
    double elapsedTime;
    for(int j=0;j<10000;j++){
    			 //auto start = std::chrono::system_clock::now();
    			gettimeofday(&t1, NULL);
    			_uPort->reset();
    			gettimeofday(&t2, NULL);
    			elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;      // sec to ms
    			elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;   // us to ms
    			time+= elapsedTime;
     }
     time = time/10000.0;
     std::cout << "empty "<<":"<<time<<std::endl;
    		//delete []data;
    for(int i=2;i<21;i++){
		int data_len=pow(2,i);
		time = 0.0;
		double *data = new double [data_len];
		_uPort->reset();
		for(int j=0;j<data_len;j++)
			data[i]=2.3;

		for(int j=0;j<10000;j++){
			 //auto start = std::chrono::system_clock::now();
			gettimeofday(&t1, NULL);
			_uPort->foo(data,data_len);
			_uPort->bar(data,data_len);
			gettimeofday(&t2, NULL);
			elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;      // sec to ms
			elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;   // us to ms
			time+= elapsedTime;
		}
		time = time/10000.0;
		std::cout << "time "<<"2^"<<i<<":"<<time<<std::endl;
		delete []data;
    }



}
extern "C" void main_loop_();
int main(){
	main_loop_();
}
