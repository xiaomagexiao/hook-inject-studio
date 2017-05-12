package com.example.mama.readmemory;

/**
 * # long类型的要小写，不能大写
 */

public class NativeHookHelper {
    /**
     * 先调用initso
     */
    public static native String initso();
    public static native void test();
    public static native void init(long value);
    public static native void bigger();
    public static native void equal();
    public static native void smaller();
    public static native void newValue(long newValue);
    public static native void clear();
    public static native void printResult();
    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("hook");
        NativeHookHelper.initso();
    }

    public static native void setValue(long address, long value);
}
