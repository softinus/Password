#pragma once

#include "cocos2d.h"
#include "ui\CocosGUI.h"
#include "HelloWorldScene.h"
USING_NS_CC;

using namespace ui;


class StartLogoScene : public cocos2d::Layer
{
public:
	static Scene* scene();
	CREATE_FUNC(StartLogoScene);
	virtual bool init();

	EventListenerTouchOneByOne * listener;

	void creatGameScene(void);
	void changeScene(void);

	virtual bool onTouchBegan(Touch* touch, Event* event);

protected:
	MenuItemImage* m_img_Logo;


};