#include "cca/cfd/DriverNativeDispatcher.h"
#include <algorithm>

#ifdef JAVA
JNIEXPORT void JNICALL Java_cca_cfd_DriverNativeDispatcher_createInstance(JNIEnv *env, jobject obj){
  JavaVM* jvm;
  env->GetJavaVM(&jvm);
  
  cca::cfd::DriverNativeDispatcher *ref=new cca::cfd::DriverNativeDispatcher();
  
  jfieldID id =env->GetFieldID(env->GetObjectClass(obj), "_ref", "J");
  env->SetLongField(obj, id, (jlong)ref);
    
}

JNIEXPORT void JNICALL Java_cca_cfd_DriverNativeDispatcher_destroyInstance(JNIEnv *env, jobject obj,jlong ref){
  delete ((cca::cfd::DriverNativeDispatcher*)ref);
}

JNIEXPORT void JNICALL Java_cca_cfd_DriverNativeDispatcher_connect(JNIEnv *env, jobject obj,jlong ref,jlong destination){
  ((cca::cfd::DriverNativeDispatcher*)ref)->connect((cca::cfd::Driver*)destination);
}

JNIEXPORT void JNICALL Java_cca_cfd_DriverNativeDispatcher_disconnect(JNIEnv *env, jobject obj,jlong ref,jlong destination){
  ((cca::cfd::DriverNativeDispatcher*)ref)->disconnect((cca::cfd::Driver*)destination);
}
#endif

cca::cfd::DriverNativeDispatcher::DriverNativeDispatcher(){

}

cca::cfd::DriverNativeDispatcher::~DriverNativeDispatcher(){

}

void cca::cfd::DriverNativeDispatcher::connect(cca::cfd::Driver* destination){
  if(std::find(_destinations.begin(), _destinations.end(), destination)==_destinations.end())
     _destinations.push_back(destination);
}

void cca::cfd::DriverNativeDispatcher::disconnect(cca::cfd::Driver* destination){
  std::vector<cca::cfd::Driver*>::iterator iter=std::find(_destinations.begin(), _destinations.end(), destination);
  if(iter!=_destinations.end())
     _destinations.erase(iter);
}

bool cca::cfd::DriverNativeDispatcher::isConnected() const{
  return !_destinations.empty();
}


void cca::cfd::DriverNativeDispatcher::go(const std::string configFile){
    for(unsigned int i=0;i<_destinations.size();i++)
          _destinations[i]->go(configFile);
}

void cca::cfd::DriverNativeDispatcher::goParallel(const std::string configFile){
    for(unsigned int i=0;i<_destinations.size();i++)
          _destinations[i]->goParallel(configFile);
}

