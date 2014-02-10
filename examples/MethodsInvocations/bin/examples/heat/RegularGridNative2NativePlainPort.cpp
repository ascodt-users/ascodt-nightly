#include "examples/heat/RegularGridNative2NativePlainPort.h"
#include <assert.h>


JNIEXPORT void JNICALL Java_examples_heat_RegularGridNative2NativePlainPort_createInstance(JNIEnv *env, jobject obj){
  JavaVM* jvm;
  env->GetJavaVM(&jvm);
  
  examples::heat::RegularGridNative2NativePlainPort *ref=new examples::heat::RegularGridNative2NativePlainPort();
  
  jfieldID id =env->GetFieldID(env->GetObjectClass(obj), "_ref", "J");
  env->SetLongField(obj, id, (jlong)ref);
    
}

JNIEXPORT void JNICALL Java_examples_heat_RegularGridNative2NativePlainPort_destroyInstance(JNIEnv *env, jobject obj,jlong ref){
  delete ((examples::heat::RegularGridNative2NativePlainPort*)ref);
}

JNIEXPORT void JNICALL Java_examples_heat_RegularGridNative2NativePlainPort_connect(JNIEnv *env, jobject obj,jlong ref,jlong destination){
  ((examples::heat::RegularGridNative2NativePlainPort*)ref)->connect((examples::heat::RegularGrid*)destination);
}


examples::heat::RegularGridNative2NativePlainPort::RegularGridNative2NativePlainPort():
     _destination(0){

}

examples::heat::RegularGridNative2NativePlainPort::~RegularGridNative2NativePlainPort(){

}

void examples::heat::RegularGridNative2NativePlainPort::connect(examples::heat::RegularGrid* destination){
  _destination=destination;
}
void examples::heat::RegularGridNative2NativePlainPort::setOffset(const double* offset, const int offset_len){
     assert(_destination!=NULL);
     _destination->setOffset(offset,offset_len);
}
void examples::heat::RegularGridNative2NativePlainPort::setDomain(const double* domain, const int domain_len){
     assert(_destination!=NULL);
     _destination->setDomain(domain,domain_len);
}
void examples::heat::RegularGridNative2NativePlainPort::setDimensions(const int* dimensions, const int dimensions_len){
     assert(_destination!=NULL);
     _destination->setDimensions(dimensions,dimensions_len);
}
void examples::heat::RegularGridNative2NativePlainPort::addCellScalars(const std::string variableName,const double* scalars, const int scalars_len){
     assert(_destination!=NULL);
     _destination->addCellScalars(variableName,scalars,scalars_len);
}
void examples::heat::RegularGridNative2NativePlainPort::render(){
     assert(_destination!=NULL);
     _destination->render();
}

