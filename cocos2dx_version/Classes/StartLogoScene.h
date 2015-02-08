#pragma once

#include "cocos2d.h"
#include "ui\CocosGUI.h"                //코코스 스튜디오 GUI 기능 추가
USING_NS_CC;
using namespace ui;

class StartLogoScene : public cocos2d::Layer
{


public:
	static cocos2d::Scene* createScene();
	virtual bool init();

	CREATE_FUNC(StartLogoScene);

protected:
	MenuItemImage* m_img_Logo;
};

