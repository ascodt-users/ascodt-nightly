#include "examples/DriverNativeDispatcher.h"
#include <algorithm>

JNIEXPORT void JNICALL Java_examples_DriverNativeDispatcher_createInstance(JNIEnv *env, jobject obj){
  JavaVM* jvm;
  env->GetJavaVM(&jvm);
  
  examples::DriverNativeDispatcher *ref=new examples::DriverNativeDispatcher();
  
  jfieldID id =env->GetFieldID(env->GetObjectClass(obj), "_ref", "J");
  env->SetLongField(obj, id, (jlong)ref);
    
}

JNIEXPORT void JNICALL Java_examples_DriverNativeDispatcher_destroyInstance(JNIEnv *env, jobject obj,jlong ref){
  delete ((examples::DriverNativeDispatcher*)ref);
}

JNIEXPORT void JNICALL Java_examples_DriverNativeDispatcher_connect(JNIEnv *env, jobject obj,jlong ref,jlong destination){
  ((examples::DriverNativeDispatcher*)ref)->connect((examples::Driver*)destination);
}

JNIEXPORT void JNICALL Java_examples_DriverNativeDispatcher_disconnect(JNIEnv *env, jobject obj,jlong ref,jlong destination){
  ((examples::DriverNativeDispatcher*)ref)->disconnect((examples::Driver*)destination);
}


examples::DriverNativeDispatcher::DriverNativeDispatcher(){

}

examples::DriverNativeDispatcher::~DriverNativeDispatcher(){

}

void examples::DriverNativeDispatcher::connect(examples::Driver* destination){
  if(std::find(_destinations.begin(), _destinations.end(), destination)==_destinations.end())
     _destinations.push_back(destination);
}

void examples::DriverNativeDispatcher::disconnect(examples::Driver* destination){
  std::vector<examples::Driver*>::iterator iter=std::find(_destinations.begin(), _destinations.end(), destination);
  if(iter!=_destinations.end())
     _destinations.erase(iter);
}

bool examples::DriverNativeDispatcher::isConnected() const{
  return !_destinations.empty();
}


void examples::DriverNativeDispatcher::go(){
    for(unsigned int i=0;i<_destinations.size();i++)
          _destinations[i]->go();
}

void examples::DriverNativeDispatcher::goParallel(){
    for(unsigned int i=0;i<_destinations.size();i++)
          _destinations[i]->goParallel();
}

