#include "test/MyComponentJNIProxy.h"
#include "test/MyComponentImplementation.h"

#include <fstream>  

JNIEXPORT void JNICALL Java_test_MyComponentAbstractJavaNativeImplementation_createInstance(JNIEnv *env, jobject obj){
  test::MyComponentImplementation *ref=new test::MyComponentImplementation();
  jfieldID id =env->GetFieldID(env->GetObjectClass(obj), "_ref", "J");
  env->SetLongField(obj, id, (jlong)ref);
}

JNIEXPORT void JNICALL Java_test_MyComponentAbstractJavaNativeImplementation_destroyInstance(JNIEnv *env, jobject obj,jlong ref){
  delete ((test::MyComponentImplementation*)ref);
}
