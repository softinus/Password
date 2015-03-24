#include "SelectStageScene.h"
#include "Util/Global.h"
#include "Util/DataSingleton.h"

#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

#define STAGE_COUNT 9


Scene* SelectStageScene::createScene2()
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
		audio->playEffect("raw/number.wav", false, 1.0f, 1.0f, 1.0f);

		Director::getInstance()->getEventDispatcher()->removeEventListenersForType(EventListener::Type::TOUCH_ONE_BY_ONE);

		auto hScene = MainScene::createScene();
		auto pScene = TransitionFade::create(1.0f, hScene);
		//auto pScene = TransitionFlipAngular::create(1.0f, hScene);
		Director::getInstance()->replaceScene(pScene);
	}
		break;
	}
}


void SelectStageScene::onButtonSelectStage(Ref* sender, Widget::TouchEventType type)
{
	Button* btn = (Button*)sender;

	switch (type)
	{
	case Widget::TouchEventType::BEGAN:
		break;
	case Widget::TouchEventType::MOVED:
		break;
	case Widget::TouchEventType::ENDED:
	{

		auto audio = SimpleAudioEngine::getInstance();
		audio->playEffect("raw/number.wav", false, 1.0f, 1.0f, 1.0f);

		DataSingleton::getInstance().nPlayMode = m_PAGE_stage->getCurPageIndex();	// current mode
		DataSingleton::getInstance().nLevel = atoi(btn->getName().c_str());	// current level
		Director::getInstance()->getEventDispatcher()->removeEventListenersForType(EventListener::Type::TOUCH_ONE_BY_ONE);


		auto hScene = InGameScene::createScene();
		auto pScene = TransitionFade::create(1.0f, hScene);
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

	//Size s = this->getContentSize();


	if (UserDefault::getInstance()->getIntegerForKey("init") == NULL)	// if it has no record.
	{
		UserDefault::getInstance()->setIntegerForKey("init", true);

		UserDefault::getInstance()->setIntegerForKey("stage_clear_easy", 0);
		UserDefault::getInstance()->setIntegerForKey("stage_clear_normal", -1);

		for (int i = 0; i < STAGE_COUNT; ++i)
		{
			string str = "rank_easy_";
			str += to_string2(i + 1);
			UserDefault::getInstance()->setIntegerForKey(str.c_str(), 0);	// save each level's rank.

			string str2 = "rank_normal_";
			str2 += to_string2(i + 1);
			UserDefault::getInstance()->setIntegerForKey(str2.c_str(), 0);	// save each level's rank.

			string str3 = "rank_challenge_";
			str3 += to_string2(i + 1);
			UserDefault::getInstance()->setIntegerForKey(str3.c_str(), 0);	// save each level's rank.
		}
	}

	
	m_BTN_left = Button::create("scene2/s2_btn_left_up.png", "scene2/s2_btn_left_down.png");
	m_BTN_left->setPosition(Vec2(69, 586));
	m_BTN_left->addTouchEventListener(CC_CALLBACK_2(SelectStageScene::onButtonPageLeft, this));
	m_BTN_left->setZOrder(10);
	this->addChild(m_BTN_left);

	m_BTN_right = Button::create("scene2/s2_btn_right_up.png", "scene2/s2_btn_right_down.png");
	m_BTN_right->setPosition(Vec2(651, 586));
	m_BTN_right->addTouchEventListener(CC_CALLBACK_2(SelectStageScene::onButtonPageRight, this));
	m_BTN_right->setZOrder(10);
	this->addChild(m_BTN_right);

	m_IMG_title = MenuItemImage::create("scene2/s2_pnl_stage.png", "scene2/s2_pnl_stage.png");
	m_IMG_title->setPosition(Vec2(377, 1025.5));
	this->addChild(m_IMG_title);



	// page indicators
	for (int p = 0; p < EStage::ALL; ++p)
	{
		string strNaviOn= "";
		if (p == EStage::CHALLENGE)	// Show red navigator when turn to page in challenge mode.
		{
			strNaviOn = "scene2/page_navi_on2.png";
		}
		else
		{
			strNaviOn = "scene2/page_navi_on.png";
		}
		auto image1 = MenuItemImage::create("scene2/page_navi_off.png", "scene2/page_navi_off.png", NULL, NULL);
		MenuItemImage*  IMG_page_indicator = MenuItemImage::create(strNaviOn, strNaviOn);
		IMG_page_indicator->setDisabledImage(image1);
		IMG_page_indicator->setPosition(Vec2(370 - (EStage::ALL * 15) + (p * 30), 196));	// calc page indicators

		if (p == 0)
			IMG_page_indicator->setEnabled(true);
		else
			IMG_page_indicator->setEnabled(false);

		m_vPageIndicators.push_back(IMG_page_indicator);
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

	for (int p = 0; p < EStage::ALL; ++p)
	{
		Layout* _frame = Layout::create();

		MenuItemImage* IMG_status = NULL;
		if (p == EStage::EASY)
		{
			IMG_status = MenuItemImage::create("scene2/s2_pnl_easy.png", "scene2/s2_pnl_easy.png");
		}
		else if (p == EStage::NORMAL)
		{
			IMG_status = MenuItemImage::create("scene2/s2_pnl_normal.png", "scene2/s2_pnl_normal.png");
		}
		else if (p == EStage::CHALLENGE)
		{
			IMG_status = MenuItemImage::create("scene2/s2_pnl_cha.png", "scene2/s2_pnl_cha.png");
		}
		IMG_status->setPosition(Vec2(m_PAGE_stage->getContentSize().width/2, 750));
		_frame->addChild(IMG_status);

		for (int i = 0; i < STAGE_COUNT; ++i)
		{
				string strImageUp = "scene2/s2_btn_stg";
				string strImageDown = "scene2/s2_btn_stg";
				string strImageDisable = "scene2/s2_btn_stg";
				strImageUp += to_string2(i + 1);
				if (p == EStage::EASY || p == EStage::NORMAL)
				{
					strImageUp += "_up.png";
					strImageDown += to_string2(i + 1);
					strImageDown += "_down.png";
					strImageDisable += to_string2(i + 1);
					strImageDisable += "_deact.png";
				}
				else if (p == EStage::CHALLENGE)
				{
					strImageUp += "_up2.png";
					strImageDown += to_string2(i + 1);
					strImageDown += "_down2.png";
					strImageDisable += to_string2(i + 1);
					strImageDisable += "_deact.png";
				}


				Button* BTN_stage = Button::create(strImageUp, strImageDown, strImageDisable);
				BTN_stage->setName(StringUtils::format("%d", i+1));
				//BTN_stage->setTitleText("rank");
				BTN_stage->setContentSize(Size(150, 150));
				BTN_stage->addTouchEventListener(CC_CALLBACK_2(SelectStageScene::onButtonSelectStage, this));
				BTN_stage->setZOrder(1);
				BTN_stage->setPosition(Vec2(155 + 155*(i % 3), 555-155*(i / 3) ));
				
				// It depends how many stages cleared.
				int nClearedStage = 0;
				if (p == EStage::EASY)
				{
					nClearedStage = UserDefault::getInstance()->getIntegerForKey("stage_clear_easy");
					BTN_stage->setBright(i < nClearedStage + 1);
					BTN_stage->setEnabled(i < nClearedStage + 1);
				}
				else if (p == EStage::NORMAL)
				{
					nClearedStage = UserDefault::getInstance()->getIntegerForKey("stage_clear_normal");
					BTN_stage->setBright(i < nClearedStage + 1);
					BTN_stage->setEnabled(i < nClearedStage + 1);
				}
				else if (p == EStage::CHALLENGE)
				{
					BTN_stage->setBright(true);
					BTN_stage->setEnabled(true);
				}
				
				
				MenuItemImage* IMG_rank = NULL;
				if (p != EStage::CHALLENGE)	// show rank when it's not challenge mode.
				{
					/*if (p == EStage::NORMAL)
					{
						m_PAGE_stage->scrollToPage(0);
					}*/
					IMG_rank = ShowRank(p, i);
					_frame->addChild(IMG_rank);
				}
				else
				{
					// userDefault prefix of key.
					string str = "rank_challenge_";
					str += to_string2(i + 1);
					int nCurrRank = UserDefault::getInstance()->getIntegerForKey(str.c_str(), -1);	// restore each level's rank.

					Label* LBL_stage = Label::create(to_string2(nCurrRank), "fonts/LCDM2N_.TTF", 40.0f);
					LBL_stage->setZOrder(11);
					LBL_stage->setPosition(Vec2(212 + 155 * (i % 3), 530 - 155 * (i / 3)));
					_frame->addChild(LBL_stage);
				}
				
				_frame->addChild(BTN_stage);
		}

		m_PAGE_stage->insertPage(_frame, p);
	}


	m_PAGE_stage->scrollToPage(DataSingleton::getInstance().nPlayMode);

	//m_PAGE_stage->removePageAtIndex(0);

	m_PAGE_stage->addEventListener(CC_CALLBACK_2(SelectStageScene::pageViewEvent, this));


	this->addChild(m_PAGE_stage);

	return true;
}


void SelectStageScene::onButtonPageLeft(Ref* sender, Widget::TouchEventType type)
{
	switch (type)
	{
	case Widget::TouchEventType::BEGAN:
		break;
	case Widget::TouchEventType::MOVED:
		break;
	case Widget::TouchEventType::ENDED:
		size_t idx = m_PAGE_stage->getCurPageIndex();
		m_PAGE_stage->scrollToPage(idx - 1);
		break;
	}
	
}
void SelectStageScene::onButtonPageRight(Ref* sender, Widget::TouchEventType type)
{
	switch (type)
	{
	case Widget::TouchEventType::BEGAN:
		break;
	case Widget::TouchEventType::MOVED:
		break;
	case Widget::TouchEventType::ENDED:
		size_t idx = m_PAGE_stage->getCurPageIndex();
		m_PAGE_stage->scrollToPage(idx + 1);
		break;
	}
}


void SelectStageScene::pageViewEvent(Ref *pSender, PageView::EventType type)
{
	switch (type)
	{
	case PageView::EventType::TURNING:
	{
		PageView* pageView = dynamic_cast<PageView*>(pSender);

		for (int i = 0; i < m_vPageIndicators.size(); ++i)
		{
			if (pageView->getCurPageIndex() == i)	// page indicators
			{
				m_vPageIndicators[i]->setEnabled(true);
			}
			else
			{
				m_vPageIndicators[i]->setEnabled(false);
			}

			if (pageView->getCurPageIndex() == m_vPageIndicators.size()-1)	// when turn to last page change button color
			{
				m_BTN_left->loadTextureNormal("scene2/s2_btn_left_up2.png");
				m_BTN_left->loadTexturePressed("scene2/s2_btn_left_down2.png");

				m_BTN_right->loadTextureNormal("scene2/s2_btn_right_up2.png");
				m_BTN_right->loadTexturePressed("scene2/s2_btn_right_down2.png");
			}
			else
			{
				m_BTN_left->loadTextureNormal("scene2/s2_btn_left_up.png");
				m_BTN_left->loadTexturePressed("scene2/s2_btn_left_down.png");

				m_BTN_right->loadTextureNormal("scene2/s2_btn_right_up.png");
				m_BTN_right->loadTexturePressed("scene2/s2_btn_right_down.png");
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

MenuItemImage* SelectStageScene::ShowRank(int p, int i)
{
	// userDefault prefix of key.
	string str = "rank_";
	if (p == EStage::EASY)
		str += "easy_";
	else if (p == EStage::NORMAL)
		str += "normal_";

	str += to_string2(i + 1);
	int nCurrRank = UserDefault::getInstance()->getIntegerForKey(str.c_str(), -1);	// restore each level's rank.
	bool bUnranked = false;

	string strIMGrank = "scene2/s2_rank_";
	if (nCurrRank == ERank::D_RANK)
	{
		strIMGrank += "d.png";
	}
	if (nCurrRank == ERank::C_RANK)	// c rank
	{
		strIMGrank += "c.png";
	}
	else if (nCurrRank == ERank::B_RANK)	// b rank
	{
		strIMGrank += "b.png";
	}
	else if (nCurrRank == ERank::A_RANK)	// a rank
	{
		strIMGrank += "a.png";
	}
	else if (nCurrRank == ERank::S_RANK)	// s rank
	{
		strIMGrank += "s.png";
	}
	else
	{
		bUnranked = true;
	}

	MenuItemImage* IMG_rank = MenuItemImage::create(strIMGrank, strIMGrank);
	IMG_rank->setZOrder(11);
	IMG_rank->setPosition(Vec2(197 + 155 * (i % 3), 515 - 155 * (i / 3)));
	IMG_rank->setVisible(!bUnranked);	// 언랭크이면 표시 안함.

	// 새로 깨면 연출 동작
	if (DataSingleton::getInstance().nCleardStage == i + 1 && DataSingleton::getInstance().bNewRanked)
	{
		auto fadeout = FadeOut::create(0.1f);
		auto scale1 = ScaleTo::create(0.1f, 2.5f);
		auto roate1 = RotateBy::create(0.1f, 35);
		auto sq1 = Spawn::create(fadeout, scale1, roate1, NULL);

		auto fadein = FadeIn::create(0.8f);
		auto delay = DelayTime::create(0.3f);

		auto scale2 = ScaleTo::create(0.7f, 1.0f);
		auto roate2 = RotateBy::create(0.7f, -35);
		auto sq2 = Spawn::create(scale2, roate2, NULL);
		auto easeEinout = EaseElasticInOut::create(sq2);

		auto seq = Sequence::create(sq1, fadein, delay, easeEinout, NULL);
		IMG_rank->runAction(seq);

		DataSingleton::getInstance().nCleardStage = -1;	// 한번 플레이 하면 끝 [3/9/2015 ChoiJunHyeok]
	}



	return IMG_rank;
}
