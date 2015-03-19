#include "MainScene.h"

#include "GPGS/GameSharing.h"
#include "CustomUI/PopupWindow.h"

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

	DataSingleton::getInstance().nPlayMode = 0;

	m_IMG_ani_BG = MenuItemImage::create("scene1-1/ani_bg.png", "scene1-1/ani_bg.png");
	m_IMG_ani_BG->setPosition(Vec2(0, 0));
	m_IMG_ani_BG->setAnchorPoint(Vec2(0, 0));
	m_IMG_ani_BG->setOpacity(76.5);
	this->addChild(m_IMG_ani_BG);

	{
		auto m_img_eff = MenuItemImage::create("scene1-1/s1_effct_blackg.png", "scene1-1/s1_effct_blackg.png");
		m_img_eff->setPosition(Vec2(0, s.height*0.66));
		m_img_eff->setAnchorPoint(Vec2(0, 0));
		this->addChild(m_img_eff);

		auto move1 = MoveTo::create(1.0f, Vec2(0, -s.height));
		auto move2 = MoveTo::create(0.0f, Vec2(0, s.height*0.6));
		auto delay = DelayTime::create(2.0f);
		auto seq = Sequence::create(move1, delay, move2, NULL);
		RepeatForever *action_3 = RepeatForever::create(seq);
		m_img_eff->runAction(action_3);
	};// 연출1

	{
		auto m_img_eff = MenuItemImage::create("scene1-1/s1_effct_blackg.png", "scene1-1/s1_effct_blackg.png");
		m_img_eff->setPosition(Vec2(0, s.height*0.9));
		m_img_eff->setAnchorPoint(Vec2(0, 0));
		this->addChild(m_img_eff);

		auto move1 = MoveTo::create(2.0f, Vec2(0, -s.height));
		auto move2 = MoveTo::create(0.0f, Vec2(0, s.height*0.9));
		auto delay = DelayTime::create(1.0f);
		auto seq = Sequence::create(move1, delay, move2, NULL);
		RepeatForever *action_3 = RepeatForever::create(seq);
		m_img_eff->runAction(action_3);
	};// 연출2

	{
		auto m_img_eff = MenuItemImage::create("scene1-1/s1_effct_blackg.png", "scene1-1/s1_effct_blackg.png");
		m_img_eff->setPosition(Vec2(0, s.height*1.2));
		m_img_eff->setAnchorPoint(Vec2(0, 0));
		this->addChild(m_img_eff);

		auto move1 = MoveTo::create(2.0f, Vec2(0, -s.height));
		auto move2 = MoveTo::create(0.0f, Vec2(0, s.height*1.2));
		auto delay = DelayTime::create(1.0f);
		auto seq = Sequence::create(move1, delay, move2, NULL);
		RepeatForever *action_3 = RepeatForever::create(seq);
		m_img_eff->runAction(action_3);
	};// 연출3



	
	
	//SpriteFrameCache::getInstance()->addSpriteFramesWithFile("sprites/logo_eff.plist");

	

	{	// 배경연출
		Size s = Director::sharedDirector()->getWinSize();

		Sprite *sprite = Sprite::create("scene1-1/sprite2_title.png");
		sprite->setPosition(Vec2(360, 990));

		Texture2D * texture = TextureCache::sharedTextureCache()->addImage("scene1-1/sprite2_title.png");

		vector<SpriteFrame*> animFrames;
		for (int i = 0; i < 8; ++i)
		{
			auto frame = SpriteFrame::create("scene1-1/sprite2_title.png", Rect(0, 180 * i, 720, 180));
			animFrames.push_back(frame);
		}
		for (int i = 7; i > 0; --i)
		{
			auto frame = SpriteFrame::create("scene1-1/sprite2_title.png", Rect(0, 180 * i, 720, 180));
			animFrames.push_back(frame);
		}

		Animation * animation = Animation::create();
		animation->setDelayPerUnit(0.1f);
		for (size_t i = 0; i<animFrames.size(); ++i)
		{
			animation->addSpriteFrame(animFrames[i]);
		}


		sprite->runAction(RepeatForever::create(Animate::create(animation)));
		this->addChild(sprite);
	}

	//m_img_Logo = MenuItemImage::create("scene1-1/s1_title.png", "scene1-1/s1_title.png");
	//m_img_Logo->setPosition(Vec2(360, 990));
	//this->addChild(m_img_Logo);


	//ParticleSystemQuad *particle = ParticleSystemQuad::create("particle/particle4.plist");
	//particle->setTexture(CCTextureCache::sharedTextureCache()->addImage("particle/particle_texture.png"));
	//particle->setPosition(Vec2(this->getContentSize().width / 2, this->getContentSize().height / 2));
	//this->addChild(particle);

	//Label* LBL_title = Label::create("password", "fonts/LCDM2L_.TTF", 85);
	//LBL_title->setPosition(Vec2(360, 990));
	//LBL_title->setTextColor(Color4B(25, 185, 35, 255));
	//LBL_title->enableGlow(Color4B(25, 185, 35, 120));
	//LBL_title->enableShadow(Color4B(25, 185, 35, 120), Size(3, 10), 10);
	//LBL_title->enableOutline(Color4B(255, 255, 255, 100), 1);
	//this->addChild(LBL_title);



	{
		auto img_set1 = MenuItemImage::create("scene1-1/s1_btn_set_up.png", "scene1-1/s1_btn_set_up.png");
		auto img_set2 = MenuItemImage::create("scene1-1/s1_btn_set_down.png", "scene1-1/s1_btn_set_down.png");

		MenuItemToggle* button = MenuItemToggle::createWithCallback(
			CC_CALLBACK_1(MainScene::Touch_setting, this), img_set1, img_set2, NULL);

		m_BTN_set = Menu::create(button, NULL);
		m_BTN_set->setPosition(Vec2(64, 1178));
		m_BTN_set->setVisible(false);
		this->addChild(m_BTN_set);
	}


	{

		m_BTN_sound = Button::create("scene1-1/s1_btn_sound.png", "scene1-1/s1_btn_sound.png");
		m_BTN_sound->setPosition(Vec2(637, 1178));
		m_BTN_sound->addTouchEventListener(CC_CALLBACK_2(MainScene::Touch_sound, this));
		this->addChild(m_BTN_sound);

	}



	m_BTN_ranking = Button::create("scene1-1/s1_btn_ranking_up.png", "scene1-1/s1_btn_ranking_down.png");
	m_BTN_ranking->setPosition(Vec2(197, 835));
	m_BTN_ranking->addTouchEventListener(CC_CALLBACK_2(MainScene::Touch_ranking, this));
	this->addChild(m_BTN_ranking);

	m_BTN_credits = Button::create("scene1-1/s1_btn_credits_up.png", "scene1-1/s1_btn_credits_down.png");
	m_BTN_credits->setPosition(Vec2(512, 835));
	m_BTN_credits->addTouchEventListener(CC_CALLBACK_2(MainScene::Touch_credits, this));
	this->addChild(m_BTN_credits);

	//m_BTN_replay = Button::create("scene1-1/s1_btn_replay_up.png", "scene1-1/s1_btn_replay_down.png");
	//m_BTN_replay->setPosition(Vec2(512, 835));
	//m_BTN_replay->addTouchEventListener(CC_CALLBACK_2(MainScene::Touch_replay, this));
	//this->addChild(m_BTN_replay);

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


	//m_IMG_popup_BG = Sprite::create("common/bg_black_80.png");
	//m_IMG_popup_BG->setPosition(Vec2(s.width / 2, s.height / 2));
	////m_IMG_BG->setOpacity(76.5);
	//m_IMG_popup_BG->setVisible(false);
	//
	////m_img_BG->setAnchorPoint(Vec2(0, 0));
	//this->addChild(m_IMG_popup_BG);

	//m_IMG_popup_credits = Sprite::create("scene1-1/s1_pup_credits.png");
	//m_IMG_popup_credits->setPosition(Vec2(s.width / 2, s.height / 2));
	//m_IMG_popup_credits->setVisible(false);
	//m_img_BG->setAnchorPoint(Vec2(0, 0));
	//this->addChild(m_IMG_popup_credits);

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


void MainScene::Touch_sound(Ref* sender, Widget::TouchEventType type)
{
	switch (type)
	{
	case Widget::TouchEventType::BEGAN:
		break;
	case Widget::TouchEventType::MOVED:
		break;
	case Widget::TouchEventType::ENDED:

		GameSharing::ShowSignForm();
		//GameSharing::ConnectToParse();
		//MessageBox("send!", "to Parse");

		break;
	}
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
		audio->playEffect("raw/number.wav", false, 1.0f, 1.0f, 1.0f);


		GameSharing::ShowLeaderboards(0);

		break;
	
	}


}
void MainScene::Touch_credits(Ref* sender, Widget::TouchEventType type)
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
		audio->playEffect("raw/number.wav", false, 1.0f, 1.0f, 1.0f);

		UIPopupWindow* pPopupCredit = UIPopupWindow::create(Sprite::create("scene1-1/s1_pup_credits.png"));
		pPopupCredit->setBackgroundBorard(Sprite::create("common/bg_black_80.png"));
		//pPopupCredit->setCallBackFunc(CC_CALLBACK_1(MainScene::ShowPopup));
		pPopupCredit->setMessageString("test");
		pPopupCredit->showPopup(this);

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
		audio->playEffect("raw/number.wav", false, 1.0f, 1.0f, 1.0f);
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