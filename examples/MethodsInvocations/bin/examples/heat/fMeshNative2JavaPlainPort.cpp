#include "examples/heat/fMeshNative2JavaPlainPort.h"

JNIEXPORT void JNICALL Java_examples_heat_fMeshNative2JavaPlainPort_createInstance(JNIEnv *env, jobject obj){
  JavaVM* jvm;
  env->GetJavaVM(&jvm);
  jobject self=env->NewGlobalRef(obj);
  
  examples::heat::fMeshNative2JavaPlainPort *ref=new examples::heat::fMeshNative2JavaPlainPort(jvm,self);
  
  jfieldID id =env->GetFieldID(env->GetObjectClass(obj), "_ref", "J");
  env->SetLongField(obj, id, (jlong)ref);
  
}

JNIEXPORT void JNICALL Java_examples_heat_fMeshNative2JavaPlainPort_destroyInstance(JNIEnv *env, jobject obj,jlong ref){
  delete ((examples::heat::fMeshNative2JavaPlainPort*)ref);
  
}

examples::heat::fMeshNative2JavaPlainPort::fMeshNative2JavaPlainPort(JavaVM* jvm,jobject obj):
     _jvm(jvm),
     _obj(obj){

}

examples::heat::fMeshNative2JavaPlainPort::~fMeshNative2JavaPlainPort(){
  JNIEnv* env;
  _jvm->GetEnv((void**)&env,JNI_VERSION_1_6);
  env->DeleteGlobalRef(_obj);
}

void examples::heat::fMeshNative2JavaPlainPort::allocate(const int* dim, const int dim_len){
  JNIEnv* env;
  int status=_jvm->GetEnv((void**)&env,JNI_VERSION_1_6);
  //jfieldID pid =env->GetFieldID(env->GetObjectClass(_obj),_portIdentifier.c_str(), "Lexamples/heat/fMeshDispatcher;");
  //jobject obj= env->GetObjectField(_obj,pid);
  //jclass cls = env->FindClass("Lexamples/heat/fMeshDispatcher;");
  jclass cls=env->GetObjectClass(_obj);
  jmethodID mid = env->GetMethodID(cls,"allocate","([I)V");
  
  if(mid){
     jintArray dim_jni=env->NewIntArray(dim_len);
env->SetIntArrayRegion(dim_jni,0,dim_len,(jint*)dim);

     env->CallVoidMethod(_obj,mid,dim_jni);
     
  }
}
void examples::heat::fMeshNative2JavaPlainPort::copyData(double* data, const int data_len){
  JNIEnv* env;
  int status=_jvm->GetEnv((void**)&env,JNI_VERSION_1_6);
  //jfieldID pid =env->GetFieldID(env->GetObjectClass(_obj),_portIdentifier.c_str(), "Lexamples/heat/fMeshDispatcher;");
  //jobject obj= env->GetObjectField(_obj,pid);
  //jclass cls = env->FindClass("Lexamples/heat/fMeshDispatcher;");
  jclass cls=env->GetObjectClass(_obj);
  jmethodID mid = env->GetMethodID(cls,"copyData","([D)V");
  
  if(mid){
     jdoubleArray data_jni=env->NewDoubleArray(data_len);
env->SetDoubleArrayRegion(data_jni,0,data_len,(jdouble*)data);

     env->CallVoidMethod(_obj,mid,data_jni);
     env->GetDoubleArrayRegion(data_jni,0,data_len,(jdouble*)data);

  }
}
void examples::heat::fMeshNative2JavaPlainPort::getData(void*& handle){
  JNIEnv* env;
  int status=_jvm->GetEnv((void**)&env,JNI_VERSION_1_6);
  //jfieldID pid =env->GetFieldID(env->GetObjectClass(_obj),_portIdentifier.c_str(), "Lexamples/heat/fMeshDispatcher;");
  //jobject obj= env->GetObjectField(_obj,pid);
  //jclass cls = env->FindClass("Lexamples/heat/fMeshDispatcher;");
  jclass cls=env->GetObjectClass(_obj);
  jmethodID mid = env->GetMethodID(cls,"getData","([J)V");
  
  if(mid){
     jlongArray handle_jni=env->NewLongArray(1);
env->SetLongArrayRegion(handle_jni,0,1,(jlong*)&handle);

     env->CallVoidMethod(_obj,mid,handle_jni);
     env->GetLongArrayRegion(handle_jni,0,1,(jlong*)&handle);

  }
}
