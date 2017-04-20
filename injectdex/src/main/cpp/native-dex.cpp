#include <jni.h>
#include "log.h"

extern "C"
JNIEXPORT void JNICALL
Java_com_hook_dex_HookDexHelper_test(JNIEnv *env, jclass type) {

    LOGE("i am hook dex!!!");
}