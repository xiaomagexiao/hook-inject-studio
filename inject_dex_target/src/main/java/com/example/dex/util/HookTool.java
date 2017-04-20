package com.example.dex.util;

import android.content.Context;
import android.os.Handler;
import android.util.Log;

public class HookTool {
	public static final String TAG = "MAGE";
	public static Context mContext;

	public static void dexInject() {
		Log.e(TAG, TAG + "this is dex code,welcome to HookTool~");
		try {
			Object currentActivityThread = ReflectUtils.invokeStaticMethod("android.app.ActivityThread", "currentActivityThread",
					new Class[] {}, new Object[] {});
			Log.e(TAG, TAG + "-" + currentActivityThread);
			Handler localHandler = (Handler) ReflectUtils.getFieldValue(currentActivityThread, "mH");
			Log.e(TAG, TAG + "-" + localHandler);
			HookCallback oriCallback = (HookCallback) ReflectUtils.getFieldValue(localHandler, "mCallback");
			Log.e(TAG, TAG + "-" + oriCallback);
			HookCallback hookCallBack = new HookCallback(oriCallback);
			Log.e(TAG, TAG + "-" + hookCallBack);
			ReflectUtils.setFieldValue(localHandler, "mCallback", hookCallBack);
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	public static Context getContext() {
		if (mContext == null) {
			try {
				mContext = ActivityThread.getSystemContext();
			} catch (Exception e) {
				e.printStackTrace();
			}
		}
		Log.e(TAG, TAG + "mContext = " + mContext);
		return mContext;
	}

}