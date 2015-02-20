#include "HelloWorldScene.h"
//#include "cocostudio\CocoStudio.h"
//#include "ui\UILayout.h"
//#include "ui/CocosGUI.h"

#include "Global.h"
#include "DataSingleton.h"

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

		if (m_bGameOver == false)
		{
			for (int i = 0; i < m_vButtons.size(); ++i)
			{
				if (m_vButtons[i]->getSelectedIndex() == 1)
				{
					m_vAnswer.push_back(i + 1);	// ´­·ÁÁ® ÀÖÀ¸¸é Á¤´ä¿¡ ³Ö°í
					//strAnswer.append(to_string2(m_vAnswer[m_vAnswer.size() - 1]));
				}
			}
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
				m_bGameOver = true;
				m_BTN_submit->setTitleText("RESTART");
				MessageBox("S!", "E");
				Director::getInstance()->end();
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
				MessageBox("Game over", "end");
				Director::getInstance()->end();
			}
			break;
		}
		else
		{
			if (m_bGameOver == false)
				break;

			for (int i = 0; i < m_vButtons.size(); ++i)
			{
				m_vButtons[i]->setSelectedIndex(0);
				m_vButtons[i]->setColor(Color3B(255, 255, 255));
			}
			lst_log->cleanup();
			m_bGameOver = false;
			break;
		}
	}
}

void InGameScene::Touch_NumPad(Ref* sender)
{
	MenuItemToggle* tgl = dynamic_cast<MenuItemToggle*>(sender);

		// change button select status whether it pressed or not.
		if (tgl->getSelectedIndex() == 0)
		{
			++m_nDigitCount;
		}
		else
		{
			--m_nDigitCount;
		}

		m_TXT_digit->setString(to_string2(m_nDigitCount) + "/" + to_string2(m_nAnswerDigit ));
		
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
		//MessageBox(str.c_str(), "ÀÀ?");
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		//exit(0);		
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		
#endif
}

// on "init" you need to initialize your instance
bool InGameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }


	auto keylistener = EventListenerKeyboard::create();
	keylistener->onKeyReleased = CC_CALLBACK_2(InGameScene::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keylistener, this);

	m_nAnswerDigit = 2;
	m_nDigitCount = 0;
	m_bGameOver = false;
	int nLevel = DataSingleton::getInstance().nLevel;
	int nButtonSize = 0;
	int nStartX = 0;
	int nStartY = 0;
	int nMargin = 1;

	if (nLevel == 1)
	{
		m_nWid = 2;
		m_nHei = 2;
		m_nLife = 3;
		m_nAnswerDigit = 2;

		nButtonSize = 338;
		nStartX = 190;
		nStartY = 757;
	}
	else if (nLevel == 2)
	{
		m_nWid = 3;
		m_nHei = 2;
		m_nLife = 4;
		m_nAnswerDigit = 3;

		nButtonSize = 224;
		nStartX = 133;
		nStartY = 700;
	}
	else if (nLevel == 3)
	{
		m_nWid = 3;
		m_nHei = 3;
		m_nLife = 4;
		m_nAnswerDigit = 4;

		nButtonSize = 224;
		nStartX = 133;
		nStartY = 814;
	}
	else if (nLevel == 4)
	{
		m_nWid = 4;
		m_nHei = 3;
		m_nLife = 5;
		m_nAnswerDigit = 4;

		nButtonSize = 168;
		nStartX = 105;
		nStartY = 757;
	}
	else if (nLevel == 5)
	{
		m_nWid = 4;
		m_nHei = 4;
		m_nLife = 5;
		m_nAnswerDigit = 5;

		nButtonSize = 168;
		nStartX = 105;
		nStartY = 842;
	}
	else if (nLevel == 6)
	{
		m_nWid = 5;
		m_nHei = 4;
		m_nLife = 6;
		m_nAnswerDigit = 5;

		nButtonSize = 135;
		nStartX = 88;
		nStartY = 804;
	}
	else if (nLevel == 7)
	{
		m_nWid = 5;
		m_nHei = 5;
		m_nLife = 6;
		m_nAnswerDigit = 6;

		nButtonSize = 168;
		nStartX = 88;
		nStartY = 858;
	}
	else if (nLevel == 8)
	{
		m_nWid = 6;
		m_nHei = 5;
		m_nLife = 7;
		m_nAnswerDigit = 7;

		nButtonSize = 112;
		nStartX = 77;
		nStartY = 870;
	}
	else if (nLevel == 9)
	{
		m_nWid = 6;
		m_nHei = 6;
		m_nLife = 7;
		m_nAnswerDigit = 7;

		nButtonSize = 112;
		nStartX = 77;
		nStartY = 870;
	}
	
	for (int i = 0; i < m_nWid; ++i)
	{
		for (int j = 0; j < m_nHei; ++j)
		{
			auto img1 = MenuItemImage::create("scene4/button/btn_pad_up.png", "scene4/button/btn_pad_up.png");
			auto img2 = MenuItemImage::create("scene4/button/btn_pad_down.png", "scene4/button/btn_pad_down.png");

			MenuItemToggle* button = MenuItemToggle::createWithCallback(
				CC_CALLBACK_1(InGameScene::Touch_NumPad, this), img1, img2, NULL);
						
			auto menu = Menu::create(button, NULL);
			menu->setPosition(Vec2(nStartX + (nButtonSize + nMargin) * i, nStartY - (nButtonSize + nMargin) * j));
			menu->setContentSize(Size(nButtonSize, nButtonSize));

			auto LBL_number = Label::createWithTTF("0", "fonts/LCDM2N_.TTF", 120.f);
			LBL_number->setPosition(Vec2(nStartX + (nButtonSize + nMargin) * i, nStartY - (nButtonSize + nMargin) * j));
			LBL_number->setString(to_string2(j*m_nWid + (i+1)));
			LBL_number->setTextColor(Color4B(17, 140, 24, 200));
			LBL_number->enableOutline(Color4B::WHITE, 1);

			this->addChild(menu);
			this->addChild(LBL_number);

			m_vButtons.push_back(button);
		}
		
	}


	// ANSWER_DIGITÀÚ¸® ³­¼ö·Î Á¤´äÀ» »ý¼ºÇÑ´Ù.
	int nSum = 0;
	srand((unsigned int)time(NULL));
	while (m_vQuestion.size() != m_nAnswerDigit)
	{
		int nNumber = 1 + random(0, m_nWid*m_nHei);
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
	
	// gen answer
	m_TXT_sum = Label::create(to_string2(nSum), "fonts/LCDM2N_.TTF", 54.f);
	m_TXT_sum->setPosition(Vec2(200, 1000));
	m_TXT_sum->setAnchorPoint(Vec2(0, 0));
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
	m_TXT_life->setPosition(Vec2(600, 1000));
	m_TXT_life->setAnchorPoint(Vec2(0, 0));
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
