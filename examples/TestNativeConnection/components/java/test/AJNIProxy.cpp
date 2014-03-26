#include "test/AJNIProxy.h"
#include "test/AImplementation.h"
#include "test/Foo.h"

#include <fstream>  

JNIEXPORT void JNICALL Java_test_AAbstractJavaNativeImplementation_createInstance(JNIEnv *env, jobject obj){
  test::AImplementation *ref=new test::AImplementation();
  jfieldID id =env->GetFieldID(env->GetObjectClass(obj), "_ref", "J");
  env->SetLongField(obj, id, (jlong)ref);
}

JNIEXPORT void JNICALL Java_test_AAbstractJavaNativeImplementation_destroyInstance(JNIEnv *env, jobject obj,jlong ref){
  delete ((test::AImplementation*)ref);
}

JNIEXPORT void JNICALL Java_test_AAbstractJavaNativeImplementation_connectfoo(JNIEnv *env, jobject obj,jlong ref,jlong portRef){
  ((test::AImplementation*)ref)->connectfoo(
     ((test::FooNativeDispatcher*) portRef)
  );    
}

JNIEXPORT void JNICALL Java_test_AAbstractJavaNativeImplementation_disconnectfoo(JNIEnv *env, jobject obj,jlong ref){
   ((test::AImplementation*)ref)->disconnectfoo();   
}

JNIEXPORT void JNICALL Java_test_AAbstractJavaNativeImplementation_bar(JNIEnv *env, jobject obj,jlong ref){
  
  ((test::AImplementation*)ref)->bar();
  
}
