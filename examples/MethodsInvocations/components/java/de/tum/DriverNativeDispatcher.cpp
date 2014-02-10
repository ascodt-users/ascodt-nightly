#include "de/tum/DriverNativeDispatcher.h"
#include <algorithm>

JNIEXPORT void JNICALL Java_de_tum_DriverNativeDispatcher_createInstance(JNIEnv *env, jobject obj){
  JavaVM* jvm;
  env->GetJavaVM(&jvm);
  
  de::tum::DriverNativeDispatcher *ref=new de::tum::DriverNativeDispatcher();
  
  jfieldID id =env->GetFieldID(env->GetObjectClass(obj), "_ref", "J");
  env->SetLongField(obj, id, (jlong)ref);
    
}

JNIEXPORT void JNICALL Java_de_tum_DriverNativeDispatcher_destroyInstance(JNIEnv *env, jobject obj,jlong ref){
  delete ((de::tum::DriverNativeDispatcher*)ref);
}

JNIEXPORT void JNICALL Java_de_tum_DriverNativeDispatcher_connect(JNIEnv *env, jobject obj,jlong ref,jlong destination){
  ((de::tum::DriverNativeDispatcher*)ref)->connect((de::tum::Driver*)destination);
}

JNIEXPORT void JNICALL Java_de_tum_DriverNativeDispatcher_disconnect(JNIEnv *env, jobject obj,jlong ref,jlong destination){
  ((de::tum::DriverNativeDispatcher*)ref)->disconnect((de::tum::Driver*)destination);
}


de::tum::DriverNativeDispatcher::DriverNativeDispatcher(){

}

de::tum::DriverNativeDispatcher::~DriverNativeDispatcher(){

}

void de::tum::DriverNativeDispatcher::connect(de::tum::Driver* destination){
  if(std::find(_destinations.begin(), _destinations.end(), destination)==_destinations.end())
     _destinations.push_back(destination);
}

void de::tum::DriverNativeDispatcher::disconnect(de::tum::Driver* destination){
  std::vector<de::tum::Driver*>::iterator iter=std::find(_destinations.begin(), _destinations.end(), destination);
  if(iter!=_destinations.end())
     _destinations.erase(iter);
}

bool de::tum::DriverNativeDispatcher::isConnected() const{
  return !_destinations.empty();
}


void de::tum::DriverNativeDispatcher::go(){
    for(unsigned int i=0;i<_destinations.size();i++)
          _destinations[i]->go();
}

