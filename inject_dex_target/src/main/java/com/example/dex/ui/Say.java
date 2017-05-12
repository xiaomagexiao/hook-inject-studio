package com.example.dex.ui;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.util.Log;
import android.widget.Toast;

import com.example.dex.util.HookTool;
import com.example.mama.readmemory.NativeHookHelper;

import org.json.JSONException;
import org.json.JSONObject;

import java.math.BigInteger;

/**
 * 接收广播来控制测试
 * adb shell am broadcast -a inject.cmd --es cmd {"action":"init"--"value":"100"}
 * adb shell am broadcast -a inject.cmd --es cmd {"action":"bigger"}
 * adb shell am broadcast -a inject.cmd --es cmd {"action":"smaller"}
 * adb shell am broadcast -a inject.cmd --es cmd {"action":"equal"}
 * adb shell am broadcast -a inject.cmd --es cmd {"action":"newValue"--"value":""}
 * adb shell am broadcast -a inject.cmd --es cmd {"action":"clear"}
 * adb shell am broadcast -a inject.cmd --es cmd {"action":"printResult"}
 * adb shell am broadcast -a inject.cmd --es cmd {"action":"setValue"--"value":"100"--"address":"0x2222"}
 * <p>
 * public static native void init(long value);
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
        cmd = cmd.replace("{", "{'").replace(":", "':'").replace(",", "','").replace("}", "'}");
        Log.e("MAGE", "cmd = " + cmd);
        JSONObject jsoncmd = new JSONObject(cmd);
        String action = jsoncmd.optString("action");
        String value = jsoncmd.optString("value");
        String address = jsoncmd.optString("address");
        if ("init".equals(action)) {
            NativeHookHelper.init(Long.valueOf(value));
        } else if ("bigger".equals(action)) {
            NativeHookHelper.bigger();
        } else if ("smaller".equals(action)) {
            NativeHookHelper.smaller();
        } else if ("equal".equals(action)) {
            NativeHookHelper.equal();
        } else if ("newValue".equals(action)) {
            NativeHookHelper.newValue(Long.valueOf(value));
        } else if ("clear".equals(action)) {
            NativeHookHelper.clear();
        } else if ("printResult".equals(action)) {
            NativeHookHelper.printResult();
        } else if ("setValue".equals(action)) {
            if (address == null || address.trim().length() == 0) {
                Log.e("MAGE say", "error address[" + address + "] for set!!!");
                return;
            }
            setValue(strToLong(address), Long.valueOf(value));
            Log.e("MAGE", "setValue = " + 123);
        }
        Log.e("MAGE", "version = " + 123);
    }

    private static void setValue(long address, long value) {
        Log.e("MAGE", "address = " + address + ", value = " + value);
        NativeHookHelper.setValue(address, value);
    }

    private static long strToLong(String address) {
        return new BigInteger(address, 16).longValue();
    }

}
