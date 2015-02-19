#pragma once

#include "cocos2d.h"
#include "ui\CocosGUI.h"
#include "HelloWorldScene.h"
#include "MainScene.h"
USING_NS_CC;

using namespace ui;


class StartLogoScene : public cocos2d::Layer
{
public:
	static Scene* scene();
	CREATE_FUNC(StartLogoScene);
	virtual bool init();

	EventListenerTouchOneByOne * listener;

	static Scene* createScene(void);
	void changeScene(void);

	virtual bool onTouchBegan(Touch* touch, Event* event);

	void scheduleCallback(float delta);	// schedule

protected:
	MenuItemImage* m_img_Logo;


};