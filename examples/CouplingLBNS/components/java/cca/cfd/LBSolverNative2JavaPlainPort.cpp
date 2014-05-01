#include "cca/cfd/LBSolverNative2JavaPlainPort.h"

JNIEXPORT void JNICALL Java_cca_cfd_LBSolverNative2JavaPlainPort_createInstance(JNIEnv *env, jobject obj){
  JavaVM* jvm;
  env->GetJavaVM(&jvm);
  jobject self=env->NewGlobalRef(obj);
  
  cca::cfd::LBSolverNative2JavaPlainPort *ref=new cca::cfd::LBSolverNative2JavaPlainPort(jvm,self);
  
  jfieldID id =env->GetFieldID(env->GetObjectClass(obj), "_ref", "J");
  env->SetLongField(obj, id, (jlong)ref);
  
}

JNIEXPORT void JNICALL Java_cca_cfd_LBSolverNative2JavaPlainPort_destroyInstance(JNIEnv *env, jobject obj,jlong ref){
  delete ((cca::cfd::LBSolverNative2JavaPlainPort*)ref);
  
}

cca::cfd::LBSolverNative2JavaPlainPort::LBSolverNative2JavaPlainPort(JavaVM* jvm,jobject obj):
     _jvm(jvm),
     _obj(obj){

}

cca::cfd::LBSolverNative2JavaPlainPort::~LBSolverNative2JavaPlainPort(){
  JNIEnv* env;
  _jvm->GetEnv((void**)&env,JNI_VERSION_1_6);
  env->DeleteGlobalRef(_obj);
}

void cca::cfd::LBSolverNative2JavaPlainPort::setup(const std::string inputScenario){
  JNIEnv* env;
  int status=_jvm->GetEnv((void**)&env,JNI_VERSION_1_6);
  jclass cls=env->GetObjectClass(_obj);
  jmethodID mid = env->GetMethodID(cls,"setup","(Ljava/lang/String;)V");
  
  if(mid){
     jobject inputScenario_jni=env->NewStringUTF(inputScenario.c_str());

     env->CallVoidMethod(_obj,mid,inputScenario_jni);
     
  }
}
void cca::cfd::LBSolverNative2JavaPlainPort::setupParallel(const std::string inputScenario){
  JNIEnv* env;
  int status=_jvm->GetEnv((void**)&env,JNI_VERSION_1_6);
  jclass cls=env->GetObjectClass(_obj);
  jmethodID mid = env->GetMethodID(cls,"setupParallel","(Ljava/lang/String;)V");
  
  if(mid){
     jobject inputScenario_jni=env->NewStringUTF(inputScenario.c_str());

     env->CallVoidMethod(_obj,mid,inputScenario_jni);
     
  }
}
void cca::cfd::LBSolverNative2JavaPlainPort::setupCommForNSRegion(const int* startOfRegion, const int startOfRegion_len,const int* endOfRegion, const int endOfRegion_len,const std::string* commids, const int commids_len){
  JNIEnv* env;
  int status=_jvm->GetEnv((void**)&env,JNI_VERSION_1_6);
  jclass cls=env->GetObjectClass(_obj);
  jmethodID mid = env->GetMethodID(cls,"setupCommForNSRegion","([I[I[Ljava/lang/String;)V");
  
  if(mid){
     jintArray startOfRegion_jni=env->NewIntArray(startOfRegion_len);
env->SetIntArrayRegion(startOfRegion_jni,0,startOfRegion_len,(jint*)startOfRegion);
jintArray endOfRegion_jni=env->NewIntArray(endOfRegion_len);
env->SetIntArrayRegion(endOfRegion_jni,0,endOfRegion_len,(jint*)endOfRegion);
jobjectArray commids_jni=env->NewObjectArray(commids_len,env->FindClass("Ljava/lang/String;"),0);
for(int i=0;i<commids_len;i++)
	env->SetObjectArrayElement(commids_jni,i, env->NewStringUTF(commids[i].c_str()));

     env->CallVoidMethod(_obj,mid,startOfRegion_jni,endOfRegion_jni,commids_jni);
     
  }
}
void cca::cfd::LBSolverNative2JavaPlainPort::setupCommForNSRegionParallel(const int* startOfRegion, const int startOfRegion_len,const int* endOfRegion, const int endOfRegion_len,const std::string* commids, const int commids_len){
  JNIEnv* env;
  int status=_jvm->GetEnv((void**)&env,JNI_VERSION_1_6);
  jclass cls=env->GetObjectClass(_obj);
  jmethodID mid = env->GetMethodID(cls,"setupCommForNSRegionParallel","([I[I[Ljava/lang/String;)V");
  
  if(mid){
     jintArray startOfRegion_jni=env->NewIntArray(startOfRegion_len);
env->SetIntArrayRegion(startOfRegion_jni,0,startOfRegion_len,(jint*)startOfRegion);
jintArray endOfRegion_jni=env->NewIntArray(endOfRegion_len);
env->SetIntArrayRegion(endOfRegion_jni,0,endOfRegion_len,(jint*)endOfRegion);
jobjectArray commids_jni=env->NewObjectArray(commids_len,env->FindClass("Ljava/lang/String;"),0);
for(int i=0;i<commids_len;i++)
	env->SetObjectArrayElement(commids_jni,i, env->NewStringUTF(commids[i].c_str()));

     env->CallVoidMethod(_obj,mid,startOfRegion_jni,endOfRegion_jni,commids_jni);
     
  }
}
void cca::cfd::LBSolverNative2JavaPlainPort::solve(){
  JNIEnv* env;
  int status=_jvm->GetEnv((void**)&env,JNI_VERSION_1_6);
  jclass cls=env->GetObjectClass(_obj);
  jmethodID mid = env->GetMethodID(cls,"solve","()V");
  
  if(mid){
     
     env->CallVoidMethod(_obj,mid);
     
  }
}
void cca::cfd::LBSolverNative2JavaPlainPort::solveParallel(){
  JNIEnv* env;
  int status=_jvm->GetEnv((void**)&env,JNI_VERSION_1_6);
  jclass cls=env->GetObjectClass(_obj);
  jmethodID mid = env->GetMethodID(cls,"solveParallel","()V");
  
  if(mid){
     
     env->CallVoidMethod(_obj,mid);
     
  }
}
void cca::cfd::LBSolverNative2JavaPlainPort::solveOneTimestep(){
  JNIEnv* env;
  int status=_jvm->GetEnv((void**)&env,JNI_VERSION_1_6);
  jclass cls=env->GetObjectClass(_obj);
  jmethodID mid = env->GetMethodID(cls,"solveOneTimestep","()V");
  
  if(mid){
     
     env->CallVoidMethod(_obj,mid);
     
  }
}
void cca::cfd::LBSolverNative2JavaPlainPort::solveOneTimestepParallel(){
  JNIEnv* env;
  int status=_jvm->GetEnv((void**)&env,JNI_VERSION_1_6);
  jclass cls=env->GetObjectClass(_obj);
  jmethodID mid = env->GetMethodID(cls,"solveOneTimestepParallel","()V");
  
  if(mid){
     
     env->CallVoidMethod(_obj,mid);
     
  }
}
void cca::cfd::LBSolverNative2JavaPlainPort::setVelocities(const double* velocitiesX, const int velocitiesX_len,const double* velocitiesY, const int velocitiesY_len,const double* velocitiesZ, const int velocitiesZ_len){
  JNIEnv* env;
  int status=_jvm->GetEnv((void**)&env,JNI_VERSION_1_6);
  jclass cls=env->GetObjectClass(_obj);
  jmethodID mid = env->GetMethodID(cls,"setVelocities","([D[D[D)V");
  
  if(mid){
     jdoubleArray velocitiesX_jni=env->NewDoubleArray(velocitiesX_len);
env->SetDoubleArrayRegion(velocitiesX_jni,0,velocitiesX_len,(jdouble*)velocitiesX);
jdoubleArray velocitiesY_jni=env->NewDoubleArray(velocitiesY_len);
env->SetDoubleArrayRegion(velocitiesY_jni,0,velocitiesY_len,(jdouble*)velocitiesY);
jdoubleArray velocitiesZ_jni=env->NewDoubleArray(velocitiesZ_len);
env->SetDoubleArrayRegion(velocitiesZ_jni,0,velocitiesZ_len,(jdouble*)velocitiesZ);

     env->CallVoidMethod(_obj,mid,velocitiesX_jni,velocitiesY_jni,velocitiesZ_jni);
     
  }
}
void cca::cfd::LBSolverNative2JavaPlainPort::setVelocitiesParallel(const double* velocitiesX, const int velocitiesX_len,const double* velocitiesY, const int velocitiesY_len,const double* velocitiesZ, const int velocitiesZ_len){
  JNIEnv* env;
  int status=_jvm->GetEnv((void**)&env,JNI_VERSION_1_6);
  jclass cls=env->GetObjectClass(_obj);
  jmethodID mid = env->GetMethodID(cls,"setVelocitiesParallel","([D[D[D)V");
  
  if(mid){
     jdoubleArray velocitiesX_jni=env->NewDoubleArray(velocitiesX_len);
env->SetDoubleArrayRegion(velocitiesX_jni,0,velocitiesX_len,(jdouble*)velocitiesX);
jdoubleArray velocitiesY_jni=env->NewDoubleArray(velocitiesY_len);
env->SetDoubleArrayRegion(velocitiesY_jni,0,velocitiesY_len,(jdouble*)velocitiesY);
jdoubleArray velocitiesZ_jni=env->NewDoubleArray(velocitiesZ_len);
env->SetDoubleArrayRegion(velocitiesZ_jni,0,velocitiesZ_len,(jdouble*)velocitiesZ);

     env->CallVoidMethod(_obj,mid,velocitiesX_jni,velocitiesY_jni,velocitiesZ_jni);
     
  }
}
void cca::cfd::LBSolverNative2JavaPlainPort::setPressure(const double* pressure, const int pressure_len){
  JNIEnv* env;
  int status=_jvm->GetEnv((void**)&env,JNI_VERSION_1_6);
  jclass cls=env->GetObjectClass(_obj);
  jmethodID mid = env->GetMethodID(cls,"setPressure","([D)V");
  
  if(mid){
     jdoubleArray pressure_jni=env->NewDoubleArray(pressure_len);
env->SetDoubleArrayRegion(pressure_jni,0,pressure_len,(jdouble*)pressure);

     env->CallVoidMethod(_obj,mid,pressure_jni);
     
  }
}
void cca::cfd::LBSolverNative2JavaPlainPort::setPressureParallel(const double* pressure, const int pressure_len){
  JNIEnv* env;
  int status=_jvm->GetEnv((void**)&env,JNI_VERSION_1_6);
  jclass cls=env->GetObjectClass(_obj);
  jmethodID mid = env->GetMethodID(cls,"setPressureParallel","([D)V");
  
  if(mid){
     jdoubleArray pressure_jni=env->NewDoubleArray(pressure_len);
env->SetDoubleArrayRegion(pressure_jni,0,pressure_len,(jdouble*)pressure);

     env->CallVoidMethod(_obj,mid,pressure_jni);
     
  }
}
void cca::cfd::LBSolverNative2JavaPlainPort::setGradients(const double* gradients, const int gradients_len){
  JNIEnv* env;
  int status=_jvm->GetEnv((void**)&env,JNI_VERSION_1_6);
  jclass cls=env->GetObjectClass(_obj);
  jmethodID mid = env->GetMethodID(cls,"setGradients","([D)V");
  
  if(mid){
     jdoubleArray gradients_jni=env->NewDoubleArray(gradients_len);
env->SetDoubleArrayRegion(gradients_jni,0,gradients_len,(jdouble*)gradients);

     env->CallVoidMethod(_obj,mid,gradients_jni);
     
  }
}
void cca::cfd::LBSolverNative2JavaPlainPort::setGradientsParallel(const double* gradients, const int gradients_len){
  JNIEnv* env;
  int status=_jvm->GetEnv((void**)&env,JNI_VERSION_1_6);
  jclass cls=env->GetObjectClass(_obj);
  jmethodID mid = env->GetMethodID(cls,"setGradientsParallel","([D)V");
  
  if(mid){
     jdoubleArray gradients_jni=env->NewDoubleArray(gradients_len);
env->SetDoubleArrayRegion(gradients_jni,0,gradients_len,(jdouble*)gradients);

     env->CallVoidMethod(_obj,mid,gradients_jni);
     
  }
}
void cca::cfd::LBSolverNative2JavaPlainPort::closeLBProfiles(){
  JNIEnv* env;
  int status=_jvm->GetEnv((void**)&env,JNI_VERSION_1_6);
  jclass cls=env->GetObjectClass(_obj);
  jmethodID mid = env->GetMethodID(cls,"closeLBProfiles","()V");
  
  if(mid){
     
     env->CallVoidMethod(_obj,mid);
     
  }
}
void cca::cfd::LBSolverNative2JavaPlainPort::closeLBProfilesParallel(){
  JNIEnv* env;
  int status=_jvm->GetEnv((void**)&env,JNI_VERSION_1_6);
  jclass cls=env->GetObjectClass(_obj);
  jmethodID mid = env->GetMethodID(cls,"closeLBProfilesParallel","()V");
  
  if(mid){
     
     env->CallVoidMethod(_obj,mid);
     
  }
}
void cca::cfd::LBSolverNative2JavaPlainPort::printLBDensity(){
  JNIEnv* env;
  int status=_jvm->GetEnv((void**)&env,JNI_VERSION_1_6);
  jclass cls=env->GetObjectClass(_obj);
  jmethodID mid = env->GetMethodID(cls,"printLBDensity","()V");
  
  if(mid){
     
     env->CallVoidMethod(_obj,mid);
     
  }
}
void cca::cfd::LBSolverNative2JavaPlainPort::printLBDensityParallel(){
  JNIEnv* env;
  int status=_jvm->GetEnv((void**)&env,JNI_VERSION_1_6);
  jclass cls=env->GetObjectClass(_obj);
  jmethodID mid = env->GetMethodID(cls,"printLBDensityParallel","()V");
  
  if(mid){
     
     env->CallVoidMethod(_obj,mid);
     
  }
}
void cca::cfd::LBSolverNative2JavaPlainPort::printLBProfiles(){
  JNIEnv* env;
  int status=_jvm->GetEnv((void**)&env,JNI_VERSION_1_6);
  jclass cls=env->GetObjectClass(_obj);
  jmethodID mid = env->GetMethodID(cls,"printLBProfiles","()V");
  
  if(mid){
     
     env->CallVoidMethod(_obj,mid);
     
  }
}
void cca::cfd::LBSolverNative2JavaPlainPort::printLBProfilesParallel(){
  JNIEnv* env;
  int status=_jvm->GetEnv((void**)&env,JNI_VERSION_1_6);
  jclass cls=env->GetObjectClass(_obj);
  jmethodID mid = env->GetMethodID(cls,"printLBProfilesParallel","()V");
  
  if(mid){
     
     env->CallVoidMethod(_obj,mid);
     
  }
}
void cca::cfd::LBSolverNative2JavaPlainPort::forwardVelocities(const int* keys, const int keys_len,const int* offsets, const int offsets_len,const int* flips, const int flips_len,const double* values, const int values_len,int& ackn){
  JNIEnv* env;
  int status=_jvm->GetEnv((void**)&env,JNI_VERSION_1_6);
  jclass cls=env->GetObjectClass(_obj);
  jmethodID mid = env->GetMethodID(cls,"forwardVelocities","([I[I[I[D[I)V");
  
  if(mid){
     jintArray keys_jni=env->NewIntArray(keys_len);
env->SetIntArrayRegion(keys_jni,0,keys_len,(jint*)keys);
jintArray offsets_jni=env->NewIntArray(offsets_len);
env->SetIntArrayRegion(offsets_jni,0,offsets_len,(jint*)offsets);
jintArray flips_jni=env->NewIntArray(flips_len);
env->SetIntArrayRegion(flips_jni,0,flips_len,(jint*)flips);
jdoubleArray values_jni=env->NewDoubleArray(values_len);
env->SetDoubleArrayRegion(values_jni,0,values_len,(jdouble*)values);
jintArray ackn_jni=env->NewIntArray(1);
env->SetIntArrayRegion(ackn_jni,0,1,(jint*)&ackn);

     env->CallVoidMethod(_obj,mid,keys_jni,offsets_jni,flips_jni,values_jni,ackn_jni);
     env->GetIntArrayRegion(ackn_jni,0,1,(jint*)&ackn);

  }
}
void cca::cfd::LBSolverNative2JavaPlainPort::forwardVelocitiesParallel(const int* keys, const int keys_len,const int* offsets, const int offsets_len,const int* flips, const int flips_len,const double* values, const int values_len,int& ackn){
  JNIEnv* env;
  int status=_jvm->GetEnv((void**)&env,JNI_VERSION_1_6);
  jclass cls=env->GetObjectClass(_obj);
  jmethodID mid = env->GetMethodID(cls,"forwardVelocitiesParallel","([I[I[I[D[I)V");
  
  if(mid){
     jintArray keys_jni=env->NewIntArray(keys_len);
env->SetIntArrayRegion(keys_jni,0,keys_len,(jint*)keys);
jintArray offsets_jni=env->NewIntArray(offsets_len);
env->SetIntArrayRegion(offsets_jni,0,offsets_len,(jint*)offsets);
jintArray flips_jni=env->NewIntArray(flips_len);
env->SetIntArrayRegion(flips_jni,0,flips_len,(jint*)flips);
jdoubleArray values_jni=env->NewDoubleArray(values_len);
env->SetDoubleArrayRegion(values_jni,0,values_len,(jdouble*)values);
jintArray ackn_jni=env->NewIntArray(1);
env->SetIntArrayRegion(ackn_jni,0,1,(jint*)&ackn);

     env->CallVoidMethod(_obj,mid,keys_jni,offsets_jni,flips_jni,values_jni,ackn_jni);
     env->GetIntArrayRegion(ackn_jni,0,1,(jint*)&ackn);

  }
}
void cca::cfd::LBSolverNative2JavaPlainPort::forwardPressure(const int* keys, const int keys_len,const int* offsets, const int offsets_len,const int* flips, const int flips_len,const double* values, const int values_len,int& ackn){
  JNIEnv* env;
  int status=_jvm->GetEnv((void**)&env,JNI_VERSION_1_6);
  jclass cls=env->GetObjectClass(_obj);
  jmethodID mid = env->GetMethodID(cls,"forwardPressure","([I[I[I[D[I)V");
  
  if(mid){
     jintArray keys_jni=env->NewIntArray(keys_len);
env->SetIntArrayRegion(keys_jni,0,keys_len,(jint*)keys);
jintArray offsets_jni=env->NewIntArray(offsets_len);
env->SetIntArrayRegion(offsets_jni,0,offsets_len,(jint*)offsets);
jintArray flips_jni=env->NewIntArray(flips_len);
env->SetIntArrayRegion(flips_jni,0,flips_len,(jint*)flips);
jdoubleArray values_jni=env->NewDoubleArray(values_len);
env->SetDoubleArrayRegion(values_jni,0,values_len,(jdouble*)values);
jintArray ackn_jni=env->NewIntArray(1);
env->SetIntArrayRegion(ackn_jni,0,1,(jint*)&ackn);

     env->CallVoidMethod(_obj,mid,keys_jni,offsets_jni,flips_jni,values_jni,ackn_jni);
     env->GetIntArrayRegion(ackn_jni,0,1,(jint*)&ackn);

  }
}
void cca::cfd::LBSolverNative2JavaPlainPort::forwardPressureParallel(const int* keys, const int keys_len,const int* offsets, const int offsets_len,const int* flips, const int flips_len,const double* values, const int values_len,int& ackn){
  JNIEnv* env;
  int status=_jvm->GetEnv((void**)&env,JNI_VERSION_1_6);
  jclass cls=env->GetObjectClass(_obj);
  jmethodID mid = env->GetMethodID(cls,"forwardPressureParallel","([I[I[I[D[I)V");
  
  if(mid){
     jintArray keys_jni=env->NewIntArray(keys_len);
env->SetIntArrayRegion(keys_jni,0,keys_len,(jint*)keys);
jintArray offsets_jni=env->NewIntArray(offsets_len);
env->SetIntArrayRegion(offsets_jni,0,offsets_len,(jint*)offsets);
jintArray flips_jni=env->NewIntArray(flips_len);
env->SetIntArrayRegion(flips_jni,0,flips_len,(jint*)flips);
jdoubleArray values_jni=env->NewDoubleArray(values_len);
env->SetDoubleArrayRegion(values_jni,0,values_len,(jdouble*)values);
jintArray ackn_jni=env->NewIntArray(1);
env->SetIntArrayRegion(ackn_jni,0,1,(jint*)&ackn);

     env->CallVoidMethod(_obj,mid,keys_jni,offsets_jni,flips_jni,values_jni,ackn_jni);
     env->GetIntArrayRegion(ackn_jni,0,1,(jint*)&ackn);

  }
}
void cca::cfd::LBSolverNative2JavaPlainPort::syncr(int& value){
  JNIEnv* env;
  int status=_jvm->GetEnv((void**)&env,JNI_VERSION_1_6);
  jclass cls=env->GetObjectClass(_obj);
  jmethodID mid = env->GetMethodID(cls,"syncr","([I)V");
  
  if(mid){
     jintArray value_jni=env->NewIntArray(1);
env->SetIntArrayRegion(value_jni,0,1,(jint*)&value);

     env->CallVoidMethod(_obj,mid,value_jni);
     env->GetIntArrayRegion(value_jni,0,1,(jint*)&value);

  }
}
void cca::cfd::LBSolverNative2JavaPlainPort::syncrParallel(int& value){
  JNIEnv* env;
  int status=_jvm->GetEnv((void**)&env,JNI_VERSION_1_6);
  jclass cls=env->GetObjectClass(_obj);
  jmethodID mid = env->GetMethodID(cls,"syncrParallel","([I)V");
  
  if(mid){
     jintArray value_jni=env->NewIntArray(1);
env->SetIntArrayRegion(value_jni,0,1,(jint*)&value);

     env->CallVoidMethod(_obj,mid,value_jni);
     env->GetIntArrayRegion(value_jni,0,1,(jint*)&value);

  }
}
void cca::cfd::LBSolverNative2JavaPlainPort::plot(){
  JNIEnv* env;
  int status=_jvm->GetEnv((void**)&env,JNI_VERSION_1_6);
  jclass cls=env->GetObjectClass(_obj);
  jmethodID mid = env->GetMethodID(cls,"plot","()V");
  
  if(mid){
     
     env->CallVoidMethod(_obj,mid);
     
  }
}
void cca::cfd::LBSolverNative2JavaPlainPort::plotParallel(){
  JNIEnv* env;
  int status=_jvm->GetEnv((void**)&env,JNI_VERSION_1_6);
  jclass cls=env->GetObjectClass(_obj);
  jmethodID mid = env->GetMethodID(cls,"plotParallel","()V");
  
  if(mid){
     
     env->CallVoidMethod(_obj,mid);
     
  }
}
