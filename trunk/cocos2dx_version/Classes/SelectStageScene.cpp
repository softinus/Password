#include "SelectStageScene.h"
#include "Util/Global.h"
#include "Util/DataSingleton.h"

#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

#define PAGE_COUNT 1
#define STAGE_COUNT 9


Scene* SelectStageScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = SelectStageScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}


void SelectStageScene::onButtonBack(Ref* sender, Widget::TouchEventType type)
{
	Button* btn = (Button*)sender;

	//터치 이벤트 실행시 프로그램 종료
	switch (type)
	{
	case Widget::TouchEventType::BEGAN:
		break;
	case Widget::TouchEventType::MOVED:
		break;
	case Widget::TouchEventType::ENDED:
	{
		auto audio = SimpleAudioEngine::getInstance();
		audio->playEffect("raw/enter.wav", false, 1.0f, 1.0f, 1.0f);

		Director::getInstance()->getEventDispatcher()->removeEventListenersForType(EventListener::Type::TOUCH_ONE_BY_ONE);

		auto hScene = MainScene::createScene();
		auto pScene = TransitionFade::create(1.0f, hScene);
		//auto pScene = TransitionFlipAngular::create(1.0f, hScene);
		Director::getInstance()->replaceScene(pScene);
	}
		break;
	}
}


void SelectStageScene::onButtonSelect(Ref* sender, Widget::TouchEventType type)
{
	Button* btn = (Button*)sender;

	//터치 이벤트 실행시 프로그램 종료
	switch (type)
	{
	case Widget::TouchEventType::BEGAN:
		break;
	case Widget::TouchEventType::MOVED:
		break;
	case Widget::TouchEventType::ENDED:
	{

		auto audio = SimpleAudioEngine::getInstance();
		audio->playEffect("raw/enter.wav", false, 1.0f, 1.0f, 1.0f);

		DataSingleton::getInstance().nLevel = atoi(btn->getName().c_str());
		//nLevel = atoi(btn->getName().c_str());

		Director::getInstance()->getEventDispatcher()->removeEventListenersForType(EventListener::Type::TOUCH_ONE_BY_ONE);

		auto hScene = InGameScene::createScene();
		auto pScene = TransitionFade::create(1.0f, hScene);
		//auto pScene = TransitionFlipAngular::create(1.0f, hScene);
		Director::getInstance()->replaceScene(pScene);
	}
	break;
	}

}



bool SelectStageScene::init()
{
	if (!Layer::init())	
	{
		return false;
	}

	Size s = this->getContentSize();

	if (UserDefault::getInstance()->getIntegerForKey("stage") == NULL)
	{
		UserDefault::getInstance()->setIntegerForKey("stage", 0);

		for (int i = 0; i < STAGE_COUNT; ++i)
		{
			string str = "rank_normal_";
			str += to_string2(i + 1);
			UserDefault::getInstance()->setIntegerForKey(str.c_str(), 0);	// save each level's rank.
		}
	}

	
	m_PAGE_left = Button::create("scene2/s2_btn_left_up.png", "scene2/s2_btn_left_down.png");
	m_PAGE_left->setPosition(Vec2(69, 586));
	this->addChild(m_PAGE_left);

	m_PAGE_right = Button::create("scene2/s2_btn_right_up.png", "scene2/s2_btn_right_down.png");
	m_PAGE_right->setPosition(Vec2(651, 586));
	this->addChild(m_PAGE_right);

	m_IMG_title = MenuItemImage::create("scene2/s2_pnl_stage.png", "scene2/s2_pnl_stage.png");
	m_IMG_title->setPosition(Vec2(377, 1025.5));
	this->addChild(m_IMG_title);



	for (int p = 0; p < PAGE_COUNT; ++p)
	{
		auto image1 = MenuItemImage::create("scene2/page_navi_off.png", "scene2/page_navi_off.png", NULL, NULL);
		//MenuItemImage*  IMG_page_indicator = MenuItemImage::create("scene2/page_navi_on.png", "scene2/page_navi_off.png", "scene2/page_navi_off.png");
		MenuItemImage*  IMG_page_indicator = MenuItemImage::create("scene2/page_navi_on.png", "scene2/page_navi_off.png");
		IMG_page_indicator->setDisabledImage(image1);
		IMG_page_indicator->setPosition(Vec2( 360-(PAGE_COUNT*15) + (p*30), 196));	// calc page indicators

		if (p == 0)
			IMG_page_indicator->setEnabled(true);
		else
			IMG_page_indicator->setEnabled(false);

		m_vPage.push_back(IMG_page_indicator);
		this->addChild(IMG_page_indicator);
	}
	

	m_BTN_back = Button::create("scene2/btn_back_up.png", "scene2/btn_back_down.png");
	m_BTN_back->setPosition(Vec2(145, 1200));
	m_BTN_back->addTouchEventListener(CC_CALLBACK_2(SelectStageScene::onButtonBack, this));
	this->addChild(m_BTN_back);

	
	m_PAGE_stage = PageView::create();
	m_PAGE_stage->setContentSize(Size(620, 804));
	m_PAGE_stage->setPosition(Vec2(50, 136));
	m_PAGE_stage->setBackGroundImage("scene2/s2_box01.png");
	m_PAGE_stage->setAnchorPoint(Vec2(0, 0));

	for (int p = 0; p < PAGE_COUNT; ++p)
	{
		Layout* _frame = Layout::create();

		m_IMG_status = MenuItemImage::create("scene2/s2_pnl_normal.png", "scene2/s2_pnl_normal.png");
		m_IMG_status->setPosition(Vec2(m_PAGE_stage->getContentSize().width/2, 750));
		_frame->addChild(m_IMG_status);

		for (int i = 0; i < STAGE_COUNT; ++i)
		{
				string strImageUp = "scene2/s2_btn_stg";
				string strImageDown = "scene2/s2_btn_stg";
				string strImageDisable = "scene2/s2_btn_stg";
				strImageUp += to_string2(i + 1);
				strImageUp += "_up.png";
				strImageDown += to_string2(i + 1);
				strImageDown += "_down.png";
				strImageDisable += to_string2(i + 1);
				strImageDisable += "_deact.png";

				Button* BTN_stage = Button::create(strImageUp, strImageDown, strImageDisable);
				BTN_stage->setName(StringUtils::format("%d", i+1));
				//BTN_stage->setTitleText("rank");
				BTN_stage->setContentSize(Size(150, 150));
				BTN_stage->addTouchEventListener(CC_CALLBACK_2(SelectStageScene::onButtonSelect, this));
				BTN_stage->setZOrder(1);
				BTN_stage->setPosition(Vec2(155 + 155*(i % 3), 555-155*(i / 3) ));
				
				// It depends how many stages cleared.
				int nClearedStage = UserDefault::getInstance()->getIntegerForKey("stage");
				BTN_stage->setBright(i < nClearedStage+1);
				BTN_stage->setEnabled(i < nClearedStage + 1);

				string str = "rank_normal_";
				str += to_string2(i + 1);
				int nCurrRank= UserDefault::getInstance()->getIntegerForKey(str.c_str(), 0);	// restore each level's rank.

				string strIMGrank = "scene2/s2_rank_";
				if (nCurrRank == -1)	// c rank
				{
					strIMGrank += "d.png";
				}
				if (nCurrRank == 0)	// c rank
				{
					strIMGrank += "c.png";
				}
				else if (nCurrRank == 1)	// b rank
				{
					strIMGrank += "b.png";
				}
				else if (nCurrRank == 2)	// a rank
				{
					strIMGrank += "a.png";
				}
				else if (nCurrRank == 3)	// s rank
				{
					strIMGrank += "s.png";
				}

				MenuItemImage* IMG_rank = MenuItemImage::create(strIMGrank, strIMGrank);
				IMG_rank->setZOrder(2);
				IMG_rank->setPosition(Vec2(200 + 155 * (i % 3), 505 - 155 * (i / 3)));

				_frame->addChild(IMG_rank);
				_frame->addChild(BTN_stage);
		}

		m_PAGE_stage->insertPage(_frame, p);
	}

	//m_PAGE_stage->removePageAtIndex(0);

	m_PAGE_stage->addEventListener(CC_CALLBACK_2(SelectStageScene::pageViewEvent, this));


	this->addChild(m_PAGE_stage);

	return true;
}



void SelectStageScene::pageViewEvent(Ref *pSender, PageView::EventType type)
{
	switch (type)
	{
	case PageView::EventType::TURNING:
	{
		PageView* pageView = dynamic_cast<PageView*>(pSender);

		for (int i = 0; i < m_vPage.size(); ++i)
		{
			if (pageView->getCurPageIndex() == i)
			{
				m_vPage[i]->setEnabled(true);
			}
			else
			{
				m_vPage[i]->setEnabled(false);
			}
		}
		

		//_displayValueLabel->setString(CCString::createWithFormat("page = %ld", pageView->getCurPageIndex() + 1)->getCString());
	}
	break;

	default:
		break;
	}
}



Scene* SelectStageScene::scene()
{
	Scene *scene = Scene::create();
	SelectStageScene *layer = SelectStageScene::create();
	scene->addChild(layer);

	return scene;
}

void SelectStageScene::changeScene(void)
{
	////  Director::getInstance()->getEventDispatcher()->removeAllEventListeners();

	//Director::getInstance()->getEventDispatcher()->removeEventListenersForType(EventListener::Type::TOUCH_ONE_BY_ONE);

	//auto hScene = MainScene::createScene();
	//auto pScene = TransitionFade::create(1.0f, hScene);
	////auto pScene = TransitionFlipAngular::create(1.0f, hScene);
	//Director::getInstance()->replaceScene(pScene);
}

bool SelectStageScene::onTouchBegan(Touch* touch, Event* event) {
	auto target = event->getCurrentTarget();
	Point location = target->convertToNodeSpace(touch->getLocation());

	changeScene();
	return true;
}