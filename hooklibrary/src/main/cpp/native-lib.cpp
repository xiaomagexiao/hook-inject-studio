#include <jni.h>
#include <string>
using namespace std;

#include "log.h"
extern "C"
JNIEXPORT void JNICALL
Java_com_hook_HookHelper_test(JNIEnv *env, jclass type) {

    LOGE("i am in222!!!");
}