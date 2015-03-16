/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
Copyright (c) 2013-2014 Chukong Technologies Inc.
Copyright (c) 2014 Adrian Dawid
 
http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
package org.cocos2dx.cpp;

import java.util.List;

import org.cocos2dx.lib.Cocos2dxActivity;

import android.accounts.Account;
import android.accounts.AccountManager;
import android.app.AlertDialog;
import android.app.Dialog;
import android.app.ProgressDialog;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.telephony.TelephonyManager;
import android.text.TextUtils;
import android.view.Gravity;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.view.WindowManager;
import android.widget.EditText;
import android.widget.LinearLayout;

import com.google.android.gms.ads.AdListener;
import com.google.android.gms.ads.AdRequest;
import com.google.android.gms.ads.AdSize;
import com.google.android.gms.ads.AdView;
import com.google.android.gms.ads.InterstitialAd;
import com.google.android.gms.games.Games;
import com.parse.FindCallback;
import com.parse.LogInCallback;
import com.parse.ParseException;
import com.parse.ParseObject;
import com.parse.ParseQuery;
import com.parse.ParseUser;
import com.parse.SignUpCallback;
import com.softinus.pw.R;

public class AppActivity extends BaseGameActivity {
    static int currentID;
    static int currentAchievementID;
    static boolean gpgAvailable;
    
    static String[] leaderboardIDs;
    static String[] achievementIDs;
    static Context currentContext;
    
 // For Admob [+]
 	private AdView admobView;
 	static Cocos2dxActivity mActivity;
 	LinearLayout layout;
 	LinearLayout mainLayout;
 	boolean isAdmobInited = false;
 	static InterstitialAd interstitial;
 	
 	/* Your ad unit id. Replace with your actual ad unit id. */
 	private static final String AD_UNIT_ID_FOR_FULL = "ca-app-pub-5164818819958072/3969069148";
 	private static final String AD_UNIT_ID = "ca-app-pub-5164818819958072/4026114746";
 	
 	// For Admob [-]
 	
 	// for parse
 	private ProgressDialog LoadingDL;
	AccountManager mgr;
    Account[] accts;
    // for parse 
    
    @Override
    public void onSignInSucceeded()
    {
        gpgAvailable = true;
    }
    
    @Override
    public void onSignInFailed()
    {
        gpgAvailable = false;
    }
    
    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        
    	mActivity = this;
    	
        mgr= AccountManager.get(getApplicationContext());
        accts= mgr.getAccounts();
        
        LoadingDL = new ProgressDialog(this);
    	    	
    	// Create an ad.
    	admobView = new AdView(this);
    	admobView.setAdSize(AdSize.BANNER);
    	admobView.setAdUnitId(AD_UNIT_ID);
    	
    	showAdmob();
    	
    	
        String leaderboardIdsRaw = getString(R.string.leaderboards);
        String achievementIdsRaw = getString(R.string.achievements);
        
        
        leaderboardIDs = leaderboardIdsRaw.split(";");
        achievementIDs =  achievementIdsRaw.split(";");
        
        currentContext = this;
        
    	{
			// Create the interstitial.
			interstitial = new InterstitialAd(this);
			interstitial.setAdUnitId(AD_UNIT_ID_FOR_FULL);
			

    	}
    	
    	//sendParse();
    	//ShowSignForm();
    	
        
        super.onCreate(savedInstanceState);
    }

	static public void InitParse() 
	{
		ParseUser currentUser = ParseUser.getCurrentUser();
		if (currentUser != null)
		{
			ParseObject userInfo = new ParseObject("UserInfo");
			userInfo.put("user_id", currentUser);
			userInfo.put("coin", 0);
			userInfo.saveInBackground();
		}
	}
	
	static public void earnCoins(final int nCount)
	{
		ParseUser currentUser = ParseUser.getCurrentUser();
		if (currentUser != null)
		{
			ParseQuery<ParseObject> query= ParseQuery.getQuery("UserInfo");	// 유저 데이터를 찾는다.
			query.whereEqualTo("user_id", currentUser);	// 해당되는 유저의
			query.findInBackground(new FindCallback<ParseObject>()
			{			
				@Override
				public void done(List<ParseObject> list, ParseException e)
				{
					for(ParseObject PO : list)
					{
						PO.increment("coin", nCount);
						PO.saveInBackground();
					}
				}
			});
		} else {
		  // show the signup or login screen
		}
	}
	
	static public void ShowSignForm()
	{
		mActivity.runOnUiThread(new Runnable() 
        {
	           
	        @Override
	        public void run()
	        {
	        	((AppActivity)currentContext).showDialog(R.layout.login_dialog);
	        }
        });
		
	}
	
	
	private void SignIn(final String strID, final String strPW)
	{
		ParseUser.logInInBackground(strID, strPW
				,new LogInCallback()
		{
		  public void done(ParseUser user, ParseException e)
		  {
		    if (user != null)
		    {
		    	LoadingHandler.sendEmptyMessage(3);
		    	
		    	SPUtil.putString(currentContext, "login_id", strID);
				SPUtil.putString(currentContext, "login_pw", strPW);    	        			
				
		    	//SPUtil.putBoolean(getApplicationContext(), Global.SP_LOGIN_SUCCESS, true);	
				LoadingHandler.sendEmptyMessage(999);
		    	
				//ShowAlertDialog("[Connected]", "end", "Ok");        	        			
				
		    } else {
		    	LoadingHandler.sendEmptyMessage(999);
		    	ShowAlertDialog("[Failed]", "check.", "Ok");
		    	
		    	SPUtil.putString(currentContext, "login_id", null);
		    	SPUtil.putString(currentContext, "login_pw", null);
		    	// �α��� �����ϸ� ����� ������ ����.
		    	
		        return;
		    }
		  }
		});
	}
	

    public Handler LoadingHandler = new Handler()
	{
		public void handleMessage(Message msg)
		{			
			if(msg.what==0)	// Play ��ư ������!
			{
				LoadingDL.hide();
				
				final String strID= SPUtil.getString(currentContext, "login_id");
				final String strPW= SPUtil.getString(currentContext, "login_pw"); 
				if( (strID!=null) && (strPW!=null) )	// ����� ID�� ������ �α����Ѵ�.
				{
					LoadingHandler.sendEmptyMessage(1);
					            		
            		SignIn(strID, strPW);
					
				}
				else
				{
					showDialog(R.layout.login_dialog);
				}
			}
			if(msg.what==1)
			{
				LoadingDL.setMessage("Sign in...");
		        LoadingDL.show();
			}
			if(msg.what==2)
			{
				LoadingDL.setMessage("Sign up...");
		        LoadingDL.show();
			}
			if(msg.what==3)
			{
				LoadingDL.setMessage("Getting information...");
		        LoadingDL.show();
			}
			if(msg.what==999)
			{
				LoadingDL.hide();
			}
		}
	};
	
	
    
    
    public void showAdmob ()
    {
    	if (isAdmobInited || admobView == null) {
    		return;
    	}
    	
    	//	mActivity.runOnUiThread (new Runnable () {
    	mainLayout = new LinearLayout (mActivity);
    	mainLayout.post (new Runnable () {
    			
    		@Override
    		public void run () {
    			AdRequest adRequest = new AdRequest.Builder().build();
    				
    			WindowManager wm = (WindowManager) mActivity.getSystemService ("window");
    				
    			WindowManager.LayoutParams mLayoutParams = new WindowManager.LayoutParams ();
    			mLayoutParams.type = WindowManager.LayoutParams.TYPE_APPLICATION_PANEL;
    			mLayoutParams.width = WindowManager.LayoutParams.WRAP_CONTENT;
    			mLayoutParams.height = WindowManager.LayoutParams.WRAP_CONTENT;
    			mLayoutParams.flags |= WindowManager.LayoutParams.FLAG_NOT_FOCUSABLE;
    			mLayoutParams.gravity = Gravity.BOTTOM;
    			
    			wm.addView (admobView, mLayoutParams);

    			// Enable this if your are testing AdMob, otherwise you'll risk to be banned!
    			//adRequest.addTestDevice (AdRequest.TEST_EMULATOR);
    			admobView.loadAd (adRequest);
    				
    			isAdmobInited = true;					
    		}
    	});
    }
    
    
    private void ShowAlertDialog(String strTitle, String strContent, String strButton)
	{
		new AlertDialog.Builder(this)
		.setTitle( strTitle )
		.setMessage( strContent )
		.setPositiveButton( strButton , null)
		.setCancelable(false)
		.create()
		.show();
	}
	
	
	
	@Override
	protected Dialog onCreateDialog(int id, Bundle args)
	{
		LayoutInflater factory = LayoutInflater.from(this);
	    final View LoginDialogView = factory.inflate(id, (ViewGroup) findViewById(R.layout.login_dialog));
	    
	    final EditText EDT_ID= (EditText) LoginDialogView.findViewById(R.id.edt_username);
    	final EditText EDT_PW= (EditText) LoginDialogView.findViewById(R.id.edt_password);
    	
    	for(Account acct : accts)	// account 목록
    	{
	    	if(acct.name.contains("@"))
	    	{
	    		EDT_ID.setText(acct.name);
	    		break;
	    	}
    	}
    	
	    return new AlertDialog.Builder(AppActivity.this)
	        .setIcon(android.R.drawable.ic_dialog_info)
	        .setTitle("Login or Sign up")
	        .setView(LoginDialogView)
	        .setPositiveButton("Sign in", new DialogInterface.OnClickListener()
	        {
	            public void onClick(DialogInterface dialog, int whichButton)
	            {
	            	
	            	
	            	if( TextUtils.isEmpty(EDT_ID.getText()) )
	            	{
	            		ShowAlertDialog("Sign in failed", "Please enter ID.", "Ok");
	            		showDialog(R.layout.login_dialog);
	            		//Toast.makeText(getApplicationContext(), "���̵� �Է����ּ���.", Toast.LENGTH_LONG).show();
	            	}
	            	else if( TextUtils.isEmpty(EDT_PW.getText()) )	            		
	            	{
	            		ShowAlertDialog("Sign in failed", "Please enter PW.", "Ok");
	            		showDialog(R.layout.login_dialog);
	            		//Toast.makeText(getApplicationContext(), "�н����带 �Է����ּ���.", Toast.LENGTH_LONG).show();
	            	}
	            	else
	            	{	            	
	            		LoadingHandler.sendEmptyMessage(1);
	            		
	            		SignIn(EDT_ID.getText().toString(), EDT_PW.getText().toString());
	            		
	            	}
	            	
	            	
	            }
	        })
	        .setNeutralButton("Sign up", new DialogInterface.OnClickListener()
	        {
	            public void onClick(DialogInterface dialog, int whichButton)
	            {
	            	if( TextUtils.isEmpty(EDT_ID.getText()) )
	            	{
	            		ShowAlertDialog("Sign up failed.", "Please enter ID.", "Ok");
	            	}
	            	else if( !EDT_ID.getText().toString().contains("@") )
	            	{
	            		ShowAlertDialog("Sign up failed.", "Please enter your ID correct email form :)", "Ok");
	            	}
	            	else if( TextUtils.isEmpty(EDT_PW.getText()) )	            		
	            	{
	            		ShowAlertDialog("Sign up failed.", "Please enter password.", "Ok");
	            		//Toast.makeText(getApplicationContext(), "�н����带 �Է����ּ���.", Toast.LENGTH_LONG).show();
	            	}
	            	else if( (4>EDT_PW.getText().length()) || (10<EDT_PW.getText().length()) )	            		
	            	{
	            		ShowAlertDialog("Sign up failed.", "Password must be 4~10 words.", "Ok");
	            		
	            	}
	            	else
	            	{
	            		LoadingHandler.sendEmptyMessage(2);
	            		
		        		String strNumber= null;
		        		String strIMEI= null;
		        		
		        		TelephonyManager TM = (TelephonyManager) getSystemService(Context.TELEPHONY_SERVICE); 
		        		if (TM.getSimState() == TelephonyManager.SIM_STATE_ABSENT)
		        		{
		        			strNumber= "usim_absent";
		        		} 
		        		else {
		        			strNumber= TM.getLine1Number();
		        			strIMEI= TM.getDeviceId();
		        		}
		        		
		        		ParseUser user = new ParseUser();
		        		user.setUsername(EDT_ID.getText().toString());
		        		user.setPassword(EDT_PW.getText().toString()	);
		        		user.setEmail(EDT_ID.getText().toString());
		        		 

		        		if(strNumber==null)
		        			user.put("phone", "usim_null");
		        		else
		        			user.put("phone", strNumber);
		        		 
		        		user.signUpInBackground(new SignUpCallback()
		        		{
		        		  public void done(ParseException e)
		        		  {
		        		    if (e == null)
		        		    {
		        		    	InitParse();	// 파스 초기화
		        		    	LoadingHandler.sendEmptyMessage(999);
		        		    	ShowAlertDialog("[Join success]", "Welcome abroad!\nPlease login again. +_+", "Ok");
    		                    return;
		        		    } else {
		        		    	LoadingHandler.sendEmptyMessage(999);
    		                	ShowAlertDialog("[Join failed]", "error code : "+e.getCode(), "Ok");
    		                    return;
		        		    }
		        		  }
		        		});
		        		
		        		
		        		 
	            	}
	            }
	        })
	        .setNegativeButton("Cancel", new DialogInterface.OnClickListener()
	        {
	            public void onClick(DialogInterface dialog, int whichButton)
	            {

	                /* User clicked cancel so do some stuff */
	            }
	        })
	        .create();
	}
	
    
    static public void showInterstitial()
    {
      mActivity.runOnUiThread(new Runnable() 
      {
           
        @Override
        public void run()
        {
			// Create ad request.
			AdRequest adRequest = new AdRequest.Builder().build();
			
			// Begin loading your interstitial.
			interstitial.loadAd(adRequest);
			interstitial.setAdListener(new AdListener()
			{
				@Override
		        public void onAdLoaded()
				{
		            // TODO Auto-generated method stub
		            super.onAdLoaded();
		            interstitial.show();
		        }
			});
        }
      });
    }
    
    
    
    
    /*@brief Changes the actvie leaderboard
      @param The index of the leaderboard
    */
    static public void openLeaderboard(int leaderboardID)
    {
         currentID = leaderboardID;
    }
    
    /*@brief This function opens the leaderboards ui for an leaderboard id*/
    static public void openLeaderboardUI()
    {
        if(gpgAvailable){
                ((AppActivity)currentContext).runOnUiThread(new Runnable() {
            public void run() {
                ((AppActivity)currentContext).startActivityForResult(Games.Leaderboards.getLeaderboardIntent(((AppActivity)currentContext).getGameHelper().getApiClient(), leaderboardIDs[currentID]),2);
            }
                });
        }
    }
    
    static public boolean isGPGSupported(){
        return gpgAvailable;
    }
    
    /*@brief Submits a score to the leaderboard that is currently actvie*/
    static public void submitScoreToLeaderboard(int score)
    {
        if(gpgAvailable){
        Games.Leaderboards.submitScore(((AppActivity)currentContext).getGameHelper().getApiClient(),leaderboardIDs[currentID],score);
        updateAchievement(100);
        }
    }
    
     /*@brief Shows the achievements ui*/
    static public void showAchievements() {
        if(gpgAvailable){
        ((AppActivity)currentContext).runOnUiThread(new Runnable() {
            public void run() {
                ((AppActivity)currentContext).startActivityForResult(Games.Achievements.getAchievementsIntent(((AppActivity)currentContext).getGameHelper().getApiClient()), 5);
            }
        });
        }
    }
    
    /*@brief Changes the actvie Achievement
      @param The index of the achievement in the list*/
    static public void openAchievement(int achievementID){
        currentAchievementID = achievementID;
    }
    
    static public void updateAchievement(int percentage){
        if(gpgAvailable){
       Games.Achievements.unlock(((AppActivity)currentContext).getGameHelper().getApiClient(), achievementIDs[currentAchievementID]);
        }
    }
    
    static public void exitGame()
    {
        Intent intent = new Intent(currentContext, MainActivity.class);
        MainActivity.exiting=true;
        currentContext.startActivity(intent);
    }
}


