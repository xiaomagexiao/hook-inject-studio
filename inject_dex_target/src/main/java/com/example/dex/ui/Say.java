package com.example.dex.ui;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.util.Log;
import android.widget.Toast;

import com.example.dex.util.HookTool;
import com.example.mama.readmemory.NativeSearchHelper;

import org.json.JSONException;
import org.json.JSONObject;

/**
接收广播来控制测试
aadb shell am broadcast -a inject.cmd --es cmd {"action":"init"--"value":"100"}
aadb shell am broadcast -a inject.cmd --es cmd {"action":"bigger"}
aadb shell am broadcast -a inject.cmd --es cmd {"action":"smaller"}
aadb shell am broadcast -a inject.cmd --es cmd {"action":"equal"}
aadb shell am broadcast -a inject.cmd --es cmd {"action":"newValue"--"value":""}
aadb shell am broadcast -a inject.cmd --es cmd {"action":"clear"}

public static native void init(long value);
 * public static native void bigger();
 * public static native void equal();
 * public static native void smaller();
 * public static native void newValue(long newValue);
 * public static native void clear();
 */
public class Say {
    static String intentAction = "inject.cmd";
    public static String COMMAND_NAME_KEY = "cmd";
    public static BroadcastReceiver br = new BroadcastReceiver() {
        @Override
        public void onReceive(Context context, Intent intent) {
            if (intentAction.equals(intent.getAction())) {
                Log.e("MAGE", "accept action: " + intent.getAction());
//				Log.e("MAGE", intent.getDataString());
                try {
                    executeTest(intent);
                } catch (Exception e) {
                    e.printStackTrace();
                }
            }
        }
    };

    public static void show() {
        NativeSearchHelper.initso();
        Log.e("MAGE say", "MAGE dex inject ok i am been called>>>>>>!!!!");
        Toast.makeText(HookTool.getContext(), "dex inject ok ", Toast.LENGTH_LONG).show();
        IntentFilter filter = new IntentFilter();
        filter.addAction(intentAction);
        HookTool.getContext().registerReceiver(br, filter);
    }

    private static void executeTest(Intent arg1) throws JSONException {
        String cmd = arg1.getStringExtra(COMMAND_NAME_KEY);
        if (cmd == null || cmd.trim().length() == 0) {
            return;
        }
        if (cmd.contains("--")) {
            cmd = cmd.replace("--", ",");
        }
        Log.e("MAGE", "cmd = " + cmd);
        JSONObject jsoncmd = new JSONObject(cmd);
        String action = jsoncmd.optString("action");
        String value = jsoncmd.optString("value");
        if ("init".equals(action)) {
            NativeSearchHelper.init(Long.valueOf(value));
        } else if ("bigger".equals(action)) {
            NativeSearchHelper.bigger();
        } else if ("smaller".equals(action)) {
            NativeSearchHelper.smaller();
        } else if ("equal".equals(action)) {
            NativeSearchHelper.equal();
        } else if ("newValue".equals(action)) {
            NativeSearchHelper.newValue(Long.valueOf(value));
        } else if ("clear".equals(action)) {
            NativeSearchHelper.clear();
        }
    }

}
