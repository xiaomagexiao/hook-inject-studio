package com.hook.dex;

/**
 * Created by mama on 2017/4/15.
 */

public class HookDexHelper {
    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public static native void test();

    static {
        System.loadLibrary("inject-dex");
    }

}
