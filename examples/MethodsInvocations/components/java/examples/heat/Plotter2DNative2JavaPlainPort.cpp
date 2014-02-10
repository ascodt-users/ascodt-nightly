#include "examples/heat/Plotter2DNative2JavaPlainPort.h"

JNIEXPORT void JNICALL Java_examples_heat_Plotter2DNative2JavaPlainPort_createInstance(JNIEnv *env, jobject obj){
  JavaVM* jvm;
  env->GetJavaVM(&jvm);
  jobject self=env->NewGlobalRef(obj);
  
  examples::heat::Plotter2DNative2JavaPlainPort *ref=new examples::heat::Plotter2DNative2JavaPlainPort(jvm,self);
  
  jfieldID id =env->GetFieldID(env->GetObjectClass(obj), "_ref", "J");
  env->SetLongField(obj, id, (jlong)ref);
  
}

JNIEXPORT void JNICALL Java_examples_heat_Plotter2DNative2JavaPlainPort_destroyInstance(JNIEnv *env, jobject obj,jlong ref){
  delete ((examples::heat::Plotter2DNative2JavaPlainPort*)ref);
  
}

examples::heat::Plotter2DNative2JavaPlainPort::Plotter2DNative2JavaPlainPort(JavaVM* jvm,jobject obj):
     _jvm(jvm),
     _obj(obj){

}

examples::heat::Plotter2DNative2JavaPlainPort::~Plotter2DNative2JavaPlainPort(){
  JNIEnv* env;
  _jvm->GetEnv((void**)&env,JNI_VERSION_1_6);
  env->DeleteGlobalRef(_obj);
}

void examples::heat::Plotter2DNative2JavaPlainPort::plotPoint(const std::string name,const double x,const double y){
  JNIEnv* env;
  int status=_jvm->GetEnv((void**)&env,JNI_VERSION_1_6);
  //jfieldID pid =env->GetFieldID(env->GetObjectClass(_obj),_portIdentifier.c_str(), "Lexamples/heat/Plotter2DDispatcher;");
  //jobject obj= env->GetObjectField(_obj,pid);
  //jclass cls = env->FindClass("Lexamples/heat/Plotter2DDispatcher;");
  jclass cls=env->GetObjectClass(_obj);
  jmethodID mid = env->GetMethodID(cls,"plotPoint","(Ljava/lang/String;DD)V");
  
  if(mid){
     jobject name_jni=env->NewStringUTF(name.c_str());
jdouble x_jni=x;
jdouble y_jni=y;

     env->CallVoidMethod(_obj,mid,name_jni,x_jni,y_jni);
     
  }
}
