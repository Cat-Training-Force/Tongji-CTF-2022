#include <jni.h>
#include <string>
#include <android/log.h>

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_easydroid_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */,jstring js) {
    jboolean isCopy=false;
    const char *input=env->GetStringUTFChars(js,&isCopy);
    char s[1024];
    memset(s,0,1024);
    size_t len=strlen(input);
    if(len>=1024)exit(0);
    memcpy(s,input,len);
    char res[1024];
    memset(res,0,1024);
    char tab[]="abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ+/";
    for(size_t i=0;i<len;i++){
        s[i]^=i;
    }
    size_t cnt=0;
    for(size_t i=0;i<len;i+=3){
        res[cnt++]=tab[(s[i]>>2)&0x3f];
        res[cnt++]=tab[(s[i]<<4)&0x30|(s[i+1]>>4)&0xf];
        res[cnt++]=tab[(s[i+1]<<2)&0x3c|(s[i+2]>>6)&0x3];
        res[cnt++]=tab[(s[i+2])&0x3f];
    }
    return env->NewStringUTF(res);
}