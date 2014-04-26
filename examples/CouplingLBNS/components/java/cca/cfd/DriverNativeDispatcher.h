#ifndef CCA_CFD_DRIVERNATIVEDISPATCHER_H_
#define CCA_CFD_DRIVERNATIVEDISPATCHER_H_ 

#include "cca/cfd/Driver.h"
#include <iostream>
#include <vector>

namespace cca { 
namespace cfd { 
  
     class DriverNativeDispatcher;
} 
}

#include <jni.h> 

#ifdef __cplusplus
  extern "C" {
#endif


          
JNIEXPORT void JNICALL Java_cca_cfd_DriverNativeDispatcher_createInstance(JNIEnv *env, jobject obj);
JNIEXPORT void JNICALL Java_cca_cfd_DriverNativeDispatcher_destroyInstance(JNIEnv *env, jobject obj,jlong ref);
JNIEXPORT void JNICALL Java_cca_cfd_DriverNativeDispatcher_connect(JNIEnv *env, jobject obj,jlong ref,jlong port);
JNIEXPORT void JNICALL Java_cca_cfd_DriverNativeDispatcher_disconnect(JNIEnv *env, jobject obj,jlong ref,jlong port);


#ifdef __cplusplus
  }
#endif

class cca::cfd::DriverNativeDispatcher: public cca::cfd::Driver{
  protected:
    std::vector<cca::cfd::Driver*> _destinations;
  public:
    DriverNativeDispatcher();
    virtual ~DriverNativeDispatcher();
    
    void connect(cca::cfd::Driver* ref);
    void disconnect(cca::cfd::Driver* ref);
    bool isConnected() const;
    void go(const std::string configFile);  
    void goParallel(const std::string configFile);
   
};

#endif
