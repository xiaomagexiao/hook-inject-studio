#include <jni.h>
#include <string>
using namespace std;

#include "log.h"



extern "C" int hook();
extern "C"
JNIEXPORT void JNICALL
Java_com_hook_InjectSoHelper_test(JNIEnv *env, jclass type) {

    LOGE("i am in222!!!");
    hook();
}