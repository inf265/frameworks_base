#include <jni.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <stdint.h>
#include <termios.h>
#include <android/log.h>
#include <sys/ioctl.h>
#include "Java_com_yf_lib_tigerbox_tigertones_NativeHelper.h"

int fd=0;


//com.yf.tigerbox
JNIEXPORT jint JNICALL Java_com_yf_lib_tigerbox_tigertones_NativeHelper_open(JNIEnv *env, jobject obj)
{
	int f_flags;
	
	if(fd<=0)fd = open("/dev/mf175x",O_RDWR);
	if(fd <=0 )__android_log_print(ANDROID_LOG_INFO, "mf175x", "open /dev/mf175x Error");
	else __android_log_print(ANDROID_LOG_INFO, "mf175x", "open /dev/mf175x Sucess fd=%d",fd);
		
    
	return fd;
}

JNIEXPORT jint JNICALL Java_com_yf_lib_tigerbox_tigertones_NativeHelper_close(JNIEnv *env, jobject obj)
{
	if(fd > 0)close(fd);
	return 0;
}

JNIEXPORT jint JNICALL Java_com_yf_lib_tigerbox_tigertones_NativeHelper_ioctl(JNIEnv *env, jobject obj, jint en, jint num)
{
	jint ret;
	ret=ioctl(fd, en, num);
	return ret;
}


JNIEXPORT jint JNICALL Java_com_yf_lib_tigerbox_tigertones_NativeHelper_read(JNIEnv *env, jobject obj, jbyteArray buffer, jint length)
{
	jint ret;
	jbyte *pBuffer=env->GetByteArrayElements(buffer,NULL);
	ret=read(fd,pBuffer,length);
	env->ReleaseByteArrayElements(buffer,pBuffer,0);
	//__android_log_print(ANDROID_LOG_INFO, "mf175x", "length=%d",length);
	//__android_log_print(ANDROID_LOG_INFO, "mf175x", "ret=%d",ret);
	return ret;
}

JNIEXPORT jint JNICALL Java_com_yf_lib_tigerbox_tigertones_NativeHelper_write(JNIEnv *env, jobject obj, jbyteArray msg, jint length)
{
	jint ret;
	jbyte pBuffer[length];
	env->GetByteArrayRegion(msg,0,length,pBuffer);
	ret=write(fd,pBuffer,length);
	return ret;
}
