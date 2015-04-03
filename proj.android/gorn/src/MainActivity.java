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
import android.view.View;
import android.view.MotionEvent;
import android.widget.Toast;
import android.opengl.GLSurfaceView.Renderer;
import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public class MainActivity extends Activity
{
	private GLSurfaceView glSurfaceView = null;
	private boolean rendererSet = false;
	private long lastDrawTime = 0;

	protected void onCreate(Bundle savedInstanceState)
    {
		super.onCreate(savedInstanceState);

		NativeBridge.instance.setActivity(this);

		ActivityManager activityManager = (ActivityManager) getSystemService(Context.ACTIVITY_SERVICE);
    	ConfigurationInfo configurationInfo = activityManager.getDeviceConfigurationInfo();
 
    	final boolean supportsEs2 =
        	configurationInfo.reqGlEsVersion >= 0x20000 || isProbablyEmulator();
 
	    if (supportsEs2)
        {
	        glSurfaceView = new GLSurfaceView(this);
	 
	        if (isProbablyEmulator())
            {
	            // Avoids crashes on startup with some emulator images.
	            glSurfaceView.setEGLConfigChooser(8, 8, 8, 8, 16, 0);
	        }
	 
            glSurfaceView.setPreserveEGLContextOnPause(true);
	        glSurfaceView.setEGLContextClientVersion(2);
			glSurfaceView.setRenderer(new Renderer()
            {
			    @Override
			    public void onSurfaceCreated(GL10 gl, EGLConfig config)
                {
			    	MainActivity.this.nativeOnSurfaceCreated();
			    }
			 
			    @Override
			    public void onSurfaceChanged(GL10 gl, int width, int height)
                {
			    	MainActivity.this.nativeOnSurfaceChanged(width, height);
			    }

			    @Override
			    public void onDrawFrame(GL10 gl)
                {
			    	double dt = lastDrawTime;
			    	lastDrawTime = System.currentTimeMillis();
			    	dt = (lastDrawTime - dt) / 1000.0f;
			    	MainActivity.this.nativeOnDrawFrame(dt);
			    }
			});
            glSurfaceView.setOnTouchListener(new View.OnTouchListener(){
                @Override
                public boolean onTouch(View v, MotionEvent ev){
                    final float x = ev.getX() / (float) v.getWidth() * 2  - 1;
                    final float y = (1 - ev.getY() / (float) v.getHeight()) * 2 - 1;
                    glSurfaceView.queueEvent(new Runnable(){
                        public void run()
                        {
                            MainActivity.this.nativeOnTouch(x, y);
                        }
                    });
                    return true;
                }
            });
	        rendererSet = true;
	        setContentView(glSurfaceView);
	        lastDrawTime = System.currentTimeMillis();
	    }
        else
        {
	        // Should never be seen in production, since the manifest filters
	        // unsupported devices.
	        Toast.makeText(this, "This device does not support OpenGL ES 2.0.",
	                Toast.LENGTH_LONG).show();
	        return;
	    }
	}

	private boolean isProbablyEmulator()
    {
    	return Build.VERSION.SDK_INT >= Build.VERSION_CODES.ICE_CREAM_SANDWICH_MR1
            && (Build.FINGERPRINT.startsWith("generic")
                    || Build.FINGERPRINT.startsWith("unknown")
                    || Build.MODEL.contains("google_sdk")
                    || Build.MODEL.contains("Emulator")
                    || Build.MODEL.contains("Android SDK built for x86"));
	}

	@Override
	public void onResume()
    {
		super.onResume();
		if (rendererSet)
        {
        	glSurfaceView.onResume();
    	}
        MainActivity.this.nativeOnResume();
	}

	@Override
	public void onPause()
    {
		super.onPause();
		if (rendererSet)
        {
        	glSurfaceView.onPause();
    	}
        MainActivity.this.nativeOnPause();
	}

	@Override
	public void onDestroy()
    {
        nativeOnDestroy();
		super.onDestroy();
	}

	@Override
	public void onSaveInstanceState(Bundle outState)
    {
		super.onSaveInstanceState(outState);
	}

	@Override
	public void onActivityResult(int requestCode, int resultCode, Intent data)
    {
		super.onActivityResult(requestCode, resultCode, data);
	}

    static
    {
    	System.loadLibrary("c++_shared");
    }

    public static native void nativeOnPause();
    public static native void nativeOnResume();
    public static native void nativeOnSurfaceCreated();
    public static native void nativeOnSurfaceChanged(int width, int height);
    public static native void nativeOnTouch(float x, float y);
    public static native void nativeOnDrawFrame(double dt);
    public static native void nativeOnDestroy();
}
