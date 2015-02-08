#include "HelloWorldScene.h"
//#include "cocostudio\CocoStudio.h"
//#include "ui\UILayout.h"
//#include "ui/CocosGUI.h"

USING_NS_CC;
//using namespace std;
//using namespace ui;
//using namespace cocostudio;

#define WID 6
#define HEI 6
#define ANSWER_DIGIT 4
#define LIFE 7

string to_string2(int num)
{
	ostringstream convert; // stream used for the conversion

	convert << num; // insert the textual representation of ¡®Number¡¯ in the characters    in the stream

	return convert.str();
}

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

void HelloWorld::Touch_submit(Ref* sender, Widget::TouchEventType type)
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
			if (nCount == ANSWER_DIGIT && (m_vQuestion.size() == m_vAnswer.size()))
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

void HelloWorld::Touch_NumPad(Ref* sender)
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

		m_TXT_digit->setString(to_string2(m_nDigitCount)+"/"+to_string2(ANSWER_DIGIT));
		
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
		//MessageBox(str.c_str(), "ÀÀ?");
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		//exit(0);		
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		
#endif
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

	m_nDigitCount = 0;
	m_nLife = LIFE;
	m_bGameOver = false;

	// ANSWER_DIGITÀÚ¸® ³­¼ö·Î Á¤´äÀ» »ý¼ºÇÑ´Ù.
	int nSum = 0;
	srand((unsigned int)time(NULL));
	while (m_vQuestion.size() != ANSWER_DIGIT)
	{
		int nNumber = 1 + random(0, WID*HEI);
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

	m_TXT_digit = Label::create("0/" +to_string2(ANSWER_DIGIT), "fonts/LCDM2N_.TTF", 54.f);
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

	// set number pad props.
	for (size_t i = 0; i < WID*HEI; i++)
	{
		string strBtnNormal = "scene4/pad/normal/";
		strBtnNormal += "pad_on_";
		strBtnNormal += to_string2(i+1);
		strBtnNormal += ".png";

		string strBtnPressed = "scene4/pad/pressed/";
		strBtnPressed += "pad_sel_";
		strBtnPressed += to_string2(i+1);
		strBtnPressed += ".png";

		string strBtnDisabled = "scene4/pad/disabled/";
		strBtnDisabled += "pad_off_";
		strBtnDisabled += to_string2(i + 1);
		strBtnDisabled += ".png";

		auto img1 = MenuItemImage::create(strBtnNormal, strBtnNormal);
		auto img2 = MenuItemImage::create(strBtnPressed, strBtnPressed);
		MenuItemToggle* button = MenuItemToggle::createWithCallback(
			CC_CALLBACK_1(HelloWorld::Touch_NumPad, this), img1, img2, NULL);

		auto menu = Menu::create(button, NULL);
		menu->setPosition(Vec2(77 + 113 * (i % WID), 869 - 113 * (i / HEI)));
		this->addChild(menu);

		m_vButtons.push_back(button);
		//button->setOpacity(100);
	}

	m_BTN_submit = Button::create("scene4/btn_enter_up.png", "scene4/btn_enter_down.png");
	m_BTN_submit->setPosition(Vec2(359, 180));
	m_BTN_submit->setScale9Enabled(true);
	m_BTN_submit->setSize(Size(676, 86));
	m_BTN_submit->setPressedActionEnabled(false);
	m_BTN_submit->addTouchEventListener(CC_CALLBACK_2(HelloWorld::Touch_submit, this));
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


void HelloWorld::menuCloseCallback(Ref* pSender)
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
