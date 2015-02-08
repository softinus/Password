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
}

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