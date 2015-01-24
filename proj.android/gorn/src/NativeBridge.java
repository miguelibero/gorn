package me.ibero.gorn;

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
    private int[] mImageInfo;

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

	public byte[] loadImage(byte[] data) throws IOException
	{
		Log.v(TAG, "loading image of "+data.length+" bytes...");
		BitmapFactory.Options options = new BitmapFactory.Options();
        options.inScaled = false;
        Bitmap bitmap = BitmapFactory.decodeByteArray(data, 0, data.length, options);
        if(bitmap != null)
        {
		    int bytes = bitmap.getByteCount();
            mImageInfo = new int[]{
                bitmap.getWidth(),
                bitmap.getHeight(),
                bitmap.hasAlpha()?1:0,
            };
		    ByteBuffer buffer = ByteBuffer.allocate(bytes);
		    bitmap.copyPixelsToBuffer(buffer);
		    return buffer.array();
        }
        else
        {
            mImageInfo = new int[]{0,0,0};
            return new byte[0];
        }
	}

    public int[] getImageInfo()
    {
        return mImageInfo;
    }

	public boolean validateFile(String name)
	{
		Log.v(TAG, "validating file '" + name + "'...");
		AssetManager am = mActivity.getAssets();
        try
        {
            am.open(name);
            return true;
        }
        catch (IOException ex)
        {
            return false;
        }
	}

	public byte[] loadFile(String name) throws IOException
	{
		Log.v(TAG, "loading file '" + name + "'...");
		AssetManager am = mActivity.getAssets();
		InputStream is = am.open(name);
		return readInputStream(is);
	}

	private static final String TAG = "NativeBridge";
}
