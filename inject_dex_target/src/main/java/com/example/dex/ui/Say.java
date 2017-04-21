package com.example.dex.ui;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.util.Log;
import android.widget.Toast;

import com.example.dex.util.HookTool;



public class Say {
	static BroadcastReceiver br = new BroadcastReceiver() {
		@Override
		public void onReceive(Context context, Intent intent) {

		}
	};
	public static void show() {
		Log.e("MAGE say", "MAGE dex inject ok i am been called>>>>>>!!!!");
		Toast.makeText(HookTool.getContext(), "dex inject ok ", 0).show();
		HookTool.getContext().registerReceiver(br, new IntentFilter());
	}
}
