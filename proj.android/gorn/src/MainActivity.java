package me.ibero.gorn;

import android.content.Intent;
import android.content.Context;
import android.content.pm.ConfigurationInfo;
import android.os.Bundle;
import android.os.Build;
import android.app.Activity;
import android.app.ActivityManager;
import android.util.Log;
import android.opengl.GLSurfaceView;
import android.widget.Toast;
import android.opengl.GLSurfaceView.Renderer;
import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public class MainActivity extends Activity
{
	private GLSurfaceView glSurfaceView;
	private boolean rendererSet;
	private long lastDrawTime;

	protected void onCreate(Bundle savedInstanceState){
		super.onCreate(savedInstanceState);

		NativeBridge.instance.setActivity(this);

		ActivityManager activityManager = (ActivityManager) getSystemService(Context.ACTIVITY_SERVICE);
    	ConfigurationInfo configurationInfo = activityManager.getDeviceConfigurationInfo();
 
    	final boolean supportsEs2 =
        	configurationInfo.reqGlEsVersion >= 0x20000 || isProbablyEmulator();
 
	    if (supportsEs2) {
	        glSurfaceView = new GLSurfaceView(this);
	 
	        if (isProbablyEmulator()) {
	            // Avoids crashes on startup with some emulator images.
	            glSurfaceView.setEGLConfigChooser(8, 8, 8, 8, 16, 0);
	        }
	 
	        glSurfaceView.setEGLContextClientVersion(2);
			glSurfaceView.setRenderer(new Renderer(){
			    @Override
			    public void onSurfaceCreated(GL10 gl, EGLConfig config) {
			    	MainActivity.this.onSurfaceCreated();
			    }
			 
			    @Override
			    public void onSurfaceChanged(GL10 gl, int width, int height) {
			    	MainActivity.this.onSurfaceChanged(width, height);
			    }
			    @Override
			    public void onDrawFrame(GL10 gl) {
			    	double dt = lastDrawTime;
			    	lastDrawTime = System.currentTimeMillis();
			    	dt = (lastDrawTime - dt) / 1000.0f;
			    	MainActivity.this.onDrawFrame(dt);
			    }
			});
	        rendererSet = true;
	        setContentView(glSurfaceView);
	        lastDrawTime = System.currentTimeMillis();
	    } else {
	        // Should never be seen in production, since the manifest filters
	        // unsupported devices.
	        Toast.makeText(this, "This device does not support OpenGL ES 2.0.",
	                Toast.LENGTH_LONG).show();
	        return;
	    }
	}

	private boolean isProbablyEmulator() {
    	return Build.VERSION.SDK_INT >= Build.VERSION_CODES.ICE_CREAM_SANDWICH_MR1
            && (Build.FINGERPRINT.startsWith("generic")
                    || Build.FINGERPRINT.startsWith("unknown")
                    || Build.MODEL.contains("google_sdk")
                    || Build.MODEL.contains("Emulator")
                    || Build.MODEL.contains("Android SDK built for x86"));
	}

	@Override
	public void onResume() {
		super.onResume();
		if (rendererSet) {
        	glSurfaceView.onResume();
    	}
	}

	@Override
	public void onPause() {
		super.onPause();
		if (rendererSet) {
        	glSurfaceView.onPause();
    	}
	}

	@Override
	public void onDestroy() {
		super.onDestroy();
	}

	@Override
	public void onSaveInstanceState(Bundle outState) {
		super.onSaveInstanceState(outState);
	}

	@Override
	public void onActivityResult(int requestCode, int resultCode, Intent data) {
		super.onActivityResult(requestCode, resultCode, data);
	}

    static {
    	System.loadLibrary("c++_shared");
    }

    public static native void onSurfaceCreated();
    public static native void onSurfaceChanged(int width, int height);
    public static native void onDrawFrame(double dt);
}
