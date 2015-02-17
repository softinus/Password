#include "StartLogoScene.h"




bool StartLogoScene::init()
{
	if (!Layer::init())	
	{
		return false;
	}

	Size s = this->getContentSize();

	m_img_Logo = MenuItemImage::create("scene1/logo_gab.png", "scene1/logo_gab.png");
	m_img_Logo->setPosition(Vec2(s.width / 2, s.height / 2));
	this->addChild(m_img_Logo);

	changeScene();

	return true;
}
Scene* StartLogoScene::scene()
{
	Scene *scene = Scene::create();
	StartLogoScene *layer = StartLogoScene::create();
	scene->addChild(layer);

	return scene;
}

void StartLogoScene::changeScene(void) {
	//  Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
	Director::getInstance()->getEventDispatcher()->removeEventListenersForType(EventListener::Type::TOUCH_ONE_BY_ONE);

	auto hScene = HelloWorld::createScene();
	auto pScene = TransitionFade::create(1.0f, hScene);
	Director::getInstance()->replaceScene(pScene);
}

bool StartLogoScene::onTouchBegan(Touch* touch, Event* event) {
	auto target = event->getCurrentTarget();
	Point location = target->convertToNodeSpace(touch->getLocation());

	changeScene();
	return true;
}