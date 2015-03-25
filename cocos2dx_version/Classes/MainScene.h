#pragma once

#include "cocos2d.h"
#include "ui\CocosGUI.h"
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

	void Touch_ranking(Ref* sender, Widget::TouchEventType type);
	void Touch_credits(Ref* sender, Widget::TouchEventType type);

	void Touch_sound(Ref* sender, Widget::TouchEventType type);
	void Touch_setting(Ref* sender);
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event *event);
	void ShowPopup();
	void Callback_popup_ok(Ref* pSender);
		
protected:
	//Sprite* m_IMG_popup_BG;
	//Sprite* m_IMG_popup_credits;

	MenuItemImage* m_IMG_ani_BG;
	MenuItemImage* m_img_Logo;
	Menu* m_BTN_set;
	Button* m_BTN_sound;
	Button* m_BTN_ranking;
	Button* m_BTN_replay;
	Button* m_BTN_credits;
	Button* m_BTN_base;
	Button* m_BTN_charge;
	Button* m_BTN_start;
	Button* m_BTN_charge_ad;
	Button* m_BTN_charge_ok;
	Label*	m_LBL_difficult;

	bool m_bPopupAlreadyOpened;	// popup [3/25/2015 ChoiJunHyeok]



};