package org.cocos2dx.cpp;

import android.app.Application;

import com.parse.Parse;

public class MainApp extends Application {

	@Override
	public void onCreate() 
	{
		// Enable Local Datastore.
		Parse.enableLocalDatastore(this);
		Parse.initialize(this, "OAWkpBaiKlCiyItu6swfYpjV8Y87DSdeZiqlBOOv", "0vwC4qqhxGtbTTrWcqQyxacafUXG4PYay66N5DrG");

		
		super.onCreate();
	}

}
