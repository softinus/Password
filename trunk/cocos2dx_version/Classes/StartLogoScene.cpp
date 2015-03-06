#include "StartLogoScene.h"




Scene* StartLogoScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = StartLogoScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}


bool StartLogoScene::init()
{
	if (!Layer::init())	
	{
		return false;
	}

	Size s = this->getContentSize();

	m_img_Logo = MenuItemImage::create("logo_gab.png", "logo_gab.png");
	m_img_Logo->setPosition(Vec2(0, s.height / 2));
	m_img_Logo->setOpacity(0);
	this->addChild(m_img_Logo);

	//auto action1 = JumpBy::create(1.5f, Point(s.width / 2, 0), 100, 3);
	auto *fadeIn = FadeIn::create(2.0f);
	//auto *fadeOut = FadeOut::create(1.0f);
	//m_img_Logo->runAction(action);
	//Spawn *sqawn_logo = Spawn::create(action1, fadeIn, NULL);
	m_img_Logo->runAction(fadeIn);

	this->schedule(schedule_selector(StartLogoScene::scheduleCallback), 2.5f);


	

	return true;
}

void StartLogoScene::scheduleCallback(float delta)
{
	CCLOG("scheduleCallback : %f", delta);

	changeScene();
}

Scene* StartLogoScene::scene()
{
	Scene *scene = Scene::create();
	StartLogoScene *layer = StartLogoScene::create();
	scene->addChild(layer);

	return scene;
}

void StartLogoScene::changeScene(void)
{
	//  Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
	Director::getInstance()->getEventDispatcher()->removeEventListenersForType(EventListener::Type::TOUCH_ONE_BY_ONE);

	auto hScene = MainScene::createScene();
	auto pScene = TransitionFade::create(1.0f, hScene);
	//auto pScene = TransitionFlipAngular::create(1.0f, hScene);
	Director::getInstance()->replaceScene(pScene);
}

bool StartLogoScene::onTouchBegan(Touch* touch, Event* event) {
	auto target = event->getCurrentTarget();
	Point location = target->convertToNodeSpace(touch->getLocation());

	changeScene();
	return true;
}