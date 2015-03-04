#include "ResultScene.h"



Scene* ResultScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = ResultScene::create();

	// add layer as a child to scene
	scene->addChild(layer);


	// return the scene
	return scene;
}
//
//void ResultScene::SetResult(bool bSuccess)
//{
//	m_bSuccess = bSuccess;
//}

bool ResultScene::init()
{
	if (!Layer::init())	
	{
		return false;
	}

	Size s = this->getContentSize();


	int nTotalCount = DataSingleton::getInstance().nSpentCount;

	m_IMG_result = MenuItemImage::create("scene5-1/s5_result.png", "scene5-1/s5_result.png");
	m_IMG_result->setPosition(Vec2(-260, 1144));
	this->addChild(m_IMG_result);


	string str_rank = "rank_normal_";
	str_rank += to_string2(DataSingleton::getInstance().nLevel);
	int nSavedRank= UserDefault::getInstance()->getIntegerForKey(str_rank.c_str(), 0);

	string strRankImagePath = "";
	if (m_bSuccess)
	{
		if (nTotalCount == 1)
		{
			strRankImagePath = "scene5-1/s5_rank_s.png";
			if (nSavedRank != 3)
				UserDefault::getInstance()->setIntegerForKey(str_rank.c_str(), 3);
		}
		else if (nTotalCount == 2)
		{
			strRankImagePath = "scene5-1/s5_rank_a.png";
			if (nSavedRank < 2)
				UserDefault::getInstance()->setIntegerForKey(str_rank.c_str(), 2);
		}
		else if (nTotalCount == 3)
		{
			strRankImagePath = "scene5-1/s5_rank_b.png";
			if (nSavedRank < 1)
				UserDefault::getInstance()->setIntegerForKey(str_rank.c_str(), 1);
		}
		else
		{
			strRankImagePath = "scene5-1/s5_rank_c.png";
			if (nSavedRank < 0)
				UserDefault::getInstance()->setIntegerForKey(str_rank.c_str(), 0);
		}
	}
	else
	{
		MessageBox("D","D");
		strRankImagePath = "scene5-1/s5_rank_d.png";
		if (nSavedRank < -1)
			UserDefault::getInstance()->setIntegerForKey(str_rank.c_str(), 0);
	}
	


	m_IMG_rank = MenuItemImage::create(strRankImagePath, strRankImagePath);
	m_IMG_rank->setPosition(Vec2(990, 891.5));
	this->addChild(m_IMG_rank);


	string strCount = "count : " + to_string2(nTotalCount);
	m_LBL_time = Label::createWithTTF(strCount, "fonts/LCDM2N_.TTF", 45.f);
	m_LBL_time->setPosition(Vec2(580, 740));
	m_LBL_time->setAnchorPoint(Vec2(0, 0));
	this->addChild(m_LBL_time);

	m_BTN_main = Button::create("scene5-1/btn_main_up.png", "scene5-1/btn_main_down.png");
	m_BTN_main->setPosition(Vec2(443.5, 396.5));
	this->addChild(m_BTN_main);

	m_BTN_main = Button::create("scene5-1/btn_main_up.png", "scene5-1/btn_main_down.png");
	m_BTN_main->setPosition(Vec2(443.5, 396.5));
	this->addChild(m_BTN_main);

	


	this->schedule(schedule_selector(ResultScene::scheduleCallback), 2.5f);

	{
		MoveTo *action_0 = MoveTo::create(1.5f, Point(260, 1144));
		EaseElasticInOut *action_1 = EaseElasticInOut::create(action_0);    // action, Åº¼º
		m_IMG_result->runAction(action_1);
	}
	{
		MoveTo *action_0 = MoveTo::create(1.5f, Vec2(495, 891.5));
		EaseElasticInOut *action_1 = EaseElasticInOut::create(action_0);    // action, Åº¼º
		m_IMG_rank->runAction(action_1);
	}

	{
		MoveTo *action_0 = MoveTo::create(1.5f, Vec2(290, 740));
		EaseElasticInOut *action_1 = EaseElasticInOut::create(action_0);    // action, Åº¼º
		m_LBL_time->runAction(action_1);
	}
	

	return true;
}

void ResultScene::scheduleCallback(float delta)
{
	CCLOG("scheduleCallback : %f", delta);

	changeScene();
}

Scene* ResultScene::scene()
{
	Scene *scene = Scene::create();
	ResultScene *layer = ResultScene::create();
	scene->addChild(layer);

	return scene;
}

void ResultScene::changeScene(void)
{
	//  Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
	Director::getInstance()->getEventDispatcher()->removeEventListenersForType(EventListener::Type::TOUCH_ONE_BY_ONE);

	auto hScene = SelectStageScene::createScene();
	auto pScene = TransitionFade::create(1.0f, hScene);
	//auto pScene = TransitionFlipAngular::create(1.0f, hScene);
	Director::getInstance()->replaceScene(pScene);
}

bool ResultScene::onTouchBegan(Touch* touch, Event* event) {
	auto target = event->getCurrentTarget();
	Point location = target->convertToNodeSpace(touch->getLocation());

	changeScene();
	return true;
}