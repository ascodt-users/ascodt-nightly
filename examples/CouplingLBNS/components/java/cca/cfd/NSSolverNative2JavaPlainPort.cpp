#include "cca/cfd/NSSolverNative2JavaPlainPort.h"

JNIEXPORT void JNICALL Java_cca_cfd_NSSolverNative2JavaPlainPort_createInstance(JNIEnv *env, jobject obj){
  JavaVM* jvm;
  env->GetJavaVM(&jvm);
  jobject self=env->NewGlobalRef(obj);
  
  cca::cfd::NSSolverNative2JavaPlainPort *ref=new cca::cfd::NSSolverNative2JavaPlainPort(jvm,self);
  
  jfieldID id =env->GetFieldID(env->GetObjectClass(obj), "_ref", "J");
  env->SetLongField(obj, id, (jlong)ref);
  
}

JNIEXPORT void JNICALL Java_cca_cfd_NSSolverNative2JavaPlainPort_destroyInstance(JNIEnv *env, jobject obj,jlong ref){
  delete ((cca::cfd::NSSolverNative2JavaPlainPort*)ref);
  
}

cca::cfd::NSSolverNative2JavaPlainPort::NSSolverNative2JavaPlainPort(JavaVM* jvm,jobject obj):
     _jvm(jvm),
     _obj(obj){

}

cca::cfd::NSSolverNative2JavaPlainPort::~NSSolverNative2JavaPlainPort(){
  JNIEnv* env;
  _jvm->GetEnv((void**)&env,JNI_VERSION_1_6);
  env->DeleteGlobalRef(_obj);
}

void cca::cfd::NSSolverNative2JavaPlainPort::setup(const std::string inputScenario){
  JNIEnv* env;
  int status=_jvm->GetEnv((void**)&env,JNI_VERSION_1_6);
  jclass cls=env->GetObjectClass(_obj);
  jmethodID mid = env->GetMethodID(cls,"setup","(Ljava/lang/String;)V");
  
  if(mid){
     jobject inputScenario_jni=env->NewStringUTF(inputScenario.c_str());

     env->CallVoidMethod(_obj,mid,inputScenario_jni);
     
  }
}
void cca::cfd::NSSolverNative2JavaPlainPort::setupParallel(const std::string inputScenario){
  JNIEnv* env;
  int status=_jvm->GetEnv((void**)&env,JNI_VERSION_1_6);
  jclass cls=env->GetObjectClass(_obj);
  jmethodID mid = env->GetMethodID(cls,"setupParallel","(Ljava/lang/String;)V");
  
  if(mid){
     jobject inputScenario_jni=env->NewStringUTF(inputScenario.c_str());

     env->CallVoidMethod(_obj,mid,inputScenario_jni);
     
  }
}
void cca::cfd::NSSolverNative2JavaPlainPort::setupCommForLBRegion(const int* startOfRegion, const int startOfRegion_len,const int* endOfRegion, const int endOfRegion_len,const std::string* commids, const int commids_len){
  JNIEnv* env;
  int status=_jvm->GetEnv((void**)&env,JNI_VERSION_1_6);
  jclass cls=env->GetObjectClass(_obj);
  jmethodID mid = env->GetMethodID(cls,"setupCommForLBRegion","([I[I[Ljava/lang/String;)V");
  
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
void cca::cfd::NSSolverNative2JavaPlainPort::setupCommForLBRegionParallel(const int* startOfRegion, const int startOfRegion_len,const int* endOfRegion, const int endOfRegion_len,const std::string* commids, const int commids_len){
  JNIEnv* env;
  int status=_jvm->GetEnv((void**)&env,JNI_VERSION_1_6);
  jclass cls=env->GetObjectClass(_obj);
  jmethodID mid = env->GetMethodID(cls,"setupCommForLBRegionParallel","([I[I[Ljava/lang/String;)V");
  
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
void cca::cfd::NSSolverNative2JavaPlainPort::solve(){
  JNIEnv* env;
  int status=_jvm->GetEnv((void**)&env,JNI_VERSION_1_6);
  jclass cls=env->GetObjectClass(_obj);
  jmethodID mid = env->GetMethodID(cls,"solve","()V");
  
  if(mid){
     
     env->CallVoidMethod(_obj,mid);
     
  }
}
void cca::cfd::NSSolverNative2JavaPlainPort::solveParallel(){
  JNIEnv* env;
  int status=_jvm->GetEnv((void**)&env,JNI_VERSION_1_6);
  jclass cls=env->GetObjectClass(_obj);
  jmethodID mid = env->GetMethodID(cls,"solveParallel","()V");
  
  if(mid){
     
     env->CallVoidMethod(_obj,mid);
     
  }
}
void cca::cfd::NSSolverNative2JavaPlainPort::solveOneTimestepPhaseOne(){
  JNIEnv* env;
  int status=_jvm->GetEnv((void**)&env,JNI_VERSION_1_6);
  jclass cls=env->GetObjectClass(_obj);
  jmethodID mid = env->GetMethodID(cls,"solveOneTimestepPhaseOne","()V");
  
  if(mid){
     
     env->CallVoidMethod(_obj,mid);
     
  }
}
void cca::cfd::NSSolverNative2JavaPlainPort::solveOneTimestepPhaseOneParallel(){
  JNIEnv* env;
  int status=_jvm->GetEnv((void**)&env,JNI_VERSION_1_6);
  jclass cls=env->GetObjectClass(_obj);
  jmethodID mid = env->GetMethodID(cls,"solveOneTimestepPhaseOneParallel","()V");
  
  if(mid){
     
     env->CallVoidMethod(_obj,mid);
     
  }
}
void cca::cfd::NSSolverNative2JavaPlainPort::solveOneTimestepPhaseTwo(){
  JNIEnv* env;
  int status=_jvm->GetEnv((void**)&env,JNI_VERSION_1_6);
  jclass cls=env->GetObjectClass(_obj);
  jmethodID mid = env->GetMethodID(cls,"solveOneTimestepPhaseTwo","()V");
  
  if(mid){
     
     env->CallVoidMethod(_obj,mid);
     
  }
}
void cca::cfd::NSSolverNative2JavaPlainPort::solveOneTimestepPhaseTwoParallel(){
  JNIEnv* env;
  int status=_jvm->GetEnv((void**)&env,JNI_VERSION_1_6);
  jclass cls=env->GetObjectClass(_obj);
  jmethodID mid = env->GetMethodID(cls,"solveOneTimestepPhaseTwoParallel","()V");
  
  if(mid){
     
     env->CallVoidMethod(_obj,mid);
     
  }
}
void cca::cfd::NSSolverNative2JavaPlainPort::setVelocities(const double* velocitiesX, const int velocitiesX_len,const double* velocitiesY, const int velocitiesY_len,const double* velocitiesZ, const int velocitiesZ_len){
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
void cca::cfd::NSSolverNative2JavaPlainPort::setVelocitiesParallel(const double* velocitiesX, const int velocitiesX_len,const double* velocitiesY, const int velocitiesY_len,const double* velocitiesZ, const int velocitiesZ_len){
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
void cca::cfd::NSSolverNative2JavaPlainPort::printNSPressure(){
  JNIEnv* env;
  int status=_jvm->GetEnv((void**)&env,JNI_VERSION_1_6);
  jclass cls=env->GetObjectClass(_obj);
  jmethodID mid = env->GetMethodID(cls,"printNSPressure","()V");
  
  if(mid){
     
     env->CallVoidMethod(_obj,mid);
     
  }
}
void cca::cfd::NSSolverNative2JavaPlainPort::printNSPressureParallel(){
  JNIEnv* env;
  int status=_jvm->GetEnv((void**)&env,JNI_VERSION_1_6);
  jclass cls=env->GetObjectClass(_obj);
  jmethodID mid = env->GetMethodID(cls,"printNSPressureParallel","()V");
  
  if(mid){
     
     env->CallVoidMethod(_obj,mid);
     
  }
}
void cca::cfd::NSSolverNative2JavaPlainPort::printNSProfiles(){
  JNIEnv* env;
  int status=_jvm->GetEnv((void**)&env,JNI_VERSION_1_6);
  jclass cls=env->GetObjectClass(_obj);
  jmethodID mid = env->GetMethodID(cls,"printNSProfiles","()V");
  
  if(mid){
     
     env->CallVoidMethod(_obj,mid);
     
  }
}
void cca::cfd::NSSolverNative2JavaPlainPort::printNSProfilesParallel(){
  JNIEnv* env;
  int status=_jvm->GetEnv((void**)&env,JNI_VERSION_1_6);
  jclass cls=env->GetObjectClass(_obj);
  jmethodID mid = env->GetMethodID(cls,"printNSProfilesParallel","()V");
  
  if(mid){
     
     env->CallVoidMethod(_obj,mid);
     
  }
}
void cca::cfd::NSSolverNative2JavaPlainPort::closeNSProfiles(){
  JNIEnv* env;
  int status=_jvm->GetEnv((void**)&env,JNI_VERSION_1_6);
  jclass cls=env->GetObjectClass(_obj);
  jmethodID mid = env->GetMethodID(cls,"closeNSProfiles","()V");
  
  if(mid){
     
     env->CallVoidMethod(_obj,mid);
     
  }
}
void cca::cfd::NSSolverNative2JavaPlainPort::closeNSProfilesParallel(){
  JNIEnv* env;
  int status=_jvm->GetEnv((void**)&env,JNI_VERSION_1_6);
  jclass cls=env->GetObjectClass(_obj);
  jmethodID mid = env->GetMethodID(cls,"closeNSProfilesParallel","()V");
  
  if(mid){
     
     env->CallVoidMethod(_obj,mid);
     
  }
}
void cca::cfd::NSSolverNative2JavaPlainPort::iterateBoundary(){
  JNIEnv* env;
  int status=_jvm->GetEnv((void**)&env,JNI_VERSION_1_6);
  jclass cls=env->GetObjectClass(_obj);
  jmethodID mid = env->GetMethodID(cls,"iterateBoundary","()V");
  
  if(mid){
     
     env->CallVoidMethod(_obj,mid);
     
  }
}
void cca::cfd::NSSolverNative2JavaPlainPort::iterateBoundaryParallel(){
  JNIEnv* env;
  int status=_jvm->GetEnv((void**)&env,JNI_VERSION_1_6);
  jclass cls=env->GetObjectClass(_obj);
  jmethodID mid = env->GetMethodID(cls,"iterateBoundaryParallel","()V");
  
  if(mid){
     
     env->CallVoidMethod(_obj,mid);
     
  }
}
void cca::cfd::NSSolverNative2JavaPlainPort::iterateInner(){
  JNIEnv* env;
  int status=_jvm->GetEnv((void**)&env,JNI_VERSION_1_6);
  jclass cls=env->GetObjectClass(_obj);
  jmethodID mid = env->GetMethodID(cls,"iterateInner","()V");
  
  if(mid){
     
     env->CallVoidMethod(_obj,mid);
     
  }
}
void cca::cfd::NSSolverNative2JavaPlainPort::iterateInnerParallel(){
  JNIEnv* env;
  int status=_jvm->GetEnv((void**)&env,JNI_VERSION_1_6);
  jclass cls=env->GetObjectClass(_obj);
  jmethodID mid = env->GetMethodID(cls,"iterateInnerParallel","()V");
  
  if(mid){
     
     env->CallVoidMethod(_obj,mid);
     
  }
}
void cca::cfd::NSSolverNative2JavaPlainPort::forwardVelocities(const int* keys, const int keys_len,const int* offsets, const int offsets_len,const int* flips, const int flips_len,const double* values, const int values_len,int& ackn){
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
void cca::cfd::NSSolverNative2JavaPlainPort::forwardVelocitiesParallel(const int* keys, const int keys_len,const int* offsets, const int offsets_len,const int* flips, const int flips_len,const double* values, const int values_len,int& ackn){
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
void cca::cfd::NSSolverNative2JavaPlainPort::plot(){
  JNIEnv* env;
  int status=_jvm->GetEnv((void**)&env,JNI_VERSION_1_6);
  jclass cls=env->GetObjectClass(_obj);
  jmethodID mid = env->GetMethodID(cls,"plot","()V");
  
  if(mid){
     
     env->CallVoidMethod(_obj,mid);
     
  }
}
void cca::cfd::NSSolverNative2JavaPlainPort::plotParallel(){
  JNIEnv* env;
  int status=_jvm->GetEnv((void**)&env,JNI_VERSION_1_6);
  jclass cls=env->GetObjectClass(_obj);
  jmethodID mid = env->GetMethodID(cls,"plotParallel","()V");
  
  if(mid){
     
     env->CallVoidMethod(_obj,mid);
     
  }
}
void cca::cfd::NSSolverNative2JavaPlainPort::syncr(int& value){
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
void cca::cfd::NSSolverNative2JavaPlainPort::syncrParallel(int& value){
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
