#include "cca/cfd/NS2LBNative2JavaPlainPort.h"

#ifdef JAVA

JNIEXPORT void JNICALL Java_cca_cfd_NS2LBNative2JavaPlainPort_createInstance(JNIEnv *env, jobject obj){
  JavaVM* jvm;
  env->GetJavaVM(&jvm);
  jobject self=env->NewGlobalRef(obj);
  
  cca::cfd::NS2LBNative2JavaPlainPort *ref=new cca::cfd::NS2LBNative2JavaPlainPort(jvm,self);
  
  jfieldID id =env->GetFieldID(env->GetObjectClass(obj), "_ref", "J");
  env->SetLongField(obj, id, (jlong)ref);
  
}

JNIEXPORT void JNICALL Java_cca_cfd_NS2LBNative2JavaPlainPort_destroyInstance(JNIEnv *env, jobject obj,jlong ref){
  delete ((cca::cfd::NS2LBNative2JavaPlainPort*)ref);
  
}



cca::cfd::NS2LBNative2JavaPlainPort::NS2LBNative2JavaPlainPort(JavaVM* jvm,jobject obj):
     _jvm(jvm),
     _obj(obj){

}

cca::cfd::NS2LBNative2JavaPlainPort::~NS2LBNative2JavaPlainPort(){
  JNIEnv* env;
  _jvm->GetEnv((void**)&env,JNI_VERSION_1_6);
  env->DeleteGlobalRef(_obj);
}

void cca::cfd::NS2LBNative2JavaPlainPort::iterate(){
  JNIEnv* env;
  int status=_jvm->GetEnv((void**)&env,JNI_VERSION_1_6);
  jclass cls=env->GetObjectClass(_obj);
  jmethodID mid = env->GetMethodID(cls,"iterate","()V");
  
  if(mid){
     
     env->CallVoidMethod(_obj,mid);
     
  }
}
void cca::cfd::NS2LBNative2JavaPlainPort::iterateParallel(){
  JNIEnv* env;
  int status=_jvm->GetEnv((void**)&env,JNI_VERSION_1_6);
  jclass cls=env->GetObjectClass(_obj);
  jmethodID mid = env->GetMethodID(cls,"iterateParallel","()V");
  
  if(mid){
     
     env->CallVoidMethod(_obj,mid);
     
  }
}
void cca::cfd::NS2LBNative2JavaPlainPort::retrieveTimestep(double& timestep){
  JNIEnv* env;
  int status=_jvm->GetEnv((void**)&env,JNI_VERSION_1_6);
  jclass cls=env->GetObjectClass(_obj);
  jmethodID mid = env->GetMethodID(cls,"retrieveTimestep","([D)V");
  
  if(mid){
     jdoubleArray timestep_jni=env->NewDoubleArray(1);
env->SetDoubleArrayRegion(timestep_jni,0,1,(jdouble*)&timestep);

     env->CallVoidMethod(_obj,mid,timestep_jni);
     env->GetDoubleArrayRegion(timestep_jni,0,1,(jdouble*)&timestep);

  }
}
void cca::cfd::NS2LBNative2JavaPlainPort::retrieveTimestepParallel(double& timestep){
  JNIEnv* env;
  int status=_jvm->GetEnv((void**)&env,JNI_VERSION_1_6);
  jclass cls=env->GetObjectClass(_obj);
  jmethodID mid = env->GetMethodID(cls,"retrieveTimestepParallel","([D)V");
  
  if(mid){
     jdoubleArray timestep_jni=env->NewDoubleArray(1);
env->SetDoubleArrayRegion(timestep_jni,0,1,(jdouble*)&timestep);

     env->CallVoidMethod(_obj,mid,timestep_jni);
     env->GetDoubleArrayRegion(timestep_jni,0,1,(jdouble*)&timestep);

  }
}
void cca::cfd::NS2LBNative2JavaPlainPort::retrieveVelocitiesSize(int& memory){
  JNIEnv* env;
  int status=_jvm->GetEnv((void**)&env,JNI_VERSION_1_6);
  jclass cls=env->GetObjectClass(_obj);
  jmethodID mid = env->GetMethodID(cls,"retrieveVelocitiesSize","([I)V");
  
  if(mid){
     jintArray memory_jni=env->NewIntArray(1);
env->SetIntArrayRegion(memory_jni,0,1,(jint*)&memory);

     env->CallVoidMethod(_obj,mid,memory_jni);
     env->GetIntArrayRegion(memory_jni,0,1,(jint*)&memory);

  }
}
void cca::cfd::NS2LBNative2JavaPlainPort::retrieveVelocitiesSizeParallel(int& memory){
  JNIEnv* env;
  int status=_jvm->GetEnv((void**)&env,JNI_VERSION_1_6);
  jclass cls=env->GetObjectClass(_obj);
  jmethodID mid = env->GetMethodID(cls,"retrieveVelocitiesSizeParallel","([I)V");
  
  if(mid){
     jintArray memory_jni=env->NewIntArray(1);
env->SetIntArrayRegion(memory_jni,0,1,(jint*)&memory);

     env->CallVoidMethod(_obj,mid,memory_jni);
     env->GetIntArrayRegion(memory_jni,0,1,(jint*)&memory);

  }
}
void cca::cfd::NS2LBNative2JavaPlainPort::retrieveVelocitiesCopy(double* velocityX, const int velocityX_len,double* velocityY, const int velocityY_len,double* velocityZ, const int velocityZ_len){
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
void cca::cfd::NS2LBNative2JavaPlainPort::retrieveVelocitiesCopyParallel(double* velocityX, const int velocityX_len,double* velocityY, const int velocityY_len,double* velocityZ, const int velocityZ_len){
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
void cca::cfd::NS2LBNative2JavaPlainPort::retrieveJacobianCopy(double* jacobian, const int jacobian_len){
  JNIEnv* env;
  int status=_jvm->GetEnv((void**)&env,JNI_VERSION_1_6);
  jclass cls=env->GetObjectClass(_obj);
  jmethodID mid = env->GetMethodID(cls,"retrieveJacobianCopy","([D)V");
  
  if(mid){
     jdoubleArray jacobian_jni=env->NewDoubleArray(jacobian_len);
env->SetDoubleArrayRegion(jacobian_jni,0,jacobian_len,(jdouble*)jacobian);

     env->CallVoidMethod(_obj,mid,jacobian_jni);
     env->GetDoubleArrayRegion(jacobian_jni,0,jacobian_len,(jdouble*)jacobian);

  }
}
void cca::cfd::NS2LBNative2JavaPlainPort::retrieveJacobianCopyParallel(double* jacobian, const int jacobian_len){
  JNIEnv* env;
  int status=_jvm->GetEnv((void**)&env,JNI_VERSION_1_6);
  jclass cls=env->GetObjectClass(_obj);
  jmethodID mid = env->GetMethodID(cls,"retrieveJacobianCopyParallel","([D)V");
  
  if(mid){
     jdoubleArray jacobian_jni=env->NewDoubleArray(jacobian_len);
env->SetDoubleArrayRegion(jacobian_jni,0,jacobian_len,(jdouble*)jacobian);

     env->CallVoidMethod(_obj,mid,jacobian_jni);
     env->GetDoubleArrayRegion(jacobian_jni,0,jacobian_len,(jdouble*)jacobian);

  }
}
void cca::cfd::NS2LBNative2JavaPlainPort::retrievePressureCopy(double* pressure, const int pressure_len){
  JNIEnv* env;
  int status=_jvm->GetEnv((void**)&env,JNI_VERSION_1_6);
  jclass cls=env->GetObjectClass(_obj);
  jmethodID mid = env->GetMethodID(cls,"retrievePressureCopy","([D)V");
  
  if(mid){
     jdoubleArray pressure_jni=env->NewDoubleArray(pressure_len);
env->SetDoubleArrayRegion(pressure_jni,0,pressure_len,(jdouble*)pressure);

     env->CallVoidMethod(_obj,mid,pressure_jni);
     env->GetDoubleArrayRegion(pressure_jni,0,pressure_len,(jdouble*)pressure);

  }
}
void cca::cfd::NS2LBNative2JavaPlainPort::retrievePressureCopyParallel(double* pressure, const int pressure_len){
  JNIEnv* env;
  int status=_jvm->GetEnv((void**)&env,JNI_VERSION_1_6);
  jclass cls=env->GetObjectClass(_obj);
  jmethodID mid = env->GetMethodID(cls,"retrievePressureCopyParallel","([D)V");
  
  if(mid){
     jdoubleArray pressure_jni=env->NewDoubleArray(pressure_len);
env->SetDoubleArrayRegion(pressure_jni,0,pressure_len,(jdouble*)pressure);

     env->CallVoidMethod(_obj,mid,pressure_jni);
     env->GetDoubleArrayRegion(pressure_jni,0,pressure_len,(jdouble*)pressure);

  }
}
#endif
