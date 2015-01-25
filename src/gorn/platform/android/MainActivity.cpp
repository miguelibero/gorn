#include <jni.h>
#include <gorn/base/Application.hpp>
#include <gorn/render/Gl.hpp>
#include <JniObject.hpp>

gorn::Application app;

extern "C" {

	JNIEXPORT void JNICALL Java_me_ibero_gorn_MainActivity_nativeOnSurfaceCreated(JNIEnv* env, jclass cls)
	{
		app.load();
	}

	JNIEXPORT void JNICALL Java_me_ibero_gorn_MainActivity_nativeOnPause(JNIEnv* env, jclass cls)
	{
        app.background();
	}

	JNIEXPORT void JNICALL Java_me_ibero_gorn_MainActivity_nativeOnResume(JNIEnv* env, jclass cls)
	{
        app.foreground();
	}

	JNIEXPORT void JNICALL Java_me_ibero_gorn_MainActivity_nativeOnDestroy(JNIEnv* env, jclass cls)
	{
        app.unload();
	}
	 
	JNIEXPORT void JNICALL Java_me_ibero_gorn_MainActivity_nativeOnSurfaceChanged(JNIEnv* env, jclass cls, jint width, jint height)
	{
	}
	 
	JNIEXPORT void JNICALL Java_me_ibero_gorn_MainActivity_nativeOnDrawFrame(JNIEnv* env, jclass cls, jdouble dt)
	{
		app.update(dt);
	}

	jint JNI_OnLoad(JavaVM *vm, void *reserved)
	{
        gornInitGlExtensions();
		return Jni::get().onLoad(vm);
	}

}
