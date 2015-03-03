#include <jni.h>
#include <gorn/base/Application.hpp>
#include <gorn/render/Gl.hpp>
#include <JniObject.hpp>
#include <memory>

std::unique_ptr<gorn::Application> app;

extern "C" {

	JNIEXPORT void JNICALL Java_me_ibero_gorn_MainActivity_nativeOnSurfaceCreated(JNIEnv* env, jclass cls)
	{
        app = std::move(gorn::main());
		app->realLoad();
	}

	JNIEXPORT void JNICALL Java_me_ibero_gorn_MainActivity_nativeOnPause(JNIEnv* env, jclass cls)
	{
        app->realBackground();
	}

	JNIEXPORT void JNICALL Java_me_ibero_gorn_MainActivity_nativeOnResume(JNIEnv* env, jclass cls)
	{
        app->realForeground();
	}

	JNIEXPORT void JNICALL Java_me_ibero_gorn_MainActivity_nativeOnDestroy(JNIEnv* env, jclass cls)
	{
        app->realUnload();
	}
	 
	JNIEXPORT void JNICALL Java_me_ibero_gorn_MainActivity_nativeOnSurfaceChanged(JNIEnv* env, jclass cls, jint width, jint height)
	{
	}

	JNIEXPORT void JNICALL Java_me_ibero_gorn_MainActivity_nativeOnTouch(JNIEnv* env, jclass cls, jfloat x, jfloat y)
	{
        app->realTouch(x, y);
	}
	 
	JNIEXPORT void JNICALL Java_me_ibero_gorn_MainActivity_nativeOnDrawFrame(JNIEnv* env, jclass cls, jdouble dt)
	{
		app->realUpdate(dt);
	}

	jint JNI_OnLoad(JavaVM *vm, void *reserved)
	{
        gornInitGlExtensions();
		return Jni::get().onLoad(vm);
	}

}
