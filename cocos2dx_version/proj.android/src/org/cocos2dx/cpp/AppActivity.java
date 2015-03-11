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

import org.cocos2dx.lib.Cocos2dxActivity;

import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.view.Gravity;
import android.view.WindowManager;
import android.widget.LinearLayout;

import com.google.android.gms.ads.AdListener;
import com.google.android.gms.ads.AdRequest;
import com.google.android.gms.ads.AdSize;
import com.google.android.gms.ads.AdView;
import com.google.android.gms.ads.InterstitialAd;
import com.google.android.gms.games.Games;
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
 	// For Admob [-]
	
	/* Your ad unit id. Replace with your actual ad unit id. */
	private static final String AD_UNIT_ID_FOR_FULL = "ca-app-pub-5164818819958072/3969069148";
	private static final String AD_UNIT_ID = "ca-app-pub-5164818819958072/4026114746";
    
    @Override
    public void onSignInSucceeded(){
        gpgAvailable = true;
    }
    
    @Override
    public void onSignInFailed(){
        gpgAvailable = false;
    }
    
    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        
    	mActivity = this;
    	


    	
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
		            showInterstitial();
		        }
			});
    	}
        
        
        super.onCreate(savedInstanceState);
    }
    
    
    public void showAdmob ()
    {
    	if (isAdmobInited || admobView == null) {
    		return;
    	}

    	// OnCreate 에서 호출할때는 액티비티 실행 사이클이 모드 끝나기 전에 호출하므로 post 함수로 시작 사이클이 끝나고 Runable 을 실행함.
    	// Runnable 내의 코드들은 UI 스레드에서 실행.
    		
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
    
    static private void showInterstitial()
    {
      mActivity.runOnUiThread(new Runnable() 
      {
           
        @Override
        public void run() {
          if (interstitial.isLoaded())
          {
        	  
        	  interstitial.show();
          }
        }
      });
    }
    
    
    /*@brief Changes the actvie leaderboard
      @param The index of the leaderboard
    */
    static public void openLeaderboard(int leaderboardID){
         currentID = leaderboardID;
    }
    
    /*@brief This function opens the leaderboards ui for an leaderboard id*/
    static public void openLeaderboardUI(){
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


