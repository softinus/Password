#include "PopupWindow.h"

UIPopupWindow * UIPopupWindow::create(Sprite  *sprBackgroundImg)
{
	UIPopupWindow *pRet = new UIPopupWindow();
	if (pRet && pRet->init())
	{
		pRet->setBackgroundBorard(nullptr);
		pRet->setBackgroundImage(sprBackgroundImg);
		pRet->setTextInit(); //����� ���� UI�ʱ�ȭ

		pRet->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(pRet);

	}
	return pRet;
}

bool UIPopupWindow::onInit()
{
	m_nZorderCnt = 1;//�߰��� �ڽİ�ü�鿡 ���� Zorder�� ���������
	m_sprBg = NULL;




	//// setup content
	//Sprite* pSprite = Sprite::create("common/Button_Normal.png");
	//pSprite->setPosition(ccp(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	//clip->addChild(pSprite);

	//this->addChild(shape);

	return true;
}

void UIPopupWindow::addPlist(const std::string& filename)
{
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(filename);
}


void UIPopupWindow::onBtnCallback(Ref *pSender, ui::Button::TouchEventType touchType)
{
	// �����߰��Ǵ� ��ư�� ���� �̺�Ʈ�ڵ鷯 �Լ�����...
	if (touchType == ui::Widget::TouchEventType::ENDED)
	{
		//SimpleAudioEngine::getInstance()->playEffect( DF_SOUND_UI_01); //�̺κ��� ��ưŬ���� ����Ʈ ���� �������ؼ�	
		m_nResult = ((Node*)pSender)->getTag();    //� ��ư���� üũ�� ���� ��ư�� �߰��� Tag�� �ɹ��������� �������ֵ��� �Ѵ�.
		onCallBackFunc();   //���� BaseŬ������ �˾� �ݹ��Լ��� ȣ���Ѵ�.
	}
}

void UIPopupWindow::onSldCallback(Ref *pSender, ui::Slider::EventType touchType)
{
	if(touchType == ui::Slider::EventType::ON_PERCENTAGE_CHANGED)
	{
		m_nResult = ((Node*)pSender)->getTag();    //� ��ư���� üũ�� ���� ��ư�� �߰��� Tag�� �ɹ��������� �������ֵ��� �Ѵ�.
		onCallBackFunc();   //���� BaseŬ������ �˾� �ݹ��Լ��� ȣ���Ѵ�.
	}
}

void UIPopupWindow::setBackgroundBorard(Sprite  *sprBg)//�˾� �Ʒ��� �����̳� �� �̷���? �Ͽ��� �� �عٴ�
{
	if (!sprBg)return;

	Size size = Director::getInstance()->getWinSize();
	sprBg->setPosition(size.width / 2, size.height / 2);
	//addChild(sprBg, -10);


	{	// TODO: ���ٽ� ��� ���� �Լ� ���� ���������. [3/20/2015 ChoiJunHyeok]
		DrawNode* shape = DrawNode::create();
		Size sRectSize = Size(680, 680);
		Vec2 vStartPoint = Vec2(20, 250);
		shape->drawSolidRect(vStartPoint, vStartPoint + sRectSize, Color4F(1, 1, 1, 1));

		auto sptest = Sprite::create("scene4/s4_pup_success.png");
		sptest->setPosition(Point(100, 100));
		sptest->setZOrder(105);

		auto clipping = ClippingNode::create();
		//auto clippingShape = Sprite::create("scene4/box_life.png");
		clipping->setStencil(shape);
		clipping->setContentSize(sprBg->getContentSize());
		clipping->setInverted(true);
		clipping->setAlphaThreshold(0.0f);
		clipping->addChild(sprBg);
		this->addChild(clipping, 105);
	}

}


void UIPopupWindow::setBackgroundImage(Sprite  *sprBg)
{
	if (m_sprBg)
	{
#if COCOS2D_DEBUG > 0
		char msg[256] = { 0 };
		sprintf(msg, "Already BackgroundImage");
		CCASSERT(m_sprBg == NULL, msg);
#endif
		return;
	}

	m_sprBg = sprBg;
	if (!m_sprBg)return;


	try
	{
		Size size = Director::getInstance()->getWinSize();
		m_sprBg->setPosition(size.width / 2, size.height / 2);
		addChild(m_sprBg, -1);
	}
	catch (...)
	{
	}

}

void UIPopupWindow::setBackgroundImagePosition(const Point& position)
{
	if (!m_sprBg)return;
	m_sprBg->setPosition(position);
}

void UIPopupWindow::setTextInit() //����� ���� UI�ʱ�ȭ
{
	Size size = Director::getInstance()->getWinSize();

	m_txtTitle = Text::create();    //Ÿ��Ʋ
	//m_txtTitle->setFontName(GET_TTF_FONTNAME()); //�ٱ��� ������ ���� TTF��Ʈ ����
	m_txtTitle->setString("");
	m_txtTitle->setFontSize(20);
	m_txtTitle->setColor(Color3B(0, 0, 0));


	if (m_sprBg)
	{
		Rect rct = m_sprBg->getTextureRect();
		m_txtTitle->setPosition(Point(size.width / 2, (size.height / 2 + rct.size.height / 2) - 40));
	}

	m_txt = Text::create();
	m_txt->setString("");

	//m_txt->setFontName(GET_TTF_FONTNAME());//�ٱ��� ������ ���� TTF��Ʈ ����
	m_txt->setFontSize(20);
	m_txt->setColor(Color3B(255, 255, 255));
	m_txt->setPosition(Point(size.width / 2, (size.height / 2) + 20));

	addChild(m_txtTitle, (int)m_nZorderCnt + 100);
	addChild(m_txt, (int)m_nZorderCnt + 100);

}

void UIPopupWindow :: addGuideRect(Vec2 vStartPoint, Size sRectSize)
{
	DrawNode* shape = DrawNode::create();

	shape->drawRect(vStartPoint, vStartPoint + sRectSize, Color4F(0.9f, 0.0f, 0.0f, 0.8f));

	this->addChild(shape);
}

void UIPopupWindow::addText(const std::string& text, const std::string& font, const Vec2& pos, int size, const Color3B& color)
{
	//Text* textMsg = Text::create(); 
	Label* textMsg = Label::createWithTTF(text, font, size);
	this->addChild(textMsg, (int)m_nZorderCnt);
	m_nZorderCnt++;

	if (m_sprBg)
	{
		textMsg->setAnchorPoint(Vec2(0, 0.5));
		textMsg->setPosition(m_sprBg->getPosition() + pos);
	}
	else
	{
		textMsg->setPosition(pos);
	}
	textMsg->setTextColor(Color4B(color.r, color.g, color.b, 255));
}

void UIPopupWindow::addSlideButton(const std::string& track, const std::string& progress, const std::string& normal, const std::string& pressed, const std::string& disable, Widget::TextureResType texType, const float percentage, const Point &pos, const int nTag)
{
	Slider *pSlider = Slider::create();
	this->addChild(pSlider, (int)m_nZorderCnt);
	m_nZorderCnt++;

	pSlider->setTouchEnabled(true);
	pSlider->loadBarTexture(track, texType);
	pSlider->loadProgressBarTexture(progress, texType);
	pSlider->loadSlidBallTextures(normal, pressed, disable, texType);

	if (m_sprBg)
	{
		pSlider->setAnchorPoint(Vec2(1, 0.5));
		pSlider->setPosition(m_sprBg->getPosition() + pos);
	}
	else
	{
		pSlider->setPosition(pos);
	}

	pSlider->setPercent(percentage);
	pSlider->setTag(nTag);
	pSlider->addEventListener(CC_CALLBACK_2(UIPopupWindow::onSldCallback, this));

}

void UIPopupWindow::addButton(const char* normalTexture, const char* selectedTexture, const char* disabledTexture, Widget::TextureResType texType, const Point &pos, const std::string& text, const int nTag)
{

	//�˾�â�� ��ư�� �����Ѵ�.

	cocos2d::ui::Button *pBtn = cocos2d::ui::Button::create();
	pBtn->setTouchEnabled(true);
	pBtn->loadTextures(normalTexture, selectedTexture, disabledTexture, texType);
	pBtn->setTitleText(text);
	if (m_sprBg)
	{
		//Vec2 parents = m_sprBg->getPosition();
		//Vec2 worlspace = Vec2(pos.x * m_sprBg->getAnchorPoint().x, pos.y * m_sprBg->getAnchorPoint().y);
		//Vec2 position = pos;

		//position += worlspace;
		pBtn->setAnchorPoint(Vec2(0.5, 0.5));
		pBtn->setPosition(m_sprBg->getPosition()+pos);
	}
	else
	{
		pBtn->setPosition(pos);
	}

	pBtn->setTag(nTag);
	// pBtn->addTouchEventListener(this,toucheventselector(UIPopupWindow::onBtnClickCallbackFnc) ); //�̺κ��� 3.0���� ��������ʵ��� ����ȴ�.
	pBtn->addTouchEventListener(CC_CALLBACK_2(UIPopupWindow::onBtnCallback, this)); //��ư�� Ŭ���� �ݹ��Լ� ����

	addChild(pBtn, (int)m_nZorderCnt);
	m_nZorderCnt++;
}


void  UIPopupWindow::setTitleString(const std::string& text)
{
	m_txtTitle->setString(text);
}
void  UIPopupWindow::setMessageString(const std::string& text)
{
	m_txt->setString(text);
}

void UIPopupWindow::setFontSize_Title(int size)   //Ÿ��Ʋ ��Ʈ ����� �����Ѵ�.
{
	m_txtTitle->setFontSize(size);
}
void UIPopupWindow::setColor_Title(const Color3B& color)  //Ÿ��Ʋ ��Ʈ ���� ����
{
	m_txtTitle->setColor(color);

}
void UIPopupWindow::setPosition_Title(const Point& position)
{
	if (m_sprBg)
	{
		Vec2 parents = m_sprBg->getPosition();
		parents.scale(m_sprBg->getAnchorPoint());
		m_txtTitle->setPosition(parents + position);
	}
	else
	{
		m_txtTitle->setPosition(position);
	}
}

void UIPopupWindow::setFontName_Title(const std::string& name)
{
	m_txtTitle->setFontName(name);
}

void UIPopupWindow::SetTitleString(const std::string& text, const std::string& font, const Vec2& pos, int size, const Color3B& color)
{
	m_txtTitle->setString(text);
	m_txtTitle->setFontName(font);
	this->setPosition_Title(pos);
	m_txtTitle->setFontSize(size);
	m_txtTitle->setColor(color);
}

void UIPopupWindow::setFontSize_Msg(int size)     //�޽����� ��Ʈ ����� �����Ѵ�.
{
	m_txt->setFontSize(size);
}
void UIPopupWindow::setColor_Msg(const Color3B& color)    //�޽��� ��Ʈ ���� ����
{
	m_txt->setColor(color);
}
void UIPopupWindow::setPosition_Msg(const Point& position)
{
	if (m_sprBg)
	{
		Vec2 parents = m_sprBg->getPosition();
		parents.scale(m_sprBg->getAnchorPoint());
		m_txt->setPosition(parents + position);
	}
	else
	{
		m_txt->setPosition(position);
	}
}

void UIPopupWindow::setFontName_Msg(const std::string& name)
{
	m_txt->setFontName(name);
}

void UIPopupWindow::SetMsgString(const std::string& text, const std::string& font, const Vec2& pos, int size, const Color3B& color)
{
	m_txt->setString(text);
	m_txt->setFontName(font);
	this->setPosition_Msg(pos);
	m_txt->setFontSize(size);
	m_txt->setColor(color);
}