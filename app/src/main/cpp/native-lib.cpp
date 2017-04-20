#include <jni.h>
#include <iostream>
using namespace std;



extern "C"
JNIEXPORT void JNICALL
Java_com_example_mama_readmemosdfsdfry_HookHelper_test(
        JNIEnv *env, jclass type) {

    cout << "temp address: " << endl;
}
