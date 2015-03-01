#pragma once

#include <vector>
#include "cocos2d.h"
//#include "cocostudio\CocoStudio.h"        //코코스 스튜디오 사용
#include "ui\CocosGUI.h"                //코코스 스튜디오 GUI 기능 추가
#include "SelectStageScene.h"
#include "ResultScene.h"
#include "ResultFailedScene.h"
//#include "ButtonN.h"
USING_NS_CC;
using namespace ui;
using namespace std;

class InGameScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(InGameScene);

	

protected:
	void Touch_NumPad(Ref* sender);
	void Touch_submit(Ref* sender, Widget::TouchEventType type);
	//Layout* _layout;
	vector<int> m_vQuestion;
	vector<int> m_vAnswer;
	//vector<bool> m_vPressed;

	ListView* lst_log;
	//Layout* default_item;	// default layout item for hint list view.
	vector<MenuItemToggle*> m_vButtons;
	Button* m_BTN_submit;

	Label* m_LBL_sum;
	Label* m_LBL_digit;
	Label* m_LBL_time;

	Label* m_TXT_sum;	// sum
	Label* m_TXT_digit;	// digit counter
	Label* m_TXT_time;	// time
	Label* m_TXT_life;	// life counter
	int m_nLife;
	int m_nAnswerDigit;	// word count
	bool m_bGameOver;

	int m_nSubmitCount;	// total submit count
	int m_nDigitCount;
	int m_sumNew;

	int m_nWid;
	int m_nHei;

	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event *event);
	void changeScene(void);
	void showResult(void);
	void showResultFailed(void);
};