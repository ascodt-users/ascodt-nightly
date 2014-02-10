#include "examples/heat/DriverNativeDispatcher.h"
#include <algorithm>

JNIEXPORT void JNICALL Java_examples_heat_DriverNativeDispatcher_createInstance(JNIEnv *env, jobject obj){
  JavaVM* jvm;
  env->GetJavaVM(&jvm);
  
  examples::heat::DriverNativeDispatcher *ref=new examples::heat::DriverNativeDispatcher();
  
  jfieldID id =env->GetFieldID(env->GetObjectClass(obj), "_ref", "J");
  env->SetLongField(obj, id, (jlong)ref);
    
}

JNIEXPORT void JNICALL Java_examples_heat_DriverNativeDispatcher_destroyInstance(JNIEnv *env, jobject obj,jlong ref){
  delete ((examples::heat::DriverNativeDispatcher*)ref);
}

JNIEXPORT void JNICALL Java_examples_heat_DriverNativeDispatcher_connect(JNIEnv *env, jobject obj,jlong ref,jlong destination){
  ((examples::heat::DriverNativeDispatcher*)ref)->connect((examples::heat::Driver*)destination);
}

JNIEXPORT void JNICALL Java_examples_heat_DriverNativeDispatcher_disconnect(JNIEnv *env, jobject obj,jlong ref,jlong destination){
  ((examples::heat::DriverNativeDispatcher*)ref)->disconnect((examples::heat::Driver*)destination);
}


examples::heat::DriverNativeDispatcher::DriverNativeDispatcher(){

}

examples::heat::DriverNativeDispatcher::~DriverNativeDispatcher(){

}

void examples::heat::DriverNativeDispatcher::connect(examples::heat::Driver* destination){
  if(std::find(_destinations.begin(), _destinations.end(), destination)==_destinations.end())
     _destinations.push_back(destination);
}

void examples::heat::DriverNativeDispatcher::disconnect(examples::heat::Driver* destination){
  std::vector<examples::heat::Driver*>::iterator iter=std::find(_destinations.begin(), _destinations.end(), destination);
  if(iter!=_destinations.end())
     _destinations.erase(iter);
}

bool examples::heat::DriverNativeDispatcher::isConnected() const{
  return !_destinations.empty();
}


void examples::heat::DriverNativeDispatcher::go(){
    for(unsigned int i=0;i<_destinations.size();i++)
          _destinations[i]->go();
}

