#pragma once

#include "cocos2d.h"

#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
#include "CocosGUI.h"
#else
#include "ui\CocosGUI.h"
#endif

#include "InGameScene.h"
#include "MainScene.h"
USING_NS_CC;

using namespace ui;


class ResultFailedScene : public cocos2d::Layer
{
public:
	static Scene* scene();
	CREATE_FUNC(ResultFailedScene);
	virtual bool init();

	EventListenerTouchOneByOne * listener;

	static Scene* createScene(void);
	void changeScene(void);

	virtual bool onTouchBegan(Touch* touch, Event* event);

	void scheduleCallback(float delta);	// schedule

protected:
	MenuItemImage* m_IMG_lifewarn;
	Button* m_BTN_ad;
	Button* m_BTN_main;
	
private:
	void ShowAD(Ref* sender, Widget::TouchEventType type);
	void GoToMain(Ref* sender, Widget::TouchEventType type);

};