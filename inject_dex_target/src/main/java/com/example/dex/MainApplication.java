package com.example.dex;

import android.app.Application;
import android.content.Context;

public class MainApplication extends Application {
	private static Context context;
	private static String packageName;

	public static Context getInstance() {
		return context;
	}

	@Override
	public void onCreate() {
		super.onCreate();
		initMoocApplication(this);
	}

	public static String getMainPackageName() {
		if (packageName == null) {
			packageName = context.getPackageName();
		}
		return packageName;
	}
	
	/**
	 * 不继承该类的时候调用此方法进行初始化。
	 * @param icontext
	 */
	public static void initMoocApplication(Context icontext){
		if(context == null){
			context = icontext;
		}
	}
}
