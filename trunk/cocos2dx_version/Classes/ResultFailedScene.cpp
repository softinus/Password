#include "ResultFailedScene.h"




Scene* ResultFailedScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = ResultFailedScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}


bool ResultFailedScene::init()
{
	if (!Layer::init())	
	{
		return false;
	}

	Size s = this->getContentSize();

	m_IMG_lifewarn = MenuItemImage::create("scene5-2/s5_2_life_warnning.png", "scene5-2/s5_2_life_warnning.png");
	m_IMG_lifewarn->setPosition(Vec2(360, 943));
	this->addChild(m_IMG_lifewarn);

	m_BTN_ad = Button::create("scene5-2/s5_2_btn_go_ad_up.png", "scene5-2/s5_2_btn_go_ad_down.png");
	m_BTN_ad->setPosition(Vec2(368.5, 678));
	this->addChild(m_BTN_ad);

	m_BTN_main = Button::create("scene5-2/btn_main_up.png", "scene5-2/btn_main_down.png");
	m_BTN_main->setPosition(Vec2(381.5, 192.5));
	this->addChild(m_BTN_main);

	//auto action1 = JumpBy::create(1.5f, Point(s.width / 2, 0), 100, 3);
	//auto *fadeIn = FadeIn::create(2.0f);
	////auto *fadeOut = FadeOut::create(1.0f);
	////m_img_Logo->runAction(action);
	//Spawn *sqawn_logo = Spawn::create(action1, fadeIn, NULL);
	//m_img_Logo->runAction(sqawn_logo);

	this->schedule(schedule_selector(ResultFailedScene::scheduleCallback), 2.5f);


	

	return true;
}

void ResultFailedScene::scheduleCallback(float delta)
{
	CCLOG("scheduleCallback : %f", delta);

	//changeScene();
}

Scene* ResultFailedScene::scene()
{
	Scene *scene = Scene::create();
	ResultFailedScene *layer = ResultFailedScene::create();
	scene->addChild(layer);

	return scene;
}

void ResultFailedScene::changeScene(void)
{
	//  Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
	Director::getInstance()->getEventDispatcher()->removeEventListenersForType(EventListener::Type::TOUCH_ONE_BY_ONE);

	auto hScene = MainScene::createScene();
	auto pScene = TransitionFade::create(1.0f, hScene);
	//auto pScene = TransitionFlipAngular::create(1.0f, hScene);
	Director::getInstance()->replaceScene(pScene);
}

bool ResultFailedScene::onTouchBegan(Touch* touch, Event* event) {
	auto target = event->getCurrentTarget();
	Point location = target->convertToNodeSpace(touch->getLocation());

	changeScene();
	return true;
}