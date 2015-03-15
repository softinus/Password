#pragma once

#include "cocos2d.h"
#include "ui\CocosGUI.h"
#include "InGameScene.h"
#include "MainScene.h"
USING_NS_CC;

using namespace ui;
using namespace std;

namespace
{
	enum EStage
	{
		EASY= 0,
		NORMAL,
		CHALLENGE,
		ALL
	};
	enum ERank
	{
		D_RANK = 0,
		C_RANK,
		B_RANK,
		A_RANK,
		S_RANK
	};
}

class SelectStageScene : public cocos2d::Layer
{
public:
	static Scene* scene();
	CREATE_FUNC(SelectStageScene);
	virtual bool init();

	EventListenerTouchOneByOne * listener;

	static Scene* createScene(void);
	void changeScene(void);

	//callback events
	virtual bool onTouchBegan(Touch* touch, Event* event);
	void onButtonSelect(Ref* sender, Widget::TouchEventType type);
	void onButtonBack(Ref* sender, Widget::TouchEventType type);
	void pageViewEvent(Ref *pSender, PageView::EventType type);

protected:
	PageView* m_PAGE_stage;
	MenuItemImage* m_img_Logo;

	Button* m_PAGE_left;
	Button* m_PAGE_right;
	MenuItemImage* m_IMG_title;
	//MenuItemImage* m_IMG_status;
	vector<MenuItemImage*> m_vPage;

	Button* m_BTN_back;

};