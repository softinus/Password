package org.cocos2dx.cpp;

import android.app.Application;
import android.util.Log;

import com.parse.Parse;
import com.parse.ParseException;
import com.parse.ParsePush;
import com.parse.SaveCallback;

public class MainApp extends Application {

	@Override
	public void onCreate() 
	{
		// Enable Local Datastore.
		Parse.enableLocalDatastore(this);
		Parse.initialize(this, "OAWkpBaiKlCiyItu6swfYpjV8Y87DSdeZiqlBOOv", "0vwC4qqhxGtbTTrWcqQyxacafUXG4PYay66N5DrG");

		ParsePush.subscribeInBackground("Password", new SaveCallback() {
			  @Override
			  public void done(ParseException e) {
			    if (e == null) {
			      Log.d("com.parse.push", "=======successfully subscribed to the broadcast channel.");
			    } else {
			      Log.e("com.parse.push", "=======failed to subscribe for push", e);
			    }
			  }
			});
		
		super.onCreate();
	}

}
