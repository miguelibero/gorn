#include <jni.h>
#include <gorn/base/Application.hpp>
#include <jniobject/JniObject.hpp>

gorn::Application app;

extern "C" {

	JNIEXPORT void JNICALL Java_me_ibero_gorn_MainActivity_onSurfaceCreated(JNIEnv* env, jclass cls)
	{
		app.load();
	}
	 
	JNIEXPORT void JNICALL Java_me_ibero_gorn_MainActivity_onSurfaceChanged(JNIEnv* env, jclass cls, jint width, jint height)
	{

	}
	 
	JNIEXPORT void JNICALL Java_me_ibero_gorn_MainActivity_onDrawFrame(JNIEnv* env, jclass cls, jdouble dt)
	{
		app.update(dt);
	}

	jint JNI_OnLoad(JavaVM *vm, void *reserved)
	{
		return Jni::get().onLoad(vm);
	}

}
