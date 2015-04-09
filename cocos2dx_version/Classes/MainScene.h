#pragma once

#include "cocos2d.h"

#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
#include "CocosGUI.h"
#else
#include "ui\CocosGUI.h"
#endif

#include "SelectStageScene.h"
USING_NS_CC;

using namespace ui;


class MainScene : public cocos2d::Layer
{
public:
	static Scene* scene();
	CREATE_FUNC(MainScene);
	virtual bool init();

	EventListenerTouchOneByOne * listener;

	static Scene* createScene(void);
	void changeScene(void);

	virtual bool onTouchBegan(Touch* touch, Event* event);

	void scheduleCallback(float delta);	// schedule
	
	void Touch_start(Ref* sender, Widget::TouchEventType type);

	void Touch_signin(Ref* sender, Widget::TouchEventType type);

	void Touch_help(Ref* sender, Widget::TouchEventType type);
	void Touch_achievement(Ref* sender, Widget::TouchEventType type);

	void Touch_ranking(Ref* sender, Widget::TouchEventType type);
	void Touch_credits(Ref* sender, Widget::TouchEventType type);

	void Touch_sound(Ref* sender, Widget::TouchEventType type);
	void Touch_setting(Ref* sender);
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event *event);
	
	void ShowPopup_exit();
	void Callback_popup_exit_msg(Ref* pSender);

	void ShowPopup1();
	void ShowPopup2();
	void ShowPopup3();
	void ShowPopup4();
	void ShowPopup5();
	void ShowPopup6();
	void Callback_popup_tutorial_msg(Ref* pSender);

		
protected:
	//Sprite* m_IMG_popup_BG;
	//Sprite* m_IMG_popup_credits;

	MenuItemImage* m_IMG_ani_BG;
	MenuItemImage* m_img_Logo;
	Menu* m_BTN_set;

	Button* m_BTN_signin;
	Button* m_BTN_help;
	Button* m_BTN_achievement;

	Button* m_BTN_ranking;
	Button* m_BTN_credits;
	Button* m_BTN_base;	
	Button* m_BTN_start;	

	// deprecated
	Button* m_BTN_sound;
	Button* m_BTN_replay;
	Button* m_BTN_charge;
	Button* m_BTN_charge_ad;
	Button* m_BTN_charge_ok;
	Label*	m_LBL_difficult;
	// deprecated

	bool m_bPopupAlreadyOpened;	// popup [3/25/2015 ChoiJunHyeok]



};