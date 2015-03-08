#include "MainScene.h"

#include "GPGS/GameSharing.h"
#include "CustomUI/UIPopupWindow.h"

Scene* MainScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = MainScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}


bool MainScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto keylistener = EventListenerKeyboard::create();
	keylistener->onKeyReleased = CC_CALLBACK_2(MainScene::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keylistener, this);
	//GameSharing::initGameSharing();

	Size s = this->getContentSize();



	m_img_BG = MenuItemImage::create("scene1-1/ani_bg.png", "scene1-1/ani_bg.png");
	m_img_BG->setPosition(Vec2(0, 0));
	m_img_BG->setAnchorPoint(Vec2(0, 0));
	m_img_BG->setOpacity(20);
	this->addChild(m_img_BG);



	ParticleSystemQuad *particle = ParticleSystemQuad::create("particle/particle4.plist");
	particle->setTexture(CCTextureCache::sharedTextureCache()->addImage("particle/particle_texture.png"));
	particle->setPosition(Vec2(this->getContentSize().width / 2, this->getContentSize().height / 2));
	this->addChild(particle);

	//Label* LBL_title = Label::create("password", "fonts/LCDM2L_.TTF", 85);
	//LBL_title->setPosition(Vec2(360, 990));
	//LBL_title->setTextColor(Color4B(25, 185, 35, 255));
	//LBL_title->enableGlow(Color4B(25, 185, 35, 120));
	//LBL_title->enableShadow(Color4B(25, 185, 35, 120), Size(3, 10), 10);
	//LBL_title->enableOutline(Color4B(255, 255, 255, 100), 1);
	//this->addChild(LBL_title);


	m_img_Logo = MenuItemImage::create("scene1-1/s1_title.png", "scene1-1/s1_title.png");
	m_img_Logo->setPosition(Vec2(360, 990));
	this->addChild(m_img_Logo);

	{
		auto img_set1 = MenuItemImage::create("scene1-1/s1_btn_set_up.png", "scene1-1/s1_btn_set_up.png");
		auto img_set2 = MenuItemImage::create("scene1-1/s1_btn_set_down.png", "scene1-1/s1_btn_set_down.png");

		MenuItemToggle* button = MenuItemToggle::createWithCallback(
			CC_CALLBACK_1(MainScene::Touch_setting, this), img_set1, img_set2, NULL);

		m_BTN_set = Menu::create(button, NULL);
		m_BTN_set->setPosition(Vec2(64, 1178));
		this->addChild(m_BTN_set);
	}

	{
		auto img_sound1 = MenuItemImage::create("scene1-1/s1_btn_sound.png", "scene1-1/s1_btn_sound.png");
		auto img_sound2 = MenuItemImage::create("scene1-1/s1_btn_sound_off.png", "scene1-1/s1_btn_sound_off.png");

		MenuItemToggle* button2 = MenuItemToggle::createWithCallback(
			CC_CALLBACK_1(MainScene::Touch_sound, this), img_sound1, img_sound2, NULL);

		m_BTN_sound = Menu::create(button2, NULL);
		m_BTN_sound->setPosition(Vec2(637, 1178));
		this->addChild(m_BTN_sound);
	}



	m_BTN_ranking = Button::create("scene1-1/s1_btn_ranking_up.png", "scene1-1/s1_btn_ranking_down.png");
	m_BTN_ranking->setPosition(Vec2(197, 835));
	m_BTN_ranking->addTouchEventListener(CC_CALLBACK_2(MainScene::Touch_ranking, this));
	this->addChild(m_BTN_ranking);

	m_BTN_replay = Button::create("scene1-1/s1_btn_replay_up.png", "scene1-1/s1_btn_replay_down.png");
	m_BTN_replay->setPosition(Vec2(512, 835));
	m_BTN_replay->addTouchEventListener(CC_CALLBACK_2(MainScene::Touch_replay, this));
	this->addChild(m_BTN_replay);

	m_BTN_base = Button::create("scene1-1/s1_btry_base_off.png", "scene1-1/s1_btry_base_off.png");
	m_BTN_base->setPosition(Vec2(543, 480));
	this->addChild(m_BTN_base);

	m_BTN_charge = Button::create("scene1-1/s1_btn_charge_1.png", "scene1-1/s1_btn_charge_2.png");
	m_BTN_charge->setPosition(Vec2(640.5, 480));
	this->addChild(m_BTN_charge);

	m_BTN_start = Button::create("scene1-1/s1_btn_start_up.png", "scene1-1/s1_btn_start_down.png");
	m_BTN_start->setPosition(Vec2(360, 352));
	m_BTN_start->addTouchEventListener(CC_CALLBACK_2(MainScene::Touch_start, this));
	this->addChild(m_BTN_start);

	m_BTN_charge_ad = Button::create("scene1-1/s1_btn_charge_ad.png", "scene1-1/s1_btn_charge_ad.png");
	m_BTN_charge_ad->setPosition(Vec2(360, 682));
	this->addChild(m_BTN_charge_ad);

	m_BTN_charge_ok = Button::create("scene1-1/s1_btn_charge_ok.png", "scene1-1/s1_btn_charge_ok.png");
	m_BTN_charge_ok->setPosition(Vec2(310.5, 1159));
	this->addChild(m_BTN_charge_ok);

	m_LBL_difficult = Label::create("Current stage", "fonts/LCDM2N_.TTF", 30);
	m_LBL_difficult->setPosition(Vec2(50, 470));
	m_LBL_difficult->setAnchorPoint(Vec2(0, 0));
	this->addChild(m_LBL_difficult);


	return true;
}



Scene* MainScene::scene()
{
	Scene *scene = Scene::create();
	MainScene *layer = MainScene::create();
	scene->addChild(layer);

	return scene;
}

void MainScene::changeScene(void)
{
	//Director::getInstance()->getEventDispatcher()->removeEventListenersForType(EventListener::Type::TOUCH_ONE_BY_ONE);

	auto hScene = SelectStageScene::createScene();
	auto pScene = TransitionFade::create(1.0f, hScene);
	Director::getInstance()->replaceScene(pScene);
}


void MainScene::Touch_sound(Ref* sender)
{

}
void MainScene::Touch_setting(Ref* sender)
{

}

void MainScene::Touch_ranking(Ref* sender, Widget::TouchEventType type)
{
	//터치 이벤트 실행시 프로그램 종료
	switch (type)
	{
	case Widget::TouchEventType::BEGAN:
		break;
	case Widget::TouchEventType::MOVED:
		break;
	case Widget::TouchEventType::ENDED:

		auto audio = SimpleAudioEngine::getInstance();
		audio->playEffect("raw/enter.wav", false, 1.0f, 1.0f, 1.0f);
		break;
	}

	GameSharing::ShowLeaderboards(0);
}
void MainScene::Touch_replay(Ref* sender, Widget::TouchEventType type)
{
	//터치 이벤트 실행시 프로그램 종료
	switch (type)
	{
	case Widget::TouchEventType::BEGAN:
		break;
	case Widget::TouchEventType::MOVED:
		break;
	case Widget::TouchEventType::ENDED:

		auto audio = SimpleAudioEngine::getInstance();
		audio->playEffect("raw/enter.wav", false, 1.0f, 1.0f, 1.0f);
		break;
	}
}

void MainScene::Touch_start(Ref* sender, Widget::TouchEventType type)
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
		auto audio = SimpleAudioEngine::getInstance();
		audio->playEffect("raw/enter.wav", false, 1.0f, 1.0f, 1.0f);
		changeScene();
		break;
	}
}



bool MainScene::onTouchBegan(Touch* touch, Event* event)
{
	auto target = event->getCurrentTarget();
	Point location = target->convertToNodeSpace(touch->getLocation());

	return true;
}

void MainScene::onKeyReleased(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event *event)
{
	if (keycode == EventKeyboard::KeyCode::KEY_BACK)
	{
		ShowPopup();
	}
	else if (keycode == EventKeyboard::KeyCode::KEY_ESCAPE)
	{
		ShowPopup();
	}

}

void MainScene::Callback_popup_ok(Ref* pSender)
{
	UIPopupWindow *pPopup = (UIPopupWindow *)pSender;
	int nTag = pPopup->getResult();

	if (nTag == 1)
	{
		pPopup->closePopup();
	}
	if (nTag == 2)
	{
		pPopup->closePopup();
	}
}


void MainScene::ShowPopup()
{
	//UIPopupWindow* pPopupOK = UIPopupWindow::create(NULL, Sprite::create("quit/pup_quit.png"));
	//pPopupOK->setBackgroundBorard(Sprite::create("common/bg_black_80.png"));
	//pPopupOK->setCallBackFunc(CC_CALLBACK_1(MainScene::Callback_popup_ok, this));
	//pPopupOK->addButton("quit/pup_quit_btn_ok.png", "quit/pup_quit_btn_ok.png", "", TextureResType::LOCAL, Point(-120, -51), "", 1);
	//pPopupOK->addButton("quit/pup_quit_btn_resume.png", "quit/pup_quit_btn_resume.png", "", TextureResType::LOCAL, Point(120, -51), "", 2);
	////pPopupOK->setMessageString("test_ popup");
	//pPopupOK->showPopup(this);
}