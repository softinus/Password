#include "ResultScene.h"
#include "GPGS\GameSharing.h"



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

	GameSharing::EarnCoins(30, "full-ad");
	GameSharing::ShowFullAd();

	if (DataSingleton::getInstance().nPlayMode == EStage::CHALLENGE)
	{
		this->ShowCountInChallengeMode();
	}
	else
	{
		this->ShowRankInEasyNormalMode();
	}
	


	m_BTN_main = Button::create("scene5-1/btn_main_up.png", "scene5-1/btn_main_down.png");
	m_BTN_main->setPosition(Vec2(443.5, 396.5));
	m_BTN_main->setAnchorPoint(Vec2(0, 0));
	m_BTN_main->setVisible(false);
	this->addChild(m_BTN_main);

	m_BTN_next = Button::create("scene5-1/btn_main_up.png", "scene5-1/btn_main_down.png");
	m_BTN_next->setPosition(Vec2(43.5, 396.5));
	m_BTN_next->setAnchorPoint(Vec2(0, 0));
	m_BTN_next->setVisible(false);
	this->addChild(m_BTN_next);

	


	this->schedule(schedule_selector(ResultScene::scheduleCallback), 3.f);

	{
		MoveTo *action_0 = MoveTo::create(2.0f, Point(260, 1144));
		EaseElasticInOut *action_1 = EaseElasticInOut::create(action_0);    // action, 탄성
		m_IMG_result->runAction(action_1);
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

	auto hScene = SelectStageScene::createScene2();
	auto pScene = TransitionFade::create(1.0f, hScene);
	//auto pScene = TransitionFlipAngular::create(1.0f, hScene);
	Director::getInstance()->replaceScene(pScene);
	//Director::getInstance()->popScene();
}

bool ResultScene::onTouchBegan(Touch* touch, Event* event) {
	auto target = event->getCurrentTarget();
	Point location = target->convertToNodeSpace(touch->getLocation());

	changeScene();
	return true;
}

// when challenge mode
void ResultScene::ShowCountInChallengeMode()
{
	int nTotalCount = DataSingleton::getInstance().nStageRepeatCount;
	 
	m_IMG_result = MenuItemImage::create("scene5-1/s5_result.png", "scene5-1/s5_result.png");
	m_IMG_result->setPosition(Vec2(-260, 1144));
	this->addChild(m_IMG_result);

	int nCurrLevel = DataSingleton::getInstance().nLevel;

	string strChallenge = "rank_challenge_";
	strChallenge += to_string2(nCurrLevel);
	UserDefault::getInstance()->setIntegerForKey(strChallenge.c_str(), nTotalCount);

	string strCount = "Record : " + to_string2(nTotalCount);
	m_LBL_count = Label::createWithTTF(strCount, "fonts/LCDM2N_.TTF", 60.f);
	m_LBL_count->setPosition(Vec2(750, 740));
	m_LBL_count->setAnchorPoint(Vec2(0, 0));
	this->addChild(m_LBL_count);


	{
		DelayTime *delay = DelayTime::create(0.4f);    // 시간
		MoveTo *action_0 = MoveTo::create(2.0f, Vec2(290, 740));
		EaseElasticInOut *action_1 = EaseElasticInOut::create(action_0);    // action, 탄성
		Sequence *seq = Sequence::create(delay, action_1, NULL);
		m_LBL_count->runAction(seq);
	}

	UpdateAchievementOfChallengeMode();

}


// when easy or normal mode
void ResultScene::ShowRankInEasyNormalMode()
{
	// A,B,D 랭크 기준 [3/6/2015 ChoiJunHyeok]
	if (DataSingleton::getInstance().nLevel == 1)
	{
		m_nCriterionOfDrank = 1;	// 1단계 실패시
		m_nCriterionOfBrank = 2;	// 남은 라이프 2이하
		m_nCriterionOfArank = 4;	// 남은 라이프 4이하
		// 나머지 S랭크
	}
	else
	{
		m_nCriterionOfDrank = 3;	// 3단계 실패시
		m_nCriterionOfBrank = 1;	// 남은 라이프 1이하
		m_nCriterionOfArank = 3;	// 남은 라이프 3이하
		// 나머지 S랭크
	}


	int nTotalCount = DataSingleton::getInstance().nSpentCount;
	//	int nTotalTime = DataSingleton::getInstance().nSpentTime;


	m_IMG_result = MenuItemImage::create("scene5-1/s5_result.png", "scene5-1/s5_result.png");
	m_IMG_result->setPosition(Vec2(-260, 1144));
	this->addChild(m_IMG_result);


	string str_rank = "rank_";
	if (DataSingleton::getInstance().nPlayMode == EStage::EASY)
		str_rank += "easy_";
	else if (DataSingleton::getInstance().nPlayMode == EStage::NORMAL)
		str_rank += "normal_";

	str_rank += to_string2(DataSingleton::getInstance().nLevel);
	int nSavedRank = UserDefault::getInstance()->getIntegerForKey(str_rank.c_str(), 0);
	bool bNewRanked = false;

	string strRankImagePath = "";
	if (DataSingleton::getInstance().bClear)	// 클리어 했으면 S, A,B 중 하나
	{
		if (DataSingleton::getInstance().nLeftLife < m_nCriterionOfBrank)
		{
			strRankImagePath = "scene5-1/s5_rank_b.png";
			if (nSavedRank < 2)	// 현재 랭크가 b랭크보다 낮으면
			{
				UserDefault::getInstance()->setIntegerForKey(str_rank.c_str(), 2);
				bNewRanked = true;
			}

		}
		else if (DataSingleton::getInstance().nLeftLife < m_nCriterionOfArank)
		{
			strRankImagePath = "scene5-1/s5_rank_a.png";
			if (nSavedRank < 3)	// 현재 랭크가 a랭크보다 낮으면
			{
				UserDefault::getInstance()->setIntegerForKey(str_rank.c_str(), 3);
				bNewRanked = true;
			}

		}
		else
		{
			strRankImagePath = "scene5-1/s5_rank_s.png";
			if (nSavedRank != 4)	// 현재 랭크가 s랭크가 아니면
			{
				UserDefault::getInstance()->setIntegerForKey(str_rank.c_str(), 4);
				bNewRanked = true;
			}

		}
	}
	else
	{
		if (m_nCriterionOfDrank > DataSingleton::getInstance().nStageRepeatCount)	// criterion of D rank
		{
			strRankImagePath = "scene5-1/s5_rank_d.png";
			if (nSavedRank == -1)	// 현재 랭크가 없으면
			{
				UserDefault::getInstance()->setIntegerForKey(str_rank.c_str(), 0);
				bNewRanked = true;
			}

		}
		else
		{
			strRankImagePath = "scene5-1/s5_rank_c.png";
			if (nSavedRank < 1)	// 현재 랭크가 c랭크보다 낮으면
			{
				UserDefault::getInstance()->setIntegerForKey(str_rank.c_str(), 1);
				bNewRanked = true;
			}

		}

	}
	DataSingleton::getInstance().nCleardStage = DataSingleton::getInstance().nLevel;
	DataSingleton::getInstance().bNewRanked = bNewRanked;


	m_IMG_rank = MenuItemImage::create(strRankImagePath, strRankImagePath);
	m_IMG_rank->setPosition(Vec2(1150, 891.5));
	this->addChild(m_IMG_rank);


	string strCount = "count : " + to_string2(nTotalCount);
	m_LBL_count = Label::createWithTTF(strCount, "fonts/LCDM2N_.TTF", 45.f);
	m_LBL_count->setPosition(Vec2(750, 740));
	m_LBL_count->setAnchorPoint(Vec2(0, 0));
	this->addChild(m_LBL_count);

	string strTime = "time : " + to_string2(DataSingleton::getInstance().nSpentTime);
	m_LBL_time = Label::createWithTTF(strTime, "fonts/LCDM2N_.TTF", 45.f);
	m_LBL_time->setPosition(Vec2(750, 690));
	m_LBL_time->setAnchorPoint(Vec2(0, 0));
	this->addChild(m_LBL_time);

	{
		DelayTime *delay = DelayTime::create(0.2f);    // 시간
		MoveTo *action_0 = MoveTo::create(2.0f, Vec2(495, 891.5));
		EaseElasticInOut *action_1 = EaseElasticInOut::create(action_0);    // action, 탄성
		Sequence *seq = Sequence::create(delay, action_1, NULL);
		m_IMG_rank->runAction(action_1);
	}

	{
		DelayTime *delay = DelayTime::create(0.4f);    // 시간
		MoveTo *action_0 = MoveTo::create(2.0f, Vec2(290, 740));
		EaseElasticInOut *action_1 = EaseElasticInOut::create(action_0);    // action, 탄성
		Sequence *seq = Sequence::create(delay, action_1, NULL);
		m_LBL_count->runAction(seq);
	}

	{
		DelayTime *delay = DelayTime::create(0.6f);    // 시간
		MoveTo *action_2 = MoveTo::create(2.0f, Vec2(290, 690));
		EaseElasticInOut *action_3 = EaseElasticInOut::create(action_2);    // action, 탄성
		Sequence *seq = Sequence::create(delay, action_3, NULL);

		m_LBL_time->runAction(seq);
	}
}

void ResultScene::UpdateAchievementOfChallengeMode()
{

	int nChallengeSum = 0;
	for (size_t i = 1; i < 10; i++)
	{
		string strChallenge = "rank_challenge_";
		strChallenge += to_string2(i);
		int nSingleScore = UserDefault::getInstance()->getIntegerForKey(strChallenge.c_str(), 0);

		nChallengeSum += nSingleScore * pow(2, (i - 1));

	}


	//int nScore= UserDefault::getInstance()->getIntegerForKey("leaderboard_challenge_score", 0);	// load existing score
	int nNewScore = nChallengeSum;

	GameSharing::SubmitScore(nNewScore, 0);

	if (nNewScore >= 50)
	{
		GameSharing::UnlockAchivement(EAchievement::BEGINNER_CHALLENGER);
	}
	else if (nNewScore >= 100)
	{
		GameSharing::UnlockAchivement(EAchievement::EXPERT_CHALLENGER);
	}
	else if (nNewScore >= 300)
	{
		GameSharing::UnlockAchivement(EAchievement::MASTER_CHALLENGER);
	}
	else if (nNewScore >= 1000)
	{
		GameSharing::UnlockAchivement(EAchievement::THE_KING_OF_PW);
	}

	UserDefault::getInstance()->setIntegerForKey("leaderboard_challenge_score", nNewScore);

	//string str = "old score: " + to_string2(nScore) + "\nnew score: " + to_string2(nNewScore);
	//MessageBox(str.c_str(), "test");
}
