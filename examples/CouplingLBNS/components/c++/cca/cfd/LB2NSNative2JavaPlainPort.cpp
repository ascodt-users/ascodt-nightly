#include "cca/cfd/LB2NSNative2JavaPlainPort.h"

JNIEXPORT void JNICALL Java_cca_cfd_LB2NSNative2JavaPlainPort_createInstance(JNIEnv *env, jobject obj){
  JavaVM* jvm;
  env->GetJavaVM(&jvm);
  jobject self=env->NewGlobalRef(obj);
  
  cca::cfd::LB2NSNative2JavaPlainPort *ref=new cca::cfd::LB2NSNative2JavaPlainPort(jvm,self);
  
  jfieldID id =env->GetFieldID(env->GetObjectClass(obj), "_ref", "J");
  env->SetLongField(obj, id, (jlong)ref);
  
}

JNIEXPORT void JNICALL Java_cca_cfd_LB2NSNative2JavaPlainPort_destroyInstance(JNIEnv *env, jobject obj,jlong ref){
  delete ((cca::cfd::LB2NSNative2JavaPlainPort*)ref);
  
}

cca::cfd::LB2NSNative2JavaPlainPort::LB2NSNative2JavaPlainPort(JavaVM* jvm,jobject obj):
     _jvm(jvm),
     _obj(obj){

}

cca::cfd::LB2NSNative2JavaPlainPort::~LB2NSNative2JavaPlainPort(){
  JNIEnv* env;
  _jvm->GetEnv((void**)&env,JNI_VERSION_1_6);
  env->DeleteGlobalRef(_obj);
}

void cca::cfd::LB2NSNative2JavaPlainPort::iterateBoundary(){
  JNIEnv* env;
  int status=_jvm->GetEnv((void**)&env,JNI_VERSION_1_6);
  jclass cls=env->GetObjectClass(_obj);
  jmethodID mid = env->GetMethodID(cls,"iterateBoundary","()V");
  
  if(mid){
     
     env->CallVoidMethod(_obj,mid);
     
  }
}
void cca::cfd::LB2NSNative2JavaPlainPort::iterateBoundaryParallel(){
  JNIEnv* env;
  int status=_jvm->GetEnv((void**)&env,JNI_VERSION_1_6);
  jclass cls=env->GetObjectClass(_obj);
  jmethodID mid = env->GetMethodID(cls,"iterateBoundaryParallel","()V");
  
  if(mid){
     
     env->CallVoidMethod(_obj,mid);
     
  }
}
void cca::cfd::LB2NSNative2JavaPlainPort::iterateInner(){
  JNIEnv* env;
  int status=_jvm->GetEnv((void**)&env,JNI_VERSION_1_6);
  jclass cls=env->GetObjectClass(_obj);
  jmethodID mid = env->GetMethodID(cls,"iterateInner","()V");
  
  if(mid){
     
     env->CallVoidMethod(_obj,mid);
     
  }
}
void cca::cfd::LB2NSNative2JavaPlainPort::iterateInnerParallel(){
  JNIEnv* env;
  int status=_jvm->GetEnv((void**)&env,JNI_VERSION_1_6);
  jclass cls=env->GetObjectClass(_obj);
  jmethodID mid = env->GetMethodID(cls,"iterateInnerParallel","()V");
  
  if(mid){
     
     env->CallVoidMethod(_obj,mid);
     
  }
}
void cca::cfd::LB2NSNative2JavaPlainPort::retrieveTimestep(double& dt){
  JNIEnv* env;
  int status=_jvm->GetEnv((void**)&env,JNI_VERSION_1_6);
  jclass cls=env->GetObjectClass(_obj);
  jmethodID mid = env->GetMethodID(cls,"retrieveTimestep","([D)V");
  
  if(mid){
     jdoubleArray dt_jni=env->NewDoubleArray(1);
env->SetDoubleArrayRegion(dt_jni,0,1,(jdouble*)&dt);

     env->CallVoidMethod(_obj,mid,dt_jni);
     env->GetDoubleArrayRegion(dt_jni,0,1,(jdouble*)&dt);

  }
}
void cca::cfd::LB2NSNative2JavaPlainPort::retrieveTimestepParallel(double& dt){
  JNIEnv* env;
  int status=_jvm->GetEnv((void**)&env,JNI_VERSION_1_6);
  jclass cls=env->GetObjectClass(_obj);
  jmethodID mid = env->GetMethodID(cls,"retrieveTimestepParallel","([D)V");
  
  if(mid){
     jdoubleArray dt_jni=env->NewDoubleArray(1);
env->SetDoubleArrayRegion(dt_jni,0,1,(jdouble*)&dt);

     env->CallVoidMethod(_obj,mid,dt_jni);
     env->GetDoubleArrayRegion(dt_jni,0,1,(jdouble*)&dt);

  }
}
void cca::cfd::LB2NSNative2JavaPlainPort::retrieveVelocitiesSize(int& memoryX,int& memoryY,int& memoryZ){
  JNIEnv* env;
  int status=_jvm->GetEnv((void**)&env,JNI_VERSION_1_6);
  jclass cls=env->GetObjectClass(_obj);
  jmethodID mid = env->GetMethodID(cls,"retrieveVelocitiesSize","([I[I[I)V");
  
  if(mid){
     jintArray memoryX_jni=env->NewIntArray(1);
env->SetIntArrayRegion(memoryX_jni,0,1,(jint*)&memoryX);
jintArray memoryY_jni=env->NewIntArray(1);
env->SetIntArrayRegion(memoryY_jni,0,1,(jint*)&memoryY);
jintArray memoryZ_jni=env->NewIntArray(1);
env->SetIntArrayRegion(memoryZ_jni,0,1,(jint*)&memoryZ);

     env->CallVoidMethod(_obj,mid,memoryX_jni,memoryY_jni,memoryZ_jni);
     env->GetIntArrayRegion(memoryX_jni,0,1,(jint*)&memoryX);
env->GetIntArrayRegion(memoryY_jni,0,1,(jint*)&memoryY);
env->GetIntArrayRegion(memoryZ_jni,0,1,(jint*)&memoryZ);

  }
}
void cca::cfd::LB2NSNative2JavaPlainPort::retrieveVelocitiesSizeParallel(int& memoryX,int& memoryY,int& memoryZ){
  JNIEnv* env;
  int status=_jvm->GetEnv((void**)&env,JNI_VERSION_1_6);
  jclass cls=env->GetObjectClass(_obj);
  jmethodID mid = env->GetMethodID(cls,"retrieveVelocitiesSizeParallel","([I[I[I)V");
  
  if(mid){
     jintArray memoryX_jni=env->NewIntArray(1);
env->SetIntArrayRegion(memoryX_jni,0,1,(jint*)&memoryX);
jintArray memoryY_jni=env->NewIntArray(1);
env->SetIntArrayRegion(memoryY_jni,0,1,(jint*)&memoryY);
jintArray memoryZ_jni=env->NewIntArray(1);
env->SetIntArrayRegion(memoryZ_jni,0,1,(jint*)&memoryZ);

     env->CallVoidMethod(_obj,mid,memoryX_jni,memoryY_jni,memoryZ_jni);
     env->GetIntArrayRegion(memoryX_jni,0,1,(jint*)&memoryX);
env->GetIntArrayRegion(memoryY_jni,0,1,(jint*)&memoryY);
env->GetIntArrayRegion(memoryZ_jni,0,1,(jint*)&memoryZ);

  }
}
void cca::cfd::LB2NSNative2JavaPlainPort::retrieveVelocitiesCopy(double* velocityX, const int velocityX_len,double* velocityY, const int velocityY_len,double* velocityZ, const int velocityZ_len){
  JNIEnv* env;
  int status=_jvm->GetEnv((void**)&env,JNI_VERSION_1_6);
  jclass cls=env->GetObjectClass(_obj);
  jmethodID mid = env->GetMethodID(cls,"retrieveVelocitiesCopy","([D[D[D)V");
  
  if(mid){
     jdoubleArray velocityX_jni=env->NewDoubleArray(velocityX_len);
env->SetDoubleArrayRegion(velocityX_jni,0,velocityX_len,(jdouble*)velocityX);
jdoubleArray velocityY_jni=env->NewDoubleArray(velocityY_len);
env->SetDoubleArrayRegion(velocityY_jni,0,velocityY_len,(jdouble*)velocityY);
jdoubleArray velocityZ_jni=env->NewDoubleArray(velocityZ_len);
env->SetDoubleArrayRegion(velocityZ_jni,0,velocityZ_len,(jdouble*)velocityZ);

     env->CallVoidMethod(_obj,mid,velocityX_jni,velocityY_jni,velocityZ_jni);
     env->GetDoubleArrayRegion(velocityX_jni,0,velocityX_len,(jdouble*)velocityX);
env->GetDoubleArrayRegion(velocityY_jni,0,velocityY_len,(jdouble*)velocityY);
env->GetDoubleArrayRegion(velocityZ_jni,0,velocityZ_len,(jdouble*)velocityZ);

  }
}
void cca::cfd::LB2NSNative2JavaPlainPort::retrieveVelocitiesCopyParallel(double* velocityX, const int velocityX_len,double* velocityY, const int velocityY_len,double* velocityZ, const int velocityZ_len){
  JNIEnv* env;
  int status=_jvm->GetEnv((void**)&env,JNI_VERSION_1_6);
  jclass cls=env->GetObjectClass(_obj);
  jmethodID mid = env->GetMethodID(cls,"retrieveVelocitiesCopyParallel","([D[D[D)V");
  
  if(mid){
     jdoubleArray velocityX_jni=env->NewDoubleArray(velocityX_len);
env->SetDoubleArrayRegion(velocityX_jni,0,velocityX_len,(jdouble*)velocityX);
jdoubleArray velocityY_jni=env->NewDoubleArray(velocityY_len);
env->SetDoubleArrayRegion(velocityY_jni,0,velocityY_len,(jdouble*)velocityY);
jdoubleArray velocityZ_jni=env->NewDoubleArray(velocityZ_len);
env->SetDoubleArrayRegion(velocityZ_jni,0,velocityZ_len,(jdouble*)velocityZ);

     env->CallVoidMethod(_obj,mid,velocityX_jni,velocityY_jni,velocityZ_jni);
     env->GetDoubleArrayRegion(velocityX_jni,0,velocityX_len,(jdouble*)velocityX);
env->GetDoubleArrayRegion(velocityY_jni,0,velocityY_len,(jdouble*)velocityY);
env->GetDoubleArrayRegion(velocityZ_jni,0,velocityZ_len,(jdouble*)velocityZ);

  }
}
