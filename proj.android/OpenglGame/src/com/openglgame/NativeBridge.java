package com.openglgame;

import android.content.res.AssetManager;
import android.app.Activity;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.util.Log;
import java.io.InputStream;
import java.io.IOException;
import java.io.ByteArrayOutputStream;
import java.nio.ByteBuffer;

public enum NativeBridge
{
	instance;

	private Activity mActivity;

	public void setActivity(Activity activity)
	{
		mActivity = activity;
	}

	private byte[] readInputStream(InputStream is) throws IOException
	{
		ByteArrayOutputStream os = new ByteArrayOutputStream();
        byte[] buffer = new byte[0xFFFF];

        for (int len; (len = is.read(buffer)) != -1;)
        {
            os.write(buffer, 0, len);
        }

        os.flush();
        return os.toByteArray();
	}

	public byte[] readImage(String name) throws IOException
	{
		Log.v(TAG, "reading image '" + name + "'...");
		AssetManager am = mActivity.getAssets();
		InputStream is = am.open(name);
		BitmapFactory.Options options = new BitmapFactory.Options();
        options.inScaled = false;
        Bitmap bitmap = BitmapFactory.decodeStream(is, null, options);

		int bytes = bitmap.getByteCount();
		ByteBuffer buffer = ByteBuffer.allocate(bytes);
		bitmap.copyPixelsToBuffer(buffer);
		return buffer.array();
	}

	public byte[] readFile(String name) throws IOException
	{
		Log.v(TAG, "reading file '" + name + "'...");
		AssetManager am = mActivity.getAssets();
		InputStream is = am.open(name);
		return readInputStream(is);
	}

	private static final String TAG = "NativeBridge";
}
