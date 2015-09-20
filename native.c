//add for git commit
//nothing
#include <stdio.h>
//#include <jni.h>
#include </usr/lib/jvm/java-1.7.0-openjdk-i386/include/jni.h> //loacte at /usr/lib/jvm/java-1.7.0-openjdk-i386/include/(PC)
#include <stdlib.h>
//compiling command:
//gcc -I /usr/lib/jvm/java-1.7.0-openjdk-i386/include/ -shared -o libnative.so native.c
//or
//#include </usr/lib/jvm/java-1.7.0-openjdk-i386/include/jni.h> and with command:
//gcc -shared -o libnative.so native.c

//option shared: Produce a shared object which can then be linked with other objects to form an executable. 

#if 0
typedef struct {
    char *name;          /* Java里调用的函数名 */
    char *signature;    /* JNI字段描述符, 用来表示Java里调用的函数的参数和返回值类型 */
    void *fnPtr;          /* C语言实现的本地函数 */
} JNINativeMethod;
#endif
jintArray c_hello(JNIEnv *env, jobject cls, jintArray arr)
{
	jint *carr;
	jint *oarr;
	jint i, length = 0;
	jintArray rarr;
	carr = (*env)->GetIntArrayElements(env, arr, NULL);
	if (carr == NULL) {
		return 0; /* exception occurred */
	}

    	//func ptr definition(in jni.h): jsize (JNICALL *GetArrayLength)(JNIEnv *env, jarray array);
	length = (*env)->GetArrayLength(env, arr);
	oarr = malloc(sizeof(jint) * length);
	if(oarr == NULL)
	{
		(*env)->ReleaseIntArrayElements(env, arr, carr, 0);
		return 0;
	}
	for(i = 0; i < length; i++)
	{
		oarr[i] = carr[length - 1 -i];
	}
 	//release
	(*env)->ReleaseIntArrayElements(env, arr, carr, 0);

	/* create jintArray(allocate memory by env, but value is not set yet.) */
	rarr = (*env)->NewIntArray(env, length);
	if(rarr == NULL)
		return 0;
	//copy oarr array to jintArray type array rarr
	//void (JNICALL *SetIntArrayRegion)(JNIEnv *env, jintArray array, jsize start, jsize len, const jint *buf);	
	(*env)->SetIntArrayRegion(env, rarr, 0, length, oarr);
	free(oarr); //correpsond to malloc
	
	return rarr;
}

static const JNINativeMethod methods[] = {
	{"hello", "([I)[I", (void *)c_hello}, //the middle one is signature. you can run(after compiling) "javah -jni JNIDemo" to generate JNIDemo.h which provides 
							//signatures of all native methods.
#if 0
	{"hello", "()V", (void *)c_hello},
	{"hello", "()V", (void *)c_hello},
	{"hello", "()V", (void *)c_hello},
#endif	
};

JNIEXPORT jint JNICALL
JNI_OnLoad(JavaVM *jvm, void *reserved)
{
	JNIEnv *env;
	jclass cls;

	if ((*jvm)->GetEnv(jvm, (void **)&env, JNI_VERSION_1_4)) {
		return JNI_ERR; /* JNI version not supported */
	}
	cls = (*env)->FindClass(env, "JNIDemo"); //public class JNIDemo in JNIDemo.java
	if (cls == NULL) {
		return JNI_ERR;
	}
	//2. map c_hello() to hello() in java
	if((*env)->RegisterNatives(env, cls, methods, 1) < 0) /* 1 means the number of members in array methods */
		return JNI_ERR;
	return JNI_VERSION_1_4;
}


