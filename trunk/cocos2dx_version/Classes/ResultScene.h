#pragma once

#include "cocos2d.h"
#include "ui\CocosGUI.h"
#include "SelectStageScene.h"
#include "MainScene.h"
#include "Util/DataSingleton.h"
#include "Util/Global.h"
USING_NS_CC;

using namespace ui;


class ResultScene : public cocos2d::Layer
{
public:
	static Scene* scene();
	CREATE_FUNC(ResultScene);
	virtual bool init();

	void ShowRankInEasyNormalMode();
	void ShowCountInChallengeMode();


	EventListenerTouchOneByOne * listener;

	static Scene* createScene(void);
	void changeScene(void);

	virtual bool onTouchBegan(Touch* touch, Event* event);

	void scheduleCallback(float delta);	// schedule
	int m_nCriterionOfDrank;
	int m_nCriterionOfArank;
	int m_nCriterionOfBrank;

	//void SetResult(bool);
	//ResultScene() : bSuccess(true) {};
	//ResultScene(bool bSuccess);


protected:
	MenuItemImage* m_IMG_result;
	MenuItemImage* m_IMG_rank;
	Label* m_LBL_count;
	Label* m_LBL_time;
	Button* m_BTN_main;
	Button* m_BTN_next;
	MenuItemImage* m_IMG_line;

	bool m_bSuccess;


};