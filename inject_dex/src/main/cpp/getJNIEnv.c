#include <jni.h>
#include <stdio.h>
#include <dlfcn.h>
#include <android/log.h>
/*
JNI_VERSION_1_1 0x00010001
JNI_VERSION_1_2 0x00010002
JNI_VERSION_1_4 0x00010004
JNI_VERSION_1_6 0x00010006*/

#define ENABLE_LOG 1
#if ENABLE_LOG
#define LOGE(...) ((void) __android_log_print(ANDROID_LOG_ERROR, "Dex_Injection", __VA_ARGS__))
#define LOGE(...) ((void) __android_log_print(ANDROID_LOG_DEBUG, "Dex_Injection", __VA_ARGS__))
#define LOGI(...) ((void) __android_log_print(ANDROID_LOG_INFO, "Dex_Injection", __VA_ARGS__))
#else
#define LOGE(format, args...)
#define LOGE(format, args...)
#define LOGI(format, args...)
#endif

void _init(char *args) {
    LOGE("-------------libgetJNIEnv.so is loaded!--------------\n");
}

int so_entry(char *package) {
    LOGE("so_entry is now running!\n");
    const char *dexPath;
    const char *className;
    const char *methodName;
    char dexOptDir[100] = {0};

    JNIEnv *(*getJNIEnv)();
    void *handle = dlopen("system/lib/libandroid_runtime.so", RTLD_NOW);
    getJNIEnv = dlsym(handle, "_ZN7android14AndroidRuntime9getJNIEnvEv");
    if (!getJNIEnv) {
        LOGE("can not find getJNIEnv!");
        return -1;
    }

    JNIEnv *env = getJNIEnv();

    jint ver;
    ver = (*env)->GetVersion(env);
    switch (ver) {

        case 0x00010001:
            LOGE("JNI version is JNI_VERSION_1_1");
            break;

        case 0x00010002:
            LOGE("JNI version is JNI_VERSION_1_2");
            break;

        case 0x00010004:
            LOGE("JNI version is JNI_VERSION_1_4");
            break;

        case 0x00010006:
            LOGE("JNI version is JNI_VERSION_1_6");
            break;

        default:
            LOGE("Unknown JNI_VERSION:0x%x", ver);
            break;
    }

    jclass stringClass, classLoaderClass, dexClassLoaderClass, targetClass;
    jmethodID getSystemClassLoaderMethod, dexClassLoaderContructor, loadClassMethod, targetMethod;
    jobject systemClassLoaderObject, dexClassLoaderObject;
    jstring dexPathString, dexOptDirString, classNameString, tmpString;
    jobjectArray stringArray;

    LOGE("-------------- now begin dex injection --------------");

    /* set dex dir */
    LOGE("step1ssssss: setting dex dir and opt dir...");
    dexPath = "/data/local/tmp/inject.apk";
    sprintf(dexOptDir, "/data/data/%s/cache", package);
    LOGE("MAGE cache dir=%s", dexOptDir);
    className = "com.example.dex.ui.Say";
    methodName = "show";
    LOGE("step1 finished!\n");


    /* Get SystemClasLoader */
    LOGE("step2: getting systemClassLoader method and invoke it to get systemClassLoader obeject...");
    stringClass = (*env)->FindClass(env, "java/lang/String");//获取String类
    classLoaderClass = (*env)->FindClass(env, "java/lang/ClassLoader");//获取classLoader类
    getSystemClassLoaderMethod = (*env)->GetStaticMethodID(env, classLoaderClass,
                                                           "getSystemClassLoader",
                                                           "()Ljava/lang/ClassLoader;");//获取classLoader中的getSystemClassLoader静态方法
    systemClassLoaderObject = (*env)->CallStaticObjectMethod(env, classLoaderClass,
                                                             getSystemClassLoaderMethod);//调用getSystemClassLoader静态方法来获取所属对象systemClassLoaderObject
    if (!systemClassLoaderObject) {
        LOGE("Failed to call systemClassLoaderObject");
        return -1;
    }
    LOGE("step2 finished!\n");

    /* Create DexClassLoader */
    LOGE("step3: using dexClassLoader class to create dexClassLoader object...");
    dexClassLoaderClass = (*env)->FindClass(env, "dalvik/system/DexClassLoader");//获取dexClassLoader类
    LOGE("step3: 1111");
    dexClassLoaderContructor = (*env)->GetMethodID(env, dexClassLoaderClass, "<init>",
                                                   "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/ClassLoader;)V");//获取dexClassLoader的Contructor
    LOGE("step3: 2222");
    dexPathString = (*env)->NewStringUTF(env, dexPath);//将char*转换成jString
    LOGE("step3: 3333");
    dexOptDirString = (*env)->NewStringUTF(env, dexOptDir);//将char*转换成jString
    LOGE("step3: 4444");
    dexClassLoaderObject = (*env)->NewObject(env, dexClassLoaderClass, dexClassLoaderContructor,
                                             dexPathString, dexOptDirString, NULL,
                                             systemClassLoaderObject);//生成自定义的dexClassLoader对象
    LOGE("step3 finished!\n");
    LOGE("eeeerrrrrrrrrrrrrrrrrrrrrrrr");
    // dexClassLoaderObject return null
    if (!dexClassLoaderObject) {
        LOGE("fail dex classLoader");
        return -1;
    }
    /* Use DexClassLoader to load target class */
    LOGE("step4: using dexClassLoader class to find [loadClass] method and using dexClassLoader object created above to load target class:[%s]...",
         className);
    loadClassMethod = (*env)->GetMethodID(env, dexClassLoaderClass, "loadClass",
                                          "(Ljava/lang/String;)Ljava/lang/Class;");//获取dexClassLoader类中的“loadClass”方法
    classNameString = (*env)->NewStringUTF(env, className);////将char*转换成jString
    targetClass = (jclass) (*env)->CallObjectMethod(env, dexClassLoaderObject, loadClassMethod,
                                                    classNameString); //调用“loadClass”方法来获取目标类：com.wuchao.dextobeinjectd.wuchao
    if (!targetClass) {
        LOGE("Failed to load target class [%s]", className);
        return -1;
    }
    LOGE("step4 finished!\n");

    /* Invoke target method */
    LOGE("step5: using [%s] class loaded above to find [%s] method and invoke it...", className,
         methodName);
    targetMethod = (*env)->GetStaticMethodID(env, targetClass, methodName,
                                             "()V");//获取目标类中的静态方法：methodToBeInvoked
    if (!targetMethod) {
        LOGE("Failed to load target method [%s]", methodName);
        return -1;
    }
    (*env)->CallStaticVoidMethod(env, targetClass, targetMethod);//调用目标静态方法
    LOGE("step5 finished, invoking [%s] method succeeded!", methodName);

    return 0;
}

