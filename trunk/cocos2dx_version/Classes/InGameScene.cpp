#include "InGameScene.h"
//#include "cocostudio\CocoStudio.h"
//#include "ui\UILayout.h"
//#include "ui/CocosGUI.h"

#include "Util/Global.h"
#include "Util/DataSingleton.h"
#include "GPGS/GameSharing.h"
#include "SimpleAudioEngine.h"
#include "network/HttpRequest.h"
#include "CustomUI/PopupWindow.h"
using namespace CocosDenshion;
USING_NS_CC;
//using namespace std;
//using namespace ui;
//using namespace cocostudio;




Scene* InGameScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = InGameScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

void InGameScene::InitStage()
{
	m_nCurrStageRepeatCount = 0;
	m_nSubmitCount = 0;
	m_nAnswerDigit = 2;
	m_nDigitCount = 0;
	m_nSpendTime = 0;

	int nLevel = DataSingleton::getInstance().nLevel;
	int nMode = DataSingleton::getInstance().nPlayMode;
	int nButtonSize = 0;
	int nStartX = 0;
	int nStartY = 0;
	int nMargin = 1;
	int nFontSize = 0;

	//MessageBox(to_string2(nMode).c_str(), "mode-in");
	//MessageBox(to_string2(nLevel).c_str(), "level-in");

	if (nLevel == 1)
	{
		m_nWid = 2;
		m_nHei = 2;
		m_nLife = 5;
		m_nAnswerDigit = 2;

		if (nMode == EStage::EASY)
			m_nRepeatStage_MAX = 1;
		else if (nMode == EStage::NORMAL)
			m_nRepeatStage_MAX = 2;

		m_nRecoverLifeAmount = 1;
		m_nTimeLimit = 600;

		nButtonSize = 338;
		nStartX = 190;
		nStartY = 757;
		nFontSize = 135;
	}
	else if (nLevel == 2)
	{
		m_nWid = 3;
		m_nHei = 2;
		m_nLife = 7;
		m_nAnswerDigit = 3;

		if (nMode == EStage::EASY)
			m_nRepeatStage_MAX = 1;
		else if (nMode == EStage::NORMAL)
			m_nRepeatStage_MAX = 3;

		m_nRecoverLifeAmount = 1;
		m_nTimeLimit = 660;

		nButtonSize = 224;
		nStartX = 133;
		nStartY = 700;
		nFontSize = 100;
	}
	else if (nLevel == 3)
	{
		m_nWid = 3;
		m_nHei = 3;
		m_nLife = 8;
		m_nAnswerDigit = 4;

		if (nMode == EStage::EASY)
			m_nRepeatStage_MAX = 1;
		else if (nMode == EStage::NORMAL)
			m_nRepeatStage_MAX = 3;

		m_nRecoverLifeAmount = 1;
		m_nTimeLimit = 600;

		nButtonSize = 224;
		nStartX = 133;
		nStartY = 814;
		nFontSize = 100;
	}
	else if (nLevel == 4)
	{
		m_nWid = 4;
		m_nHei = 3;
		m_nLife = 9;
		m_nAnswerDigit = 4;

		if (nMode == EStage::EASY)
			m_nRepeatStage_MAX = 1;
		else if (nMode == EStage::NORMAL)
			m_nRepeatStage_MAX = 3;

		m_nRecoverLifeAmount = 2;
		m_nTimeLimit = 780;

		nButtonSize = 168;
		nStartX = 105;
		nStartY = 757;
		nFontSize = 85;
	}
	else if (nLevel == 5)
	{
		m_nWid = 4;
		m_nHei = 4;
		m_nLife = 10;
		m_nAnswerDigit = 4;

		if (nMode == EStage::EASY)
			m_nRepeatStage_MAX = 1;
		else if (nMode == EStage::NORMAL)
			m_nRepeatStage_MAX = 3;

		m_nRecoverLifeAmount = 2;
		m_nTimeLimit = 840;

		nButtonSize = 168;
		nStartX = 105;
		nStartY = 842;
		nFontSize = 85;
	}
	else if (nLevel == 6)
	{
		m_nWid = 5;
		m_nHei = 4;
		m_nLife = 11;
		m_nAnswerDigit = 4;

		if (nMode == EStage::EASY)
			m_nRepeatStage_MAX = 1;
		else if (nMode == EStage::NORMAL)
			m_nRepeatStage_MAX = 3;

		m_nRecoverLifeAmount = 2;
		m_nTimeLimit = 900;

		nButtonSize = 135;
		nStartX = 88;
		nStartY = 804;
		nFontSize = 70;
	}
	else if (nLevel == 7)
	{
		m_nWid = 5;
		m_nHei = 5;
		m_nLife = 12;
		m_nAnswerDigit = 5;

		if (nMode == EStage::EASY)
			m_nRepeatStage_MAX = 1;
		else if (nMode == EStage::NORMAL)
			m_nRepeatStage_MAX = 3;

		m_nRecoverLifeAmount = 3;
		m_nTimeLimit = 1020;

		nButtonSize = 135;
		nStartX = 88;
		nStartY = 858;
		nFontSize = 70;
	}
	else if (nLevel == 8)
	{
		m_nWid = 6;
		m_nHei = 5;
		m_nLife = 13;
		m_nAnswerDigit = 5;

		if (nMode == EStage::EASY)
			m_nRepeatStage_MAX = 1;
		else if (nMode == EStage::NORMAL)
			m_nRepeatStage_MAX = 3;

		m_nRecoverLifeAmount = 3;
		m_nTimeLimit = 1140;

		nButtonSize = 112;
		nStartX = 77;
		nStartY = 870;
		nFontSize = 58;
	}
	else if (nLevel == 9)
	{
		m_nWid = 6;
		m_nHei = 6;
		m_nLife = 14;
		m_nAnswerDigit = 5;

		if (nMode == EStage::EASY)
			m_nRepeatStage_MAX = 1;
		else if (nMode == EStage::NORMAL)
			m_nRepeatStage_MAX = 3;

		m_nRecoverLifeAmount = 3;
		m_nTimeLimit = 1200;


		nButtonSize = 112;
		nStartX = 77;
		nStartY = 870;
		nFontSize = 58;
	}

	// all of challenge mode's time limit is 60 sec
	if (EStage::CHALLENGE == nLevel)
	{
		m_nTimeLimit = 60;
	}

	// pad setting
	for (int i = 0; i < m_nWid; ++i)
	{
		for (int j = 0; j < m_nHei; ++j)
		{
			auto img1 = MenuItemImage::create("scene4/button/btn_pad_up.png", "scene4/button/btn_pad_press.png");
			auto img2 = MenuItemImage::create("scene4/button/btn_pad_down.png", "scene4/button/btn_pad_press.png");

			MenuItemToggle* button = MenuItemToggle::createWithCallback(
				CC_CALLBACK_1(InGameScene::Touch_NumPad, this), img1, img2, NULL);

			float fResizeFactor = (float)nButtonSize / (float)(button->getContentSize().height);
			button->setScale(fResizeFactor);
			button->setTag(j*m_nWid + (i + 1));

			auto menu = Menu::create(button, NULL);
			menu->setPosition(Vec2(nStartX + (nButtonSize + nMargin) * i, nStartY - (nButtonSize + nMargin) * j));

			auto LBL_number = Label::createWithTTF("0", "fonts/LCDM2N_.TTF", nFontSize);
			LBL_number->setPosition(Vec2(nStartX + (nButtonSize + nMargin) * i, nStartY - (nButtonSize + nMargin) * j));
			LBL_number->setString(to_string2(j*m_nWid + (i + 1)));
			LBL_number->setTextColor(Color4B(17, 140, 24, 200));

			button->setUserObject(LBL_number);

			this->addChild(menu);
			this->addChild(LBL_number);

			m_vButtons.push_back(button);
		}
	}
}

// on "init" you need to initialize your instance
bool InGameScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	auto keylistener = EventListenerKeyboard::create();
	keylistener->onKeyReleased = CC_CALLBACK_2(InGameScene::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keylistener, this);

	InitStage();
	

	MakeAnswer();


	// ¹öÆ° ÇÏ³ª ´©¸£¸é Å¸ÀÌ¸Ó ½ÃÀÛÇÔ.
	this->schedule(schedule_selector(InGameScene::scheduleCallback), 0.85f);

	// gen answer
	m_TXT_sum = Label::create(to_string2(m_sumNew), "fonts/LCDM2N_.TTF", 54.f);
	m_TXT_sum->setPosition(Vec2(200, 1000));
	m_TXT_sum->setAnchorPoint(Vec2(0, 0));
	m_TXT_sum->setContentSize(Size(200, 100));
	m_TXT_sum->setVerticalAlignment(TextVAlignment::CENTER);
	m_TXT_sum->setAlignment(TextHAlignment::CENTER);
	this->addChild(m_TXT_sum);

	m_LBL_sum = Label::create("sum", "fonts/LCDM2N_.TTF", 24.f);
	m_LBL_sum->setPosition(Vec2(210, 965));
	m_LBL_sum->setAnchorPoint(Vec2(0, 0));
	m_LBL_sum->setTextColor(Color4B(79, 147, 210, 255));
	this->addChild(m_LBL_sum);

	// digit counter
	m_LBL_digit = Label::create("word", "fonts/LCDM2N_.TTF", 24.f);
	m_LBL_digit->setPosition(Vec2(62, 965));
	m_LBL_digit->setAnchorPoint(Vec2(0, 0));
	m_LBL_digit->setTextColor(Color4B(79, 147, 210, 255));
	this->addChild(m_LBL_digit);

	m_TXT_digit = Label::create("0/" + to_string2(m_nAnswerDigit), "fonts/LCDM2N_.TTF", 54.f);
	m_TXT_digit->setPosition(Vec2(50, 1000));
	m_TXT_digit->setAnchorPoint(Vec2(0, 0));
	this->addChild(m_TXT_digit);

	// time
	m_LBL_time = Label::create("time", "fonts/LCDM2N_.TTF", 24.f);
	m_LBL_time->setPosition(Vec2(465, 965));
	m_LBL_time->setAnchorPoint(Vec2(1, 0));
	m_LBL_time->setTextColor(Color4B(79, 147, 210, 255));
	this->addChild(m_LBL_time);

	m_TXT_time = Label::create("0:00", "fonts/LCDM2N_.TTF", 54.f);
	m_TXT_time->setPosition(Vec2(465, 1000));
	m_TXT_time->setAnchorPoint(Vec2(1, 0));
	this->addChild(m_TXT_time);

	// life
	m_TXT_life = Label::create(to_string2(m_nLife), "fonts/LCDM2L_.TTF", 106.f);
	m_TXT_life->setPosition(Vec2(575, 1000));
	m_TXT_life->setAnchorPoint(Vec2(0, 0));
	m_TXT_life->setAlignment(TextHAlignment::RIGHT);
	this->addChild(m_TXT_life);

	//Size visibleSize = Director::getInstance()->getVisibleSize();
	//Vec2 origin = Director::getInstance()->getVisibleOrigin();
	//Size s = this->getContentSize();

	MenuItemImage* img_lifebox = MenuItemImage::create("scene4/box_life.png", "scene4/box_life.png");
	img_lifebox->setPosition(Vec2(604, 1082));
	this->addChild(img_lifebox);


	m_BTN_submit = Button::create("scene4/btn_enter_up.png", "scene4/btn_enter_down.png");
	m_BTN_submit->setPosition(Vec2(359, 180));
	m_BTN_submit->setScale9Enabled(true);
	m_BTN_submit->setSize(Size(676, 86));
	m_BTN_submit->setPressedActionEnabled(false);
	m_BTN_submit->addTouchEventListener(CC_CALLBACK_2(InGameScene::Touch_submit, this));
	m_BTN_submit->setBright(false);
	m_BTN_submit->setEnabled(false);
	this->addChild(m_BTN_submit);

	lst_log = ListView::create();
	lst_log->setDirection(ui::ListView::Direction::VERTICAL);
	lst_log->setBounceEnabled(true);
	lst_log->setBackGroundImage("scene4/box_log.png");
	//lst_log->setBackGroundImageScale9Enabled(true);
	lst_log->setContentSize(Size(446, 130));
	lst_log->setPosition(Vec2(259, 1144));
	lst_log->setAnchorPoint(Vec2(0.5f, 0.5f));

	Text* txt = Text::create("Be sure to match the password!", "fonts/LCDM2N_.TTF", 24.f);

	Layout* default_item = Layout::create();
	default_item->setTouchEnabled(true);
	default_item->setContentSize(txt->getContentSize());
	txt->setPosition(Vec2(default_item->getContentSize().width / 2.0f,
		default_item->getContentSize().height / 2.0f));
	default_item->addChild(txt);

	lst_log->pushBackCustomItem(default_item);
	//lst_log->setItemModel(default_item);
	//lst_log->pushBackDefaultItem();
	this->addChild(lst_log);


	m_LDB_progress = LoadingBar::create("common/slider_bar_active_9patch.png");
	m_LDB_progress->setPosition(Vec2(this->getContentSize().width / 2, this->getContentSize().height-5));
	m_LDB_progress->setDirection(LoadingBar::Direction::LEFT);
	m_LDB_progress->setScale9Enabled(true);
	m_LDB_progress->setCapInsets(Rect(0, 0, 0, 0));
	m_LDB_progress->setContentSize(Size(750, 12));
	m_LDB_progress->setPercent(0.f);
	this->addChild(m_LDB_progress);


	//³ëÆ¼ÇÇÄÉÀÌ¼Ç ÃßÄ«
	NotificationCenter::sharedNotificationCenter()->addObserver(this,
		callfuncO_selector(InGameScene::doNotification), "notification", NULL);
	//"notification"ÀÌ¶ó´Â ¸Þ½ÃÁö°¡ ¿À¸é ÇØ´ç ÇÔ¼ö¸¦ ½ÇÇàÇÑ´Ù.

	if (UserDefault::getInstance()->getIntegerForKey("guide_already_showed") == NULL)	// if guide has not showed
	{
		ShowPopup1();
	}


	return true;
}

//³ëÆ¼ÇÇÄÉÀÌ¼Ç ÇÔ¼ö
void InGameScene::doNotification(Object *obj)
{
	////³ëÆ¼ÇÇÄÉÀÌ¼Ç ¹Þ±â
	//int nParam = (int)obj;
	//MessageBox(to_string2(nParam).c_str(), "param");

	//if (nParam == 1)
	//{
	//	CCDirector::sharedDirector()->resume();   //È­¸é Àç½ÃÀÛ
	//	//CCDirector::sharedDirector()->gettouc ->getTouchDispatcher()->addTargetedDelegate(pMenu, kCCMenuHandlerPriority, true);
	//	//¸Þ´º ¹öÆ° È°¼º
	//}
	//else{
	//	CCArray* childs = this->getChildren();
	//	CCLog("noti 00");
	//	CCDirector::sharedDirector()->pause();   //È­¸é Á¤Áö

	//	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(pMenu);
	//	//¸Þ´º¹öÆ° ºñÈ°¼º
	//}
}

void InGameScene::scheduleCallback(float delta)
{
	//CCLOG("scheduleCallback : %f", delta);

	--m_nTimeLimit;
	++m_nSpendTime;

	int nMinute = m_nTimeLimit / 60;
	int nSec = m_nTimeLimit % 60;

	char szTime[32] = { NULL, };
	sprintf(szTime, "%d:%02d", nMinute, nSec);
	m_TXT_time->setString(szTime);
	//DataSingleton::getInstance().strSpentTime = time;	// ÃÑ ¼Ò¸ðÇÑ ½Ã°£ ÀúÀå.
	DataSingleton::getInstance().nSpentTime = m_nSpendTime;	// ÃÑ ¼Ò¸ðÇÑ ½Ã°£ ÀúÀå.

	if (m_nTimeLimit == 0)	// ½Ã°£ ³»¿¡ ÀüºÎ ¸ø Ç®¸é ½ÇÆÐ.
	{
		DataSingleton::getInstance().bClear = false;
		DataSingleton::getInstance().nStageRepeatCount = m_nCurrStageRepeatCount;
		DataSingleton::getInstance().nLeftLife = m_nLife;

		showResultFailed();
	}

	
	
}


void InGameScene::Touch_submit(Ref* sender, Widget::TouchEventType type)
{
	Button* btn = (Button*)sender;



	//ÅÍÄ¡ ÀÌº¥Æ® ½ÇÇà½Ã ÇÁ·Î±×·¥ Á¾·á
	switch (type)
	{
	case Widget::TouchEventType::BEGAN:
		break;
	case Widget::TouchEventType::MOVED:
		break;
	case Widget::TouchEventType::ENDED:

		if (btn->isBright() == true)
		{
			auto audio = SimpleAudioEngine::getInstance();
			audio->playEffect("raw/enter.wav", false, 1.0f, 1.0f, 1.0f);
		}


		for (int i = 0; i < m_vButtons.size(); ++i)
		{
			if (m_vButtons[i]->getSelectedIndex() == 1)
			{
				m_vAnswer.push_back(m_vButtons[i]->getTag());	// ´­·ÁÁ® ÀÖÀ¸¸é Á¤´ä¿¡ ³Ö°í
				//strAnswer.append(to_string2(m_vAnswer[m_vAnswer.size() - 1]));
			}
		}

		if (m_vAnswer.empty())	// ¾Æ¹«°Íµµ ´­¸®Áö ¾ÊÀ¸¸é µ¿ÀÛ ¾È ÇÔ.
			return;

		++m_nSubmitCount;
		DataSingleton::getInstance().nSpentCount = m_nSubmitCount;

		// Ã¤Á¡ÇÏ±â
		int nCount = 0;
		string strPrint = "";

		for (int j = 0; j < m_vAnswer.size(); ++j)
		{
			strPrint += to_string2(m_vAnswer[j]);
			if (j != m_vAnswer.size() - 1)
				strPrint += ", ";

			for (int i = 0; i < m_vQuestion.size(); ++i)
			{
				if (m_vQuestion[i] == m_vAnswer[j])
				{
					++nCount;
					break;
				}
			}
		}


		// ´Ù ¸Â­Ÿ°í ÀÚ¸´¼öµµ ¸ÂÀ¸¸é Á¤´äÀÓ
		if (nCount == m_nAnswerDigit && (m_vQuestion.size() == m_vAnswer.size()))
		{
			if (m_nCurrStageRepeatCount == m_nRepeatStage_MAX-1)
			{
				ClearStage();
			}
			else
			{
				RepeatStage();
			}

			return;
		}

		m_BTN_submit->setBright(false);

		m_nDigitCount = 0;
		m_sumNew = m_nSumFixed;
		for (size_t i = 0; i < m_vButtons.size(); ++i)
		{
			m_vButtons[i]->setSelectedIndex(0);
			Label* lbl = static_cast<Label*>(m_vButtons[i]->getUserObject());
			lbl->enableOutline(Color4B::BLACK, 0);
		}

		// UI refresh
		m_TXT_digit->setString(to_string2(m_nDigitCount) + "/" + to_string2(m_nAnswerDigit));
		m_TXT_sum->setString(to_string2(m_sumNew));
		m_TXT_sum->setTextColor(Color4B(255, 255, 255, 255));
		m_BTN_submit->setBright(false);
		m_vAnswer.clear();

		// list hint element setting
		Text* txt = Text::create(strPrint, "fonts/LCDM2N_.TTF", 28.f);
		txt->setColor(Color3B(183, 183, 183));
		Text* txt2 = Text::create(to_string2(nCount), "fonts/LCDM2N_.TTF", 28.f);
		txt2->setColor(Color3B(227, 29, 29));

		Layout* default_item = Layout::create();
		default_item->setTouchEnabled(true);
		default_item->setContentSize(Size(txt->getContentSize().width + txt2->getContentSize().height
			, txt->getContentSize().height));
		txt->setPosition(Vec2(default_item->getContentSize().width / 2.0f,
			default_item->getContentSize().height / 2.0f));
		txt2->setPosition(Vec2(415,
			default_item->getContentSize().height / 2.0f));
		default_item->addChild(txt);
		default_item->addChild(txt2);

		lst_log->pushBackCustomItem(default_item);
		lst_log->refreshView();
		lst_log->scrollToBottom(.5f, false);

		// life
		this->ChangeLife(false, 1);
		
		
		//stage  over
		if (m_nLife == 0)
		{
			DataSingleton::getInstance().bClear = false;
			DataSingleton::getInstance().nStageRepeatCount = m_nCurrStageRepeatCount;
			DataSingleton::getInstance().nLeftLife = m_nLife;

			showResultFailed();
		}
		break;
	}
}



void InGameScene::Touch_NumPad(Ref* sender)
{
	MenuItemToggle* tgl = dynamic_cast<MenuItemToggle*>(sender);
	Label* lbl = static_cast<Label*>(tgl->getUserObject());

	auto audio = SimpleAudioEngine::getInstance();
	audio->playEffect("raw/number.wav", false, 1.0f, 1.0f, 1.0f);

	// change button select status whether it pressed or not.
	
	if (tgl->getSelectedIndex() == 0)	
	{
		if (lbl)
			lbl->enableOutline(Color4B::BLACK, 0);

		++m_nDigitCount;
		m_sumNew = m_sumNew + tgl->getTag();

	}
	else// if this button already selected
	{
		if (abs(m_nDigitCount) == m_nAnswerDigit)
		{
			tgl->setSelectedIndex(0);
			return;
		}

		if (lbl)
			lbl->enableOutline(Color4B::WHITE, 1);

		--m_nDigitCount;
		
		m_sumNew = m_sumNew - tgl->getTag();

	}

	if (m_sumNew < 0)	// minus
	{
		m_TXT_sum->setString("E");
		m_TXT_sum->setTextColor(Color4B::RED);
	}
	else
	{
		m_TXT_sum->setString(to_string2(m_sumNew));
		m_TXT_sum->setTextColor(Color4B::WHITE);
	}

	if (abs(m_nDigitCount)== abs(m_nAnswerDigit))	// ÀÔ·ÂÇØ¾ßÇÒ ÀÚ¸®¼ö¶û ÀÔ·ÂÇÑ ÀÚ¸®¼ö °°À¸¸é..
	{
		m_BTN_submit->setBright(true);
		m_BTN_submit->setEnabled(true);
	}
	else
	{
		m_BTN_submit->setBright(false);
		m_BTN_submit->setEnabled(false);
	}
		
	m_TXT_digit->setString(to_string2(abs(m_nDigitCount)) + "/" + to_string2(m_nAnswerDigit));

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	//MessageBox(str.c_str(), "ÀÀ?");
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	//exit(0);		
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

#endif

}


void InGameScene::onKeyReleased(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event *event)
{
	if (keycode == EventKeyboard::KeyCode::KEY_BACK)
	{
		this->changeScene();
	}
	else if (keycode == EventKeyboard::KeyCode::KEY_ESCAPE)
	{
		this->changeScene();
	}

}



void InGameScene::showResultFailed(void)
{
	//Director::getInstance()->getEventDispatcher()->removeEventListenersForType(EventListener::Type::TOUCH_ONE_BY_ONE);


	auto hScene = ResultScene::createScene();
	auto pScene = TransitionFade::create(1.0f, hScene);
	Director::getInstance()->pushScene(pScene);
}

void InGameScene::showResult(void)
{
	//Director::getInstance()->getEventDispatcher()->removeEventListenersForType(EventListener::Type::TOUCH_ONE_BY_ONE);

	auto hScene = ResultScene::createScene();
	auto pScene = TransitionFade::create(1.0f, hScene);
	Director::getInstance()->pushScene(pScene);
	//auto hScene = ResultScene::createScene();
	//this->addChild(hScene);
}

void InGameScene::changeScene(void)
{
	//Director::getInstance()->getEventDispatcher()->removeEventListenersForType(EventListener::Type::TOUCH_ONE_BY_ONE);

	auto hScene = SelectStageScene::createScene2();
	auto pScene = TransitionFade::create(1.0f, hScene);
	Director::getInstance()->replaceScene(pScene);
}


void InGameScene::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void InGameScene::ClearStage()
{
	// play 
	if(DataSingleton::getInstance().nPlayMode == EStage::EASY)
	{
		int nSavedStage = UserDefault::getInstance()->getIntegerForKey("stage_clear_easy", 0);	// get current highest stage level.
		if (nSavedStage < DataSingleton::getInstance().nLevel)	// if this level is highest level...
		{
			UserDefault::getInstance()->setIntegerForKey("stage_clear_easy", DataSingleton::getInstance().nLevel);	// update save data.
			UserDefault::getInstance()->setIntegerForKey("stage_clear_normal", DataSingleton::getInstance().nLevel-1);	// update save data.

			//submit score to Google play store game service...
			GameSharing::SubmitScore(DataSingleton::getInstance().nLevel * DataSingleton::getInstance().nPlayMode, 0);
			//GameSharing::UnlockAchivement(DataSingleton::getInstance().nLevel - 1);
		}
	}
	else if (DataSingleton::getInstance().nPlayMode == EStage::NORMAL)
	{
		int nSavedStage = UserDefault::getInstance()->getIntegerForKey("stage_clear_normal", 0);	// get current highest stage level.
		if (nSavedStage < DataSingleton::getInstance().nLevel)	// if this level is highest level...
		{
			UserDefault::getInstance()->setIntegerForKey("stage_clear_normal", DataSingleton::getInstance().nLevel);	// update save data.

			//submit score to Google play store game service...
			GameSharing::SubmitScore(DataSingleton::getInstance().nLevel * DataSingleton::getInstance().nPlayMode, 0);
			GameSharing::UnlockAchivement(DataSingleton::getInstance().nLevel - 1);
		}
	}
	else if (DataSingleton::getInstance().nPlayMode == EStage::CHALLENGE)
	{ }
	

	DataSingleton::getInstance().bClear = true;
	//DataSingleton::getInstance().nStageRepeatCount = m_nRepeatStage_MAX;
	DataSingleton::getInstance().nLeftLife = m_nLife;
	
	showResult();
}




void InGameScene::MakeAnswer()
{
	// ANSWER_DIGITÀÚ¸® ³­¼ö·Î Á¤´äÀ» »ý¼ºÇÑ´Ù.
	m_vAnswer.clear();
	m_vQuestion.clear();
	int nSum = 0;
	//srand((unsigned int)time(NULL));
	while (m_vQuestion.size() != m_nAnswerDigit)
	{
		int nNumber = random(1, m_nWid*m_nHei);
		bool bAlreadyHas = false;
		bool bCountious = false;	// ¹Ýº¹µÈ ¼ýÀÚ Á¦¿Ü.
		for (int i = 0; i < m_vQuestion.size(); ++i)
		{
			if (m_vQuestion[i] == nNumber)
			{
				bAlreadyHas = true;
				break;
			}
			if (m_vQuestion[i]-1 ==  nNumber)
			{
				bCountious = true;
				break;
			}
			if (m_vQuestion[i]+1 == nNumber)
			{
				bCountious = true;
				break;
			}
		}
		if (bAlreadyHas == false && bCountious==false)
		{
			m_vQuestion.push_back(nNumber);
			nSum += nNumber;
		}
	}
	m_sumNew = nSum;
	m_nSumFixed = nSum;
}

void InGameScene::RepeatStage()
{
	// TODO : ÀÌÂÊ¿¡ ÇöÀç ´­¸° ¹öÆ° ÃÊ±âÈ­, Á¤´ä ÃÊ±âÈ­, ¸ÅÄª¼®¼¼½º ¶ç¿ì±â, ¶óÀÌÇÁ È¸º¹
	//FinishStage();
	{
		Sprite* SPR_match = Sprite::create("scene4/s4_pup_success.png");
		SPR_match->setPosition(this->getContentSize().width / 2, this->getContentSize().height / 2);
		this->addChild(SPR_match);

		auto *fadein = FadeOut::create(1.5f);    // ½Ã°£
		auto *delay = DelayTime::create(1.5f);    // ½Ã°£
		auto *fadeout = FadeOut::create(2.5f);    // ½Ã°£

		Sequence *action_2 = Sequence::create(fadein, delay, fadeout, NULL);
		SPR_match->runAction(action_2);
	}

	ChangeLife(true, m_nRecoverLifeAmount);




	//this->setTouchEnabled(false);

	MakeAnswer();
	m_nDigitCount = 0;
	for (size_t i = 0; i < m_vButtons.size(); ++i)
	{
		m_vButtons[i]->setSelectedIndex(0);
		Label* lbl = static_cast<Label*>(m_vButtons[i]->getUserObject());
		lbl->enableOutline(Color4B::BLACK, 0);
	}

	// UI refresh
	m_TXT_digit->setString(to_string2(m_nDigitCount) + "/" + to_string2(m_nAnswerDigit));
	m_TXT_sum->setString(to_string2(m_sumNew));
	m_BTN_submit->setBright(false);

	float f = (((float)m_nCurrStageRepeatCount + 1) / (float)m_nRepeatStage_MAX) * 100.f;
	m_LDB_progress->setPercent(f);

	string str = "";
	Text* txt = NULL;
	if (EStage::CHALLENGE == DataSingleton::getInstance().nPlayMode)	// if challenge mode
	{
		// append listbox
		str = " ===== SUCCESS! (" + to_string2(m_nCurrStageRepeatCount + 1) + ") ===== ";
		txt = Text::create(str, "fonts/LCDM2N_.TTF", 30.f);
	}
	else
	{
		// append listbox
		str = " ===== SUCCESS! (" + to_string2(m_nCurrStageRepeatCount + 1) + "/" + to_string2(m_nRepeatStage_MAX) + ") ===== ";
		txt = Text::create(str, "fonts/LCDM2N_.TTF", 30.f);
	}
	

	Layout* default_item = Layout::create();
	default_item->setTouchEnabled(true);
	default_item->setContentSize(txt->getContentSize());
	txt->setPosition(Vec2(default_item->getContentSize().width / 2.0f,
		default_item->getContentSize().height / 2.0f));
	default_item->addChild(txt);

	lst_log->pushBackCustomItem(default_item);
	lst_log->refreshView();
	lst_log->scrollToBottom(0.5f, true);

	++m_nCurrStageRepeatCount;	//  repeat stage
}

void InGameScene::ChangeLife(bool bIncrease, int nAmount)
{
	Vec2 vec(m_TXT_life->getPosition().x, m_TXT_life->getPosition().y);
	Label* LBL_lifechange = Label::create("", "fonts/LCDM2N_.TTF", 70.f);
	LBL_lifechange->setPosition(Vec2(vec.x + 100, vec.y+50));

	string str = "";
	if (bIncrease)	// when increase
	{
		str += "+";
		str += to_string2(nAmount);
		LBL_lifechange->setTextColor(Color4B(0, 255, 0, 255));
	}
	else
	{
		str += "-";
		str += to_string2(nAmount);
		LBL_lifechange->setTextColor(Color4B(255, 0, 0, 255));
	}
	LBL_lifechange->setString(str);
	this->addChild(LBL_lifechange);

	auto fadeout = FadeOut::create(1.5f);
	auto move1 = MoveBy::create(1.5f, Vec2(0,200));
	auto spawn1 = Spawn::create(fadeout, move1, NULL);
	LBL_lifechange->runAction(spawn1);
	
	//if (m_nLife / 10 != 0)	// if life is one digit
	//{
	//	m_TXT_life->size
	//}
	//else
	//{
	//	m_TXT_life->setSystemFontSize(100.f);
	//}
	if (bIncrease)
	{
		m_nLife += nAmount;
		auto blink = Blink::create(1.0f, 1);
	}
	else
	{
		m_nLife -= nAmount;
		auto blink = Blink::create(1.5f, 2);
		m_TXT_life->runAction(blink);
	}
		

	m_TXT_life->setString(to_string2(m_nLife));


}




void InGameScene::Callback_popup_ok(Ref* pSender)
{
	UIPopupWindow *pPopup = (UIPopupWindow *)pSender;
	int nTag = pPopup->getResult();

	if (nTag == 0)	// skip
	{
		UserDefault::getInstance()->setIntegerForKey("guide_already_showed", true);	// 
		pPopup->closePopup();
	}
	if (nTag == 1)	// p1-next
	{
		pPopup->closePopup();
		ShowPopup2();
	}
	if (nTag == 2)	// p1-prev
	{
	}

	if (nTag == 3)	// p2-next
	{
		pPopup->closePopup();
		ShowPopup3();
	}
	if (nTag == 4)	// p2-prev
	{
		pPopup->closePopup();
		ShowPopup1();
	}

	if (nTag == 5)	// p3-next
	{
		pPopup->closePopup();
		ShowPopup4();
	}
	if (nTag == 6)	// p3-prev
	{
		pPopup->closePopup();
		ShowPopup2();
	}

	if (nTag == 7)	// p4-next
	{
		pPopup->closePopup();
		ShowPopup5();
	}
	if (nTag == 8)	// p4-prev
	{
		pPopup->closePopup();
		ShowPopup3();
	}

	if (nTag == 9)	// p5-next
	{
		UserDefault::getInstance()->setIntegerForKey("guide_already_showed", true);	// 
		pPopup->closePopup();
		//ShowPopup6();
	}
	if (nTag == 10)	// p5-prev
	{
		pPopup->closePopup();
		ShowPopup4();
	}

}



void InGameScene::ShowPopup1()
{
	Size s = this->getContentSize();

	Size sRectSize = Size(680, 680);
	Vec2 vStartPoint = Vec2(20, 250);

	UIPopupWindow* pPopupOK = UIPopupWindow::create(NULL);
	pPopupOK->setBackgroundBorard(Sprite::create("help/help_1.png"));
	//pPopupOK->addText("Just push buttons!\nAnd hit the Enter button!", "fonts/LCDM2N_.TTF", Vec2(vStartPoint.x + s.width/2, vStartPoint.y+60), 45.0f, Color3B(240, 0, 0));
	pPopupOK->setCallBackFunc(CC_CALLBACK_1(InGameScene::Callback_popup_ok, this));
	pPopupOK->addButton("help/text_box1.png", "help/text_box1.png", "", TextureResType::LOCAL, Point(310, 1031), "", -1);
	//pPopupOK->addButton("help/h1_btn_prev_up.png", "help/h1_btn_prev_up.png", "", TextureResType::LOCAL, Point(119.5, 217.5), "", 2);
	pPopupOK->addButton("help/h1_btn_next_up.png", "help/h1_btn_next_up.png", "", TextureResType::LOCAL, Point(616.5, 217.5), "", 1);
	pPopupOK->addButton("help/h1_btn_skip_up.png", "help/h1_btn_skip_up.png", "", TextureResType::LOCAL, Point(633, 1231), "", 0);
	pPopupOK->showPopup(this);
}

void InGameScene::ShowPopup2()
{
	Size s = this->getContentSize();

	Size sRectSize = Size(500, 200);
	Vec2 vStartPoint = Vec2(30, 1050);

	UIPopupWindow* pPopupOK = UIPopupWindow::create(NULL);
	pPopupOK->setBackgroundBorard(Sprite::create("help/help_2.png"));
	//pPopupOK->addText("NOW, YOU Could CHECK\nthe number of correct answers.", "fonts/LCDM2N_.TTF", Vec2(vStartPoint.x + s.width / 2, vStartPoint.y + 60), 45.0f, Color3B(240, 0, 0));
	pPopupOK->setCallBackFunc(CC_CALLBACK_1(InGameScene::Callback_popup_ok, this));
	pPopupOK->addButton("help/text_box2.png", "help/text_box2.png", "", TextureResType::LOCAL, Point(351.5, 903.5), "", -1);
	pPopupOK->addButton("help/h1_btn_prev_up.png", "help/h1_btn_prev_up.png", "", TextureResType::LOCAL, Point(119.5, 217.5), "", 4);
	pPopupOK->addButton("help/h1_btn_next_up.png", "help/h1_btn_next_up.png", "", TextureResType::LOCAL, Point(616.5, 217.5), "", 3);
	pPopupOK->addButton("help/h1_btn_skip_up.png", "help/h1_btn_skip_up.png", "", TextureResType::LOCAL, Point(633, 1231), "", 0);
	pPopupOK->showPopup(this);
}






void InGameScene::ShowPopup3()
{
	Size s = this->getContentSize();

	Size sRectSize = Size(500, 200);
	Vec2 vStartPoint = Vec2(30, 1050);

	UIPopupWindow* pPopupOK = UIPopupWindow::create(NULL);
	pPopupOK->setBackgroundBorard(Sprite::create("help/help_3.png"));
	//pPopupOK->addText("NOW, YOU Could CHECK\nthe number of correct answers.", "fonts/LCDM2N_.TTF", Vec2(vStartPoint.x + s.width / 2, vStartPoint.y + 60), 45.0f, Color3B(240, 0, 0));
	pPopupOK->setCallBackFunc(CC_CALLBACK_1(InGameScene::Callback_popup_ok, this));
	pPopupOK->addButton("help/text_box4.png", "help/text_box4.png", "", TextureResType::LOCAL, Point(428, 923), "", -1);
	pPopupOK->addButton("help/h1_btn_prev_up.png", "help/h1_btn_prev_up.png", "", TextureResType::LOCAL, Point(119.5, 217.5), "", 6);
	pPopupOK->addButton("help/h1_btn_next_up.png", "help/h1_btn_next_up.png", "", TextureResType::LOCAL, Point(616.5, 217.5), "", 5);
	pPopupOK->addButton("help/h1_btn_skip_up.png", "help/h1_btn_skip_up.png", "", TextureResType::LOCAL, Point(633, 1231), "", 0);
	pPopupOK->showPopup(this);
}


void InGameScene::ShowPopup4()
{
	Size s = this->getContentSize();

	Size sRectSize = Size(500, 200);
	Vec2 vStartPoint = Vec2(30, 1050);

	UIPopupWindow* pPopupOK = UIPopupWindow::create(NULL);
	pPopupOK->setBackgroundBorard(Sprite::create("help/help_4.png"));
	//pPopupOK->addText("NOW, YOU Could CHECK\nthe number of correct answers.", "fonts/LCDM2N_.TTF", Vec2(vStartPoint.x + s.width / 2, vStartPoint.y + 60), 45.0f, Color3B(240, 0, 0));
	pPopupOK->setCallBackFunc(CC_CALLBACK_1(InGameScene::Callback_popup_ok, this));
	pPopupOK->addButton("help/text_box5.png", "help/text_box5.png", "", TextureResType::LOCAL, Point(317, 1132), "", -1);
	pPopupOK->addButton("help/h1_btn_prev_up.png", "help/h1_btn_prev_up.png", "", TextureResType::LOCAL, Point(119.5, 217.5), "", 8);
	pPopupOK->addButton("help/h1_btn_next_up.png", "help/h1_btn_next_up.png", "", TextureResType::LOCAL, Point(616.5, 217.5), "", 7);
	pPopupOK->addButton("help/h1_btn_skip_up.png", "help/h1_btn_skip_up.png", "", TextureResType::LOCAL, Point(633, 1231), "", 0);
	pPopupOK->showPopup(this);
}

void InGameScene::ShowPopup5()
{
	Size s = this->getContentSize();

	Size sRectSize = Size(500, 200);
	Vec2 vStartPoint = Vec2(30, 1050);

	UIPopupWindow* pPopupOK = UIPopupWindow::create(NULL);
	pPopupOK->setBackgroundBorard(Sprite::create("help/help_5.png"));
	//pPopupOK->addText("NOW, YOU Could CHECK\nthe number of correct answers.", "fonts/LCDM2N_.TTF", Vec2(vStartPoint.x + s.width / 2, vStartPoint.y + 60), 45.0f, Color3B(240, 0, 0));
	pPopupOK->setCallBackFunc(CC_CALLBACK_1(InGameScene::Callback_popup_ok, this));
	pPopupOK->addButton("help/text_box6.png", "help/text_box6.png", "", TextureResType::LOCAL, Point(357, 638), "", -1);
	pPopupOK->addButton("help/h1_btn_prev_up.png", "help/h1_btn_prev_up.png", "", TextureResType::LOCAL, Point(119.5, 217.5), "", 10);
	pPopupOK->addButton("help/h1_btn_next_up.png", "help/h1_btn_next_up.png", "", TextureResType::LOCAL, Point(616.5, 217.5), "", 9);
	pPopupOK->addButton("help/h1_btn_skip_up.png", "help/h1_btn_skip_up.png", "", TextureResType::LOCAL, Point(633, 1231), "", 0);
	pPopupOK->showPopup(this);
}



