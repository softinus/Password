#include "HelloWorldScene.h"
//#include "cocostudio\CocoStudio.h"
//#include "ui\UILayout.h"
//#include "ui/CocosGUI.h"

USING_NS_CC;
//using namespace std;
//using namespace ui;
//using namespace cocostudio;


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

		if (btn->getTitleText() == "SUBMIT")
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

			strPrint += " (";
			strPrint += to_string2(nCount);
			strPrint += ")";

			// ´Ù ¸Â­Ÿ°í ÀÚ¸´¼öµµ ¸ÂÀ¸¸é Á¤´äÀÓ
			if (nCount == 4 && (m_vQuestion.size() == m_vAnswer.size()))
			{
				m_bGameOver = true;
				m_BTN_submit->setTitleText("RESTART");
				MessageBox("S!", "E");
				Director::getInstance()->end();
			}

			// list hint element setting
			Button* btn_1 = Button::create("common/button.png", "common/buttonHighlighted.png");
			btn_1->setTitleText(strPrint);
			btn_1->setScale9Enabled(true);
			btn_1->setContentSize(Size(200, 35));

			Layout* default_item = Layout::create();
			default_item->setTouchEnabled(true);
			default_item->setContentSize(btn_1->getContentSize());
			btn_1->setPosition(Vec2(default_item->getContentSize().width / 2.0f,
				default_item->getContentSize().height / 2.0f));
			default_item->addChild(btn_1);

			lst_log->pushBackCustomItem(default_item);
			//MessageBox(strAnswer.c_str(), "Result");
			m_vAnswer.clear();
			lst_log->scrollToBottom(.5f, true);

			// life
			--m_nLife;
			m_LBL_life->setString("Life : " + to_string2(m_nLife));

			if (m_nLife == 0)
			{
				//MessageBeep(0);
				MessageBox("Gover", "end");
				Director::getInstance()->end();
			}
			break;
		}
		else if (btn->getTitleText() == "RESTART")
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
			btn->setTitleText("SUBMIT");
			break;
		}
	}
}

void HelloWorld::Touch_NumPad(Ref* sender)
{
	MenuItemToggle* tgl = (MenuItemToggle*)sender;

		// change button select status whether it pressed or not.
		if (tgl->isSelected())
		{
		}
		else
		{
		}
		
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

	m_nLife = 4;
	m_bGameOver = false;

	// 4ÀÚ¸® ³­¼ö·Î Á¤´äÀ» »ý¼ºÇÑ´Ù.
	int nSum = 0;
	srand((unsigned int)time(NULL));
	while (m_vQuestion.size() != 4)
	{
		int nNumber = 1 + rand() % 9;
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
	m_LBL_sum = Label::create("Sum : "+to_string2(nSum), "fonts/Marker Felt.ttf", 30.f);
	m_LBL_sum->setPosition(Vec2(255, 725));
	m_LBL_sum->setAnchorPoint(Vec2(0, 0));
	this->addChild(m_LBL_sum);	

	m_LBL_life = Label::create("Life : " + to_string2(m_nLife), "fonts/Marker Felt.ttf", 30.f);
	m_LBL_life->setPosition(Vec2(255, 685));
	m_LBL_life->setAnchorPoint(Vec2(0, 0));
	this->addChild(m_LBL_life);
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
		
	Size s = this->getContentSize();

	// set number pad props.
	for (size_t i = 0; i < 9; i++)
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
		menu->setPosition(Vec2(s.width / 2.f - 100 + 113 * (i % 3), s.height / 2.f + 100 - 113 * (i / 3)));
		this->addChild(menu);

		m_vButtons.push_back(button);
		//button->setOpacity(100);
	}

	m_BTN_submit = Button::create("common/button.png", "common/buttonHighlighted.png");
	m_BTN_submit->setPosition(Vec2(240, 150));
	m_BTN_submit->setScale9Enabled(true);
	m_BTN_submit->setSize(Size(300, 100));
	m_BTN_submit->setPressedActionEnabled(true);
	m_BTN_submit->setTitleFontSize(42.f);
	m_BTN_submit->setTitleText("SUBMIT");
	m_BTN_submit->setTitleColor(Color3B(255, 255, 255));
	m_BTN_submit->addTouchEventListener(CC_CALLBACK_2(HelloWorld::Touch_submit, this));
	this->addChild(m_BTN_submit);

	int x = 1;
	lst_log = ListView::create();
	lst_log->setDirection(ui::ScrollView::Direction::VERTICAL);
	lst_log->setBounceEnabled(true);
	lst_log->setBackGroundImage("common/green_edit.png");
	lst_log->setBackGroundImageScale9Enabled(true);
	lst_log->setContentSize(Size(200, 150));
	lst_log->setPosition(Vec2(20, s.height-170));
	lst_log->setTag(100);

	Label* lbl = Label::createWithTTF("Fade", "fonts/Marker Felt.ttf", 20.0f);
	Button* btn_1 = Button::create("common/button.png", "common/buttonHighlighted.png");
	btn_1->setTitleText("History (hint)");
	btn_1->setScale9Enabled(true);
	btn_1->setContentSize(Size(200, 35));

	Layout* default_item = Layout::create();
	default_item->setTouchEnabled(true);
	default_item->setContentSize(btn_1->getContentSize());
	btn_1->setPosition(Vec2(default_item->getContentSize().width / 2.0f,
		default_item->getContentSize().height / 2.0f));
	default_item->addChild(btn_1);
	
	lst_log->setItemModel(default_item);
	lst_log->pushBackDefaultItem();
	this->addChild(lst_log);



	//ÄÚÄÚ½º ½ºÆ©µð¿À ÆÄÀÏ ºÒ·¯¿À´Â ¼³Á¤
	//auto node = CSLoader::createNode("Scene2.csb");
	//this->addChild(node);

	//_layout = static_cast<Layout*>(cocostudio::GUIReader::getInstance()->widgetFromBinaryFile("Scene2.csb"));
	//this->addChild(_layout);
	//Size screenSize = CCDirector::getInstance()->getWinSize();
	//Size rootSize = _layout->getContentSize();
	//this->setPosition(Vec2((screenSize.width - rootSize.width) / 2,
	//	(screenSize.height - rootSize.height) / 2));

    
 //   auto sprite = Sprite::create("HelloWorld.png");    // add "HelloWorld" splash screen"
 //   sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));	// position the sprite on the center of the screen
	//this->addChild(sprite, 0);	// add the sprite as a child to this layer
    
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
