#include "InGameScene.h"
//#include "cocostudio\CocoStudio.h"
//#include "ui\UILayout.h"
//#include "ui/CocosGUI.h"

#include "Util/Global.h"
#include "Util/DataSingleton.h"
#include "GPGS/GameSharing.h"
#include "SimpleAudioEngine.h"
#include "network/HttpRequest.h"
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

	int nLevel = DataSingleton::getInstance().nLevel;
	int nButtonSize = 0;
	int nStartX = 0;
	int nStartY = 0;
	int nMargin = 1;
	int nFontSize = 0;

	if (nLevel == 1)
	{
		m_nWid = 2;
		m_nHei = 2;
		m_nLife = 3;
		m_nAnswerDigit = 2;

		m_nRepeatStage_MAX = 10;
		m_nRecoverLife = 1;
		m_nTime = 600;

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

		m_nRepeatStage_MAX = 12;
		m_nRecoverLife = 1;
		m_nTime = 660;

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

		m_nRepeatStage_MAX = 14;
		m_nRecoverLife = 1;
		m_nTime = 600;

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

		m_nRepeatStage_MAX = 16;
		m_nRecoverLife = 2;
		m_nTime = 780;

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

		m_nRepeatStage_MAX = 18;
		m_nRecoverLife = 2;
		m_nTime = 840;

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

		m_nRepeatStage_MAX = 20;
		m_nRecoverLife = 2;
		m_nTime = 900;

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

		m_nRepeatStage_MAX = 23;
		m_nRecoverLife = 3;
		m_nTime = 1020;

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

		m_nRepeatStage_MAX = 26;
		m_nRecoverLife = 3;
		m_nTime = 1140;

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

		m_nRepeatStage_MAX = 30;
		m_nRecoverLife = 3;
		m_nTime = 1200;


		nButtonSize = 112;
		nStartX = 77;
		nStartY = 870;
		nFontSize = 58;
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




	// ANSWER_DIGITÀÚ¸® ³­¼ö·Î Á¤´äÀ» »ý¼ºÇÑ´Ù.
	int nSum = 0;
	srand((unsigned int)time(NULL));
	while (m_vQuestion.size() != m_nAnswerDigit)
	{
		int nNumber = random(1, m_nWid*m_nHei);
		bool bAlreadyHas = false;
		for (int i = 0; i < m_vQuestion.size(); ++i)
		{
			if (m_vQuestion[i] == nNumber)
			{
				bAlreadyHas = true;
				break;
			}
		}
		if (bAlreadyHas == false)
		{
			m_vQuestion.push_back(nNumber);
			nSum += nNumber;
		}
	}

	m_sumNew = nSum;

	// gen answer
	m_TXT_sum = Label::create(to_string2(nSum), "fonts/LCDM2N_.TTF", 54.f);
	m_TXT_sum->setPosition(Vec2(200, 1000));
	m_TXT_sum->setAnchorPoint(Vec2(0, 0));
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
	m_TXT_life->setPosition(Vec2(580, 1000));
	m_TXT_life->setAnchorPoint(Vec2(0, 0));
	m_TXT_life->setAlignment(TextHAlignment::CENTER);
	this->addChild(m_TXT_life);

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Size s = this->getContentSize();

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
	lst_log->setDirection(ui::ScrollView::Direction::VERTICAL);
	lst_log->setBounceEnabled(true);
	lst_log->setBackGroundImage("scene4/box_log.png");
	lst_log->setBackGroundImageScale9Enabled(true);
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

	lst_log->setItemModel(default_item);
	lst_log->pushBackDefaultItem();
	this->addChild(lst_log);


	return true;
}


void InGameScene::Touch_submit(Ref* sender, Widget::TouchEventType type)
{
	Button* btn = (Button*)sender;

	auto audio = SimpleAudioEngine::getInstance();
	audio->playEffect("raw/enter.wav", false, 1.0f, 1.0f, 1.0f);

	//ÅÍÄ¡ ÀÌº¥Æ® ½ÇÇà½Ã ÇÁ·Î±×·¥ Á¾·á
	switch (type)
	{
	case Widget::TouchEventType::BEGAN:
		break;
	case Widget::TouchEventType::MOVED:
		break;
	case Widget::TouchEventType::ENDED:

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
			if (m_nCurrStageRepeatCount == m_nRepeatStage_MAX)
			{
				FinishStage();
			}
			else
			{
				// TODO : ÀÌÂÊ¿¡ ÇöÀç ´­¸° ¹öÆ° ÃÊ±âÈ­, Á¤´ä ÃÊ±âÈ­, ¸ÅÄª¼®¼¼½º ¶ç¿ì±â, ¶óÀÌÇÁ È¸º¹
				//FinishStage();
				Sprite* SPR_match = Sprite::create("scene4/s4_pup_success.png");
				SPR_match->setPosition(this->getContentSize().width / 2, this->getContentSize().height / 2);
				this->addChild(SPR_match);
				this->setTouchEnabled(false);

				

				//Text* txt = Text::create("   =====SUCCESS! =====   ", "fonts/LCDM2N_.TTF", 30.f);

				//Layout* default_item = Layout::create();
				//default_item->setTouchEnabled(true);
				//default_item->setContentSize(txt->getContentSize());
				//txt->setPosition(Vec2(default_item->getContentSize().width / 2.0f,
				//	default_item->getContentSize().height / 2.0f));
				//default_item->addChild(txt);

				//lst_log->setItemModel(default_item);
				//lst_log->pushBackDefaultItem();
				//this->addChild(lst_log);

				++m_nCurrStageRepeatCount;
			}

			return;
		}

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
		//MessageBox(strAnswer.c_str(), "Result");
		m_vAnswer.clear();
		lst_log->scrollToBottom(.5f, false);

		// life
		--m_nLife;
		m_TXT_life->setString(to_string2(m_nLife));
			
		if (m_nLife == 0)
		{
			//MessageBeep(0);
			//MessageBox("Game over", "end");
			//Director::getInstance()->end();
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
		
	m_TXT_digit->setString(to_string2(m_nDigitCount) + "/" + to_string2(m_nAnswerDigit));

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
}

void InGameScene::changeScene(void)
{
	//Director::getInstance()->getEventDispatcher()->removeEventListenersForType(EventListener::Type::TOUCH_ONE_BY_ONE);

	auto hScene = SelectStageScene::createScene();
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

void InGameScene::FinishStage()
{
	int nSavedStage = UserDefault::getInstance()->getIntegerForKey("stage", 0);
	if (nSavedStage < DataSingleton::getInstance().nLevel)	// if this level is highest level...
	{
		UserDefault::getInstance()->setIntegerForKey("stage", DataSingleton::getInstance().nLevel);	// update save data.

		//submit score to Google play store game service...
		GameSharing::SubmitScore(DataSingleton::getInstance().nLevel, 0);
}
	showResult();
}
