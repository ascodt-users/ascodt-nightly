#include "examples/heat/RegularGridNative2JavaPlainPort.h"

JNIEXPORT void JNICALL Java_examples_heat_RegularGridNative2JavaPlainPort_createInstance(JNIEnv *env, jobject obj){
  JavaVM* jvm;
  env->GetJavaVM(&jvm);
  jobject self=env->NewGlobalRef(obj);
  
  examples::heat::RegularGridNative2JavaPlainPort *ref=new examples::heat::RegularGridNative2JavaPlainPort(jvm,self);
  
  jfieldID id =env->GetFieldID(env->GetObjectClass(obj), "_ref", "J");
  env->SetLongField(obj, id, (jlong)ref);
  
}

JNIEXPORT void JNICALL Java_examples_heat_RegularGridNative2JavaPlainPort_destroyInstance(JNIEnv *env, jobject obj,jlong ref){
  delete ((examples::heat::RegularGridNative2JavaPlainPort*)ref);
  
}

examples::heat::RegularGridNative2JavaPlainPort::RegularGridNative2JavaPlainPort(JavaVM* jvm,jobject obj):
     _jvm(jvm),
     _obj(obj){

}

examples::heat::RegularGridNative2JavaPlainPort::~RegularGridNative2JavaPlainPort(){
  JNIEnv* env;
  _jvm->GetEnv((void**)&env,JNI_VERSION_1_6);
  env->DeleteGlobalRef(_obj);
}

void examples::heat::RegularGridNative2JavaPlainPort::setOffset(const double* offset, const int offset_len){
  JNIEnv* env;
  int status=_jvm->GetEnv((void**)&env,JNI_VERSION_1_6);
  //jfieldID pid =env->GetFieldID(env->GetObjectClass(_obj),_portIdentifier.c_str(), "Lexamples/heat/RegularGridDispatcher;");
  //jobject obj= env->GetObjectField(_obj,pid);
  //jclass cls = env->FindClass("Lexamples/heat/RegularGridDispatcher;");
  jclass cls=env->GetObjectClass(_obj);
  jmethodID mid = env->GetMethodID(cls,"setOffset","([D)V");
  
  if(mid){
     jdoubleArray offset_jni=env->NewDoubleArray(offset_len);
env->SetDoubleArrayRegion(offset_jni,0,offset_len,(jdouble*)offset);

     env->CallVoidMethod(_obj,mid,offset_jni);
     
  }
}
void examples::heat::RegularGridNative2JavaPlainPort::setDomain(const double* domain, const int domain_len){
  JNIEnv* env;
  int status=_jvm->GetEnv((void**)&env,JNI_VERSION_1_6);
  //jfieldID pid =env->GetFieldID(env->GetObjectClass(_obj),_portIdentifier.c_str(), "Lexamples/heat/RegularGridDispatcher;");
  //jobject obj= env->GetObjectField(_obj,pid);
  //jclass cls = env->FindClass("Lexamples/heat/RegularGridDispatcher;");
  jclass cls=env->GetObjectClass(_obj);
  jmethodID mid = env->GetMethodID(cls,"setDomain","([D)V");
  
  if(mid){
     jdoubleArray domain_jni=env->NewDoubleArray(domain_len);
env->SetDoubleArrayRegion(domain_jni,0,domain_len,(jdouble*)domain);

     env->CallVoidMethod(_obj,mid,domain_jni);
     
  }
}
void examples::heat::RegularGridNative2JavaPlainPort::setDimensions(const int* dimensions, const int dimensions_len){
  JNIEnv* env;
  int status=_jvm->GetEnv((void**)&env,JNI_VERSION_1_6);
  //jfieldID pid =env->GetFieldID(env->GetObjectClass(_obj),_portIdentifier.c_str(), "Lexamples/heat/RegularGridDispatcher;");
  //jobject obj= env->GetObjectField(_obj,pid);
  //jclass cls = env->FindClass("Lexamples/heat/RegularGridDispatcher;");
  jclass cls=env->GetObjectClass(_obj);
  jmethodID mid = env->GetMethodID(cls,"setDimensions","([I)V");
  
  if(mid){
     jintArray dimensions_jni=env->NewIntArray(dimensions_len);
env->SetIntArrayRegion(dimensions_jni,0,dimensions_len,(jint*)dimensions);

     env->CallVoidMethod(_obj,mid,dimensions_jni);
     
  }
}
void examples::heat::RegularGridNative2JavaPlainPort::addCellScalars(const std::string variableName,const double* scalars, const int scalars_len){
  JNIEnv* env;
  int status=_jvm->GetEnv((void**)&env,JNI_VERSION_1_6);
  //jfieldID pid =env->GetFieldID(env->GetObjectClass(_obj),_portIdentifier.c_str(), "Lexamples/heat/RegularGridDispatcher;");
  //jobject obj= env->GetObjectField(_obj,pid);
  //jclass cls = env->FindClass("Lexamples/heat/RegularGridDispatcher;");
  jclass cls=env->GetObjectClass(_obj);
  jmethodID mid = env->GetMethodID(cls,"addCellScalars","(Ljava/lang/String;[D)V");
  
  if(mid){
     jobject variableName_jni=env->NewStringUTF(variableName.c_str());
jdoubleArray scalars_jni=env->NewDoubleArray(scalars_len);
env->SetDoubleArrayRegion(scalars_jni,0,scalars_len,(jdouble*)scalars);

     env->CallVoidMethod(_obj,mid,variableName_jni,scalars_jni);
     
  }
}
void examples::heat::RegularGridNative2JavaPlainPort::render(){
  JNIEnv* env;
  int status=_jvm->GetEnv((void**)&env,JNI_VERSION_1_6);
  //jfieldID pid =env->GetFieldID(env->GetObjectClass(_obj),_portIdentifier.c_str(), "Lexamples/heat/RegularGridDispatcher;");
  //jobject obj= env->GetObjectField(_obj,pid);
  //jclass cls = env->FindClass("Lexamples/heat/RegularGridDispatcher;");
  jclass cls=env->GetObjectClass(_obj);
  jmethodID mid = env->GetMethodID(cls,"render","()V");
  
  if(mid){
     
     env->CallVoidMethod(_obj,mid);
     
  }
}
