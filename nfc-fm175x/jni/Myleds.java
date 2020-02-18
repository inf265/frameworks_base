package com.android.music;

public class Myleds {
	public native int open();
    public native int close();
    public native int ioctl(int num, int en);
    public native int read(byte[] buf,int len);
    public native int write(byte[] msg,int len);
}
