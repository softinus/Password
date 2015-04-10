#include "MainScene.h"

#include "GPGS/GameSharing.h"
#include "CustomUI/PopupWindow.h"


//#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
//#include "platform/android/jni/JniHelper.h"
//
//#ifdef __cplusplus
//extern "C" {
//#endif 
//	jint Java_com_softinus_pw_SignInActivate(JNIEnv* env, jobject obj)
//	{
//		m_BTN_signin->loadTextureNormal("scene1-1/s1_btn_login_active.png");
//
//		return 0;
//	}
//#ifdef __cplusplus
//}
//#endif
//#endif


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
	m_bPopupAlreadyOpened = false;

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
		//Size s = Director::sharedDirector()->getWinSize();

		Sprite *sprite_logo = Sprite::create("scene1-1/s1_title_2.png");
		sprite_logo->setPosition(Vec2(360, 990));

		//Texture2D * texture = TextureCache::sharedTextureCache()->addImage("scene1-1/sprite2_title.png");

		vector<SpriteFrame*> animFrames;
		for (int i = 0; i < 8; ++i)
		{
			auto frame = SpriteFrame::create("scene1-1/s1_title_2.png", Rect(0, 180 * i, 720, 180));
			animFrames.push_back(frame);
		}
		for (int i = 7; i > 0; --i)
		{
			auto frame = SpriteFrame::create("scene1-1/s1_title_2.png", Rect(0, 180 * i, 720, 180));
			animFrames.push_back(frame);
		}

		Animation * animation = Animation::create();
		animation->setDelayPerUnit(0.1f);
		for (size_t i = 0; i<animFrames.size(); ++i)
		{
			animation->addSpriteFrame(animFrames[i]);
		}


		sprite_logo->runAction(RepeatForever::create(Animate::create(animation)));
		this->addChild(sprite_logo);
	}


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
		m_BTN_sound->setVisible(false);
		this->addChild(m_BTN_sound);

	}




	m_BTN_signin = Button::create("scene1-1/s1_btn_login_up.png", "scene1-1/s1_btn_login_down.png");
	m_BTN_signin->setPosition(Vec2(645, 1167));
	m_BTN_signin->addTouchEventListener(CC_CALLBACK_2(MainScene::Touch_signin, this));
	this->addChild(m_BTN_signin);


	m_BTN_help = Button::create("scene1-1/s1_btn_help_up.png", "scene1-1/s1_btn_help_down.png");
	m_BTN_help->setPosition(Vec2(512, 760));
	m_BTN_help->addTouchEventListener(CC_CALLBACK_2(MainScene::Touch_help, this));
	this->addChild(m_BTN_help);


	m_BTN_achievement = Button::create("scene1-1/s1_btn_achievement_up.png", "scene1-1/s1_btn_achievement_down.png");
	m_BTN_achievement->setPosition(Vec2(197, 760)); 
	m_BTN_achievement->addTouchEventListener(CC_CALLBACK_2(MainScene::Touch_achievement, this));
	this->addChild(m_BTN_achievement);



	m_BTN_ranking = Button::create("scene1-1/s1_btn_ranking_up.png", "scene1-1/s1_btn_ranking_down.png");
	m_BTN_ranking->setPosition(Vec2(197, 835));
	m_BTN_ranking->addTouchEventListener(CC_CALLBACK_2(MainScene::Touch_ranking, this));
	this->addChild(m_BTN_ranking);

	m_BTN_credits = Button::create("scene1-1/s1_btn_credits_up.png", "scene1-1/s1_btn_credits_down.png");
	m_BTN_credits->setPosition(Vec2(512, 835));
	m_BTN_credits->addTouchEventListener(CC_CALLBACK_2(MainScene::Touch_credits, this));
	this->addChild(m_BTN_credits);


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

	auto hScene = SelectStageScene::createScene2();
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
		pPopupCredit->addButton("quit/pup_quit_btn_ok_up.png", "quit/pup_quit_btn_ok_down.png", "", TextureResType::LOCAL, Point(0, -235), "", 3);
		pPopupCredit->setCallBackFunc(CC_CALLBACK_1(MainScene::Callback_popup_exit_msg, this));
		//pPopupCredit->setMessageString("test");
		pPopupCredit->showPopup(this);

		m_bPopupAlreadyOpened = true;

		break;
	}
}

void MainScene::Touch_signin(Ref* sender, Widget::TouchEventType type)
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

		GameSharing::ShowSignForm();

		break;
	}
}

void MainScene::Touch_help(Ref* sender, Widget::TouchEventType type)
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

		ShowPopup1();

		break;
	}
}
void MainScene::Touch_achievement(Ref* sender, Widget::TouchEventType type)
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

		GameSharing::ShowAchievementsUI();

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
	if (m_bPopupAlreadyOpened)	// if already showing
		return;

	if (keycode == EventKeyboard::KeyCode::KEY_BACK)
	{
		ShowPopup_exit();
	}
	else if (keycode == EventKeyboard::KeyCode::KEY_ESCAPE)
	{
		ShowPopup_exit();
	}

}


void MainScene::Callback_popup_exit_msg(Ref* pSender)
{
	UIPopupWindow *pPopup = (UIPopupWindow *)pSender;
	int nTag = pPopup->getResult();


	if (nTag == 1)	// ok
	{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
		MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.", "Alert");
		return;
#endif
		Director::getInstance()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		exit(0);
#endif
	}
	if (nTag == 2)	// cancel
	{
		m_bPopupAlreadyOpened = false;
		pPopup->closePopup();
	}

	if (nTag == 3)	// credit-ok
	{
		m_bPopupAlreadyOpened = false;
		pPopup->closePopup();
	}
}


void MainScene::ShowPopup_exit()
{
	UIPopupWindow* pPopupOK = UIPopupWindow::create(Sprite::create("quit/pup_quit.png"));
	pPopupOK->setBackgroundBorard(Sprite::create("common/bg_black_80.png"));
	pPopupOK->setCallBackFunc(CC_CALLBACK_1(MainScene::Callback_popup_exit_msg, this));
	pPopupOK->addButton("quit/pup_quit_btn_ok_up.png", "quit/pup_quit_btn_ok_down.png", "", TextureResType::LOCAL, Point(-120, -51), "", 1);
	pPopupOK->addButton("quit/pup_quit_btn_resume_up.png", "quit/pup_quit_btn_resume_down.png", "", TextureResType::LOCAL, Point(120, -51), "", 2);
	//pPopupOK->setMessageString("test_ popup");
	pPopupOK->showPopup(this);

	m_bPopupAlreadyOpened = true;
}




void MainScene::Callback_popup_tutorial_msg(Ref* pSender)
{
	UIPopupWindow *pPopup = (UIPopupWindow *)pSender;
	int nTag = pPopup->getResult();

	if (nTag == 0)	// skip
	{
		UserDefault::getInstance()->setIntegerForKey("guide_already_showed", true);	// 
		pPopup->closePopup();
	}
	if (nTag == 1)	// p1-next
	{
		pPopup->closePopup();
		ShowPopup2();
	}
	if (nTag == 2)	// p1-prev
	{
	}

	if (nTag == 3)	// p2-next
	{
		pPopup->closePopup();
		ShowPopup3();
	}
	if (nTag == 4)	// p2-prev
	{
		pPopup->closePopup();
		ShowPopup1();
	}

	if (nTag == 5)	// p3-next
	{
		pPopup->closePopup();
		ShowPopup4();
	}
	if (nTag == 6)	// p3-prev
	{
		pPopup->closePopup();
		ShowPopup2();
	}

	if (nTag == 7)	// p4-next
	{
		pPopup->closePopup();
		ShowPopup5();
	}
	if (nTag == 8)	// p4-prev
	{
		pPopup->closePopup();
		ShowPopup3();
	}

	if (nTag == 9)	// p5-next
	{
		pPopup->closePopup();
		ShowPopup6();
	}
	if (nTag == 10)	// p5-prev
	{
		pPopup->closePopup();
		ShowPopup4();
	}

	if (nTag == 11)	// p6-next
	{
		UserDefault::getInstance()->setIntegerForKey("guide_already_showed", true);	// 
		pPopup->closePopup();
		//ShowPopup6();
	}
	if (nTag == 12)	// p6-prev
	{
		pPopup->closePopup();
		ShowPopup5();
	}

}



void MainScene::ShowPopup1()
{
	UIPopupWindow* pPopupOK = UIPopupWindow::create(NULL);
	pPopupOK->setBackgroundBorard(Sprite::create("help/help_1.png"));
	pPopupOK->setCallBackFunc(CC_CALLBACK_1(MainScene::Callback_popup_tutorial_msg, this));
	pPopupOK->addButton("help/text_box1.png", "help/text_box1.png", "", TextureResType::LOCAL, Point(310, 1031), "", -1);
	pPopupOK->addButton("help/h1_btn_next_up.png", "help/h1_btn_next_up.png", "", TextureResType::LOCAL, Point(616.5, 217.5), "", 1);
	pPopupOK->addButton("help/h1_btn_skip_up.png", "help/h1_btn_skip_up.png", "", TextureResType::LOCAL, Point(633, 1231), "", 0);
	pPopupOK->showPopup(this);
}

void MainScene::ShowPopup2()
{
	UIPopupWindow* pPopupOK = UIPopupWindow::create(NULL);
	pPopupOK->setBackgroundBorard(Sprite::create("help/help_2.png"));
	pPopupOK->setCallBackFunc(CC_CALLBACK_1(MainScene::Callback_popup_tutorial_msg, this));
	pPopupOK->addButton("help/text_box2.png", "help/text_box2.png", "", TextureResType::LOCAL, Point(351.5, 903.5), "", -1);
	pPopupOK->addButton("help/h1_btn_prev_up.png", "help/h1_btn_prev_up.png", "", TextureResType::LOCAL, Point(119.5, 217.5), "", 4);
	pPopupOK->addButton("help/h1_btn_next_up.png", "help/h1_btn_next_up.png", "", TextureResType::LOCAL, Point(616.5, 217.5), "", 3);
	pPopupOK->addButton("help/h1_btn_skip_up.png", "help/h1_btn_skip_up.png", "", TextureResType::LOCAL, Point(633, 1231), "", 0);
	pPopupOK->showPopup(this);
}






void MainScene::ShowPopup3()
{
	UIPopupWindow* pPopupOK = UIPopupWindow::create(NULL);
	pPopupOK->setBackgroundBorard(Sprite::create("help/help_3.png"));
	pPopupOK->setCallBackFunc(CC_CALLBACK_1(MainScene::Callback_popup_tutorial_msg, this));
	pPopupOK->addButton("help/text_box3.png", "help/text_box3.png", "", TextureResType::LOCAL, Point(351.5, 903.5), "", -1);
	pPopupOK->addButton("help/h1_btn_prev_up.png", "help/h1_btn_prev_up.png", "", TextureResType::LOCAL, Point(119.5, 217.5), "", 6);
	pPopupOK->addButton("help/h1_btn_next_up.png", "help/h1_btn_next_up.png", "", TextureResType::LOCAL, Point(616.5, 217.5), "", 5);
	pPopupOK->addButton("help/h1_btn_skip_up.png", "help/h1_btn_skip_up.png", "", TextureResType::LOCAL, Point(633, 1231), "", 0);
	pPopupOK->showPopup(this);
}


void MainScene::ShowPopup4()
{
	UIPopupWindow* pPopupOK = UIPopupWindow::create(NULL);
	pPopupOK->setBackgroundBorard(Sprite::create("help/help_4.png"));
	pPopupOK->setCallBackFunc(CC_CALLBACK_1(MainScene::Callback_popup_tutorial_msg, this));
	pPopupOK->addButton("help/text_box4.png", "help/text_box4.png", "", TextureResType::LOCAL, Point(428, 923), "", -1);
	pPopupOK->addButton("help/h1_btn_prev_up.png", "help/h1_btn_prev_up.png", "", TextureResType::LOCAL, Point(119.5, 217.5), "", 8);
	pPopupOK->addButton("help/h1_btn_next_up.png", "help/h1_btn_next_up.png", "", TextureResType::LOCAL, Point(616.5, 217.5), "", 7);
	pPopupOK->addButton("help/h1_btn_skip_up.png", "help/h1_btn_skip_up.png", "", TextureResType::LOCAL, Point(633, 1231), "", 0);
	pPopupOK->showPopup(this);
}

void MainScene::ShowPopup5()
{
	UIPopupWindow* pPopupOK = UIPopupWindow::create(NULL);
	pPopupOK->setBackgroundBorard(Sprite::create("help/help_5.png"));
	pPopupOK->setCallBackFunc(CC_CALLBACK_1(MainScene::Callback_popup_tutorial_msg, this));
	pPopupOK->addButton("help/text_box5.png", "help/text_box5.png", "", TextureResType::LOCAL, Point(350, 1132), "", -1);
	pPopupOK->addButton("help/h1_btn_prev_up.png", "help/h1_btn_prev_up.png", "", TextureResType::LOCAL, Point(119.5, 217.5), "", 10);
	pPopupOK->addButton("help/h1_btn_next_up.png", "help/h1_btn_next_up.png", "", TextureResType::LOCAL, Point(616.5, 217.5), "", 9);
	pPopupOK->addButton("help/h1_btn_skip_up.png", "help/h1_btn_skip_up.png", "", TextureResType::LOCAL, Point(633, 1231), "", 0);
	pPopupOK->showPopup(this);
}

void MainScene::ShowPopup6()
{
	UIPopupWindow* pPopupOK = UIPopupWindow::create(NULL);
	pPopupOK->setBackgroundBorard(Sprite::create("help/help_6.png"));
	pPopupOK->setCallBackFunc(CC_CALLBACK_1(MainScene::Callback_popup_tutorial_msg, this));
	pPopupOK->addButton("help/text_box6.png", "help/text_box6.png", "", TextureResType::LOCAL, Point(357, 638), "", -1);
	pPopupOK->addButton("help/h1_btn_prev_up.png", "help/h1_btn_prev_up.png", "", TextureResType::LOCAL, Point(119.5, 217.5), "", 12);
	pPopupOK->addButton("help/h1_btn_next_up.png", "help/h1_btn_next_up.png", "", TextureResType::LOCAL, Point(616.5, 217.5), "", 11);
	pPopupOK->addButton("help/h1_btn_skip_up.png", "help/h1_btn_skip_up.png", "", TextureResType::LOCAL, Point(633, 1231), "", 0);
	pPopupOK->showPopup(this);
}


