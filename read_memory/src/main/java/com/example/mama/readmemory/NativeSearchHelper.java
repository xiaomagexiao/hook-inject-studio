package com.example.mama.readmemory;

/**
 * Created by mama on 2017/4/15.
 */

public class NativeSearchHelper {
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
    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("search");
    }
}
