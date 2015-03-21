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

    private void logByteArray(byte[] data)
    {
        logByteArray(data, 10);
    }

    private void logByteArray(byte[] data, int len)
    {
        String start = "";
        for(int i=0; i<len && i<data.length; i++)
        {
            start += String.format("%02x", data[i] & 0xff);
        }
        int i=data.length-len;
        if(i<0)
        {
            i=0;
        }
        String end = "";
        for(; i<data.length; i++)
        {
            end += String.format("%02x", data[i] & 0xff);
        }
        Log.v(TAG, ""+data.length+" bytes "+start+"..."+end+".");
    }

	public boolean validateImage(byte[] data) throws IOException
	{
		Log.v(TAG, "validating image...");
        logByteArray(data);
        Bitmap bitmap = BitmapFactory.decodeByteArray(data, 0, data.length);
        return bitmap != null;
    }

    private byte[] reverseImageArray(byte[] data, int components)
    {
        for(int i=0; i<data.length/2; i+=components)
        {
            for(int j=0;j<components; j++)
            {
                int a = i+j;
                int b = data.length-components-i+j;
                byte temp = data[a];
                data[a] = data[b];
                data[b] = temp;
            }
        }
        return data;
    }

	public byte[] loadImage(byte[] data) throws IOException
	{
		Log.v(TAG, "loading image...");
        logByteArray(data);
		BitmapFactory.Options options = new BitmapFactory.Options();
        options.inScaled = false;
        options.inPremultiplied = false;
        options.inJustDecodeBounds = false;
        options.inPreferredConfig = Bitmap.Config.ARGB_8888;
        Bitmap bitmap = BitmapFactory.decodeByteArray(data, 0, data.length, options);
        if(bitmap != null)
        {
            Log.v(TAG, "loaded bitmap "+bitmap.getConfig());
		    int bytes = bitmap.getByteCount();
            mImageInfo = new int[]{
                bitmap.getWidth(),
                bitmap.getHeight(),
                1,
            };
		    ByteBuffer buffer = ByteBuffer.allocate(bytes);
		    bitmap.copyPixelsToBuffer(buffer);
		    return reverseImageArray(buffer.array(), 4);
        }
        else
        {
            Log.v(TAG, "failed to decode image");
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
		byte[] data = readInputStream(is);
        logByteArray(data);
        return data;
	}

	private static final String TAG = "NativeBridge";
}
