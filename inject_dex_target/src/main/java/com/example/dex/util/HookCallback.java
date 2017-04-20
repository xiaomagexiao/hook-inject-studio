package com.example.dex.util;

import android.os.Handler.Callback;
import android.os.Message;
import android.util.Log;

public class HookCallback implements Callback {
	public static final int RESUME_ACTIVITY = 107;
	public static final int PAUSE_ACTIVITY = 101;
	private Callback mParentCallback;

	public HookCallback(Callback parentCallback) {
		mParentCallback = parentCallback;
	}

	@Override
	public boolean handleMessage(Message msg) {
		switch (msg.what) {
		case RESUME_ACTIVITY:
			Log.e(HookTool.TAG, HookTool.TAG + "hook activity resume!!!");
			break;
		case PAUSE_ACTIVITY:
			Log.e(HookTool.TAG, HookTool.TAG + "hook activity pause!!!");
		default:
			Log.e(HookTool.TAG, HookTool.TAG + "hook a " + msg.what);
			break;
		}
		if (mParentCallback != null) {
			return mParentCallback.handleMessage(msg);
		} else {
			return false;
		}
	}
}