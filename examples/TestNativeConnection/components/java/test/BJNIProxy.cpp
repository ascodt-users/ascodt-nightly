#include "test/BJNIProxy.h"
#include "test/BImplementation.h"

#include <fstream>  

JNIEXPORT void JNICALL Java_test_BAbstractJavaNativeImplementation_createInstance(JNIEnv *env, jobject obj){
  test::BImplementation *ref=new test::BImplementation();
  jfieldID id =env->GetFieldID(env->GetObjectClass(obj), "_ref", "J");
  env->SetLongField(obj, id, (jlong)ref);
}

JNIEXPORT void JNICALL Java_test_BAbstractJavaNativeImplementation_destroyInstance(JNIEnv *env, jobject obj,jlong ref){
  delete ((test::BImplementation*)ref);
}

JNIEXPORT void JNICALL Java_test_BAbstractJavaNativeImplementation_bar(JNIEnv *env, jobject obj,jlong ref){
  
  ((test::BImplementation*)ref)->bar();
  
}
