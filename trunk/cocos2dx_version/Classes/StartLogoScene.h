#pragma once

#include "cocos2d.h"
#include "ui\CocosGUI.h"                //���ڽ� ��Ʃ��� GUI ��� �߰�
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

