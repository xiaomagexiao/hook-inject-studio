package com.example.dex.util;

import java.lang.reflect.Field;

import android.content.Context;

public final class ActivityThread {
	private static final String CLASS_NAME = "android.app.ActivityThread";
	private static Field sInitialApplication_field;
	private static Field sSystemContext_field;

	/**
	 * get Application object form ActivityThread object.
	 * 
	 * @param object
	 *            ActivityThread object
	 * @return
	 */
	public static Object getInitialApplication(Object object) throws Exception {
		Object app = null;

		if (object != null && CLASS_NAME.equals(object.getClass().getName())) {

			if (sInitialApplication_field == null) {
				Class<?> ActivityThread_class = object.getClass();
				sInitialApplication_field = ActivityThread_class.getDeclaredField("mInitialApplication");
				sInitialApplication_field.setAccessible(true);
			}

			if (sInitialApplication_field != null) {
				app = sInitialApplication_field.get(object);
			}
		}

		return app;
	}

	public static Context getSystemContext() throws Exception {
		Object currentActivityThread = ReflectUtils.invokeStaticMethod("android.app.ActivityThread", "currentActivityThread",
				new Class[] {}, new Object[] {});
		if (sSystemContext_field == null) {
			Class<?> ActivityThread_class = Class.forName("android.app.ActivityThread");
			sSystemContext_field = ActivityThread_class.getDeclaredField("mSystemContext");
			sSystemContext_field.setAccessible(true);
		}
		return (Context) sSystemContext_field.get(currentActivityThread);
	}

}
