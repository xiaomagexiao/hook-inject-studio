package com.example.dex.ui;

import android.util.Log;
import android.widget.Toast;

import com.example.dex.util.HookTool;


public class Say {

	public static void show() {
		Log.e("MAGE say", "MAGE dex inject ok i am been called!!!!");
		Toast.makeText(HookTool.getContext(), "dex inject ok ", 0).show();
	}
}
