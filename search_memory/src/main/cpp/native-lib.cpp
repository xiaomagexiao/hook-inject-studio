#include <jni.h>
#include <string>
#include "Util.h"
#include "Test.h"
#include "ScanMemory.h"

static ScanMemory *pMemory = new ScanMemory();



extern "C"
JNIEXPORT void JNICALL
Java_com_example_mama_readmemory_NativeHookHelper_printResult(JNIEnv *env, jclass type) {

    pMemory->printResult();

}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_mama_readmemory_NativeHookHelper_setValue(JNIEnv *env,
                                                             jclass type,
                                                             jlong address,
                                                             jlong value) {
    cout << "change " << hex << address << "'s value to " << value << endl;
    long *pValue = (long *) address;
    *pValue = (long) value;
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_mama_readmemory_NativeHookHelper_initso(
        JNIEnv *env, jclass type) {
    string hello = "Hello from C++";
    freopen("/data/local/tmp/loglog.txt", "w", stdout);
    return env->NewStringUTF(hello.c_str());
}

int temp = 7777;

extern "C"
JNIEXPORT void JNICALL
Java_com_example_mama_readmemory_NativeHookHelper_bigger(JNIEnv *env, jclass type) {
    temp++;
    pMemory->bigger();
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_mama_readmemory_NativeHookHelper_equal(JNIEnv *env, jclass type) {
    pMemory->equal();
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_mama_readmemory_NativeHookHelper_smaller(JNIEnv *env, jclass type) {
    temp = temp - 10;
    pMemory->smaller();
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_mama_readmemory_NativeHookHelper_newValue(JNIEnv *env, jclass type,
                                                             jlong newValue) {
    pMemory->newValue(newValue);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_mama_readmemory_NativeHookHelper_clear(JNIEnv *env, jclass type) {
    pMemory->clear();
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_mama_readmemory_NativeHookHelper_init(JNIEnv *env, jclass type, jlong value) {
    pMemory->initWithVlaue(value);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_mama_readmemory_NativeHookHelper_test(
        JNIEnv *env, jclass type) {
    std::string hello = "Hello from C++";
    printf("%s\n", hello.c_str());
    Test test;
//    test.testCreateFolder();
//    test.testGetMaps();
//    test.testGetMapsWithFilter();
//    test.testGetMapsInfoWithFilter();
//    test.testScanMemory();
    ScanMemory scanMemory;
    scanMemory.initWithVlaue(7777);
    cout << "temp address: " << hex << &temp << endl;
}
