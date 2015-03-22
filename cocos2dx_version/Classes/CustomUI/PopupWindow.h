#ifndef UIPopupWindow_h
#define UIPopupWindow_h

#include "ui/cocosgui.h"
#include "PopupWindowBase.h"

using namespace cocos2d::ui;
class UIPopupWindow : public UI_PopupWindowBase
{
public:
	static UIPopupWindow * create(Sprite  *sprBackgroundImg); //기본생성시 백그라운드 이미지와  백배경에 반투명 이미지를 설정한다.
	virtual bool onInit();

	void addPlist(const std::string& filename);

	void addText(const std::string& text, const std::string& font, const Vec2& pos, int size = 28, const Color3B& color = Color3B::BLACK);
	void addSlideButton(const std::string& track, const std::string& progress, const std::string& normal, const std::string& pressed, const std::string& disable, Widget::TextureResType texType, const float percentage, const Point &pos, const int nTag);
	void addButton(const char* normalTexture, const char* selectedTexture, const char* disabledTexture, Widget::TextureResType texType, const Point &pos, const std::string& text, const int nTag); //팝업창에 버튼을 추가한다.
	virtual void onBtnCallback(Ref *pSender, ui::Button::TouchEventType touchType);//추가되는 버튼들에 대한 콜백함수 설정
	virtual void onSldCallback(Ref *pSender, ui::Slider::EventType touchType);// 슬라이드.

	void addGuideRect(Vec2 vStartPonit, Size sRectSize);	// guide용 [3/20/2015 ChoiJunHyeok]

	//CREATE_FUNC(UIPopupWindow);    //기본 create()함수 정의
public:
	virtual void setFontSize_Title(int size);   //타이틀 폰트 사이즈를 설정한다.
	virtual void setColor_Title(const Color3B& color);  //타이틀 폰트 색상 설정
	virtual void setPosition_Title(const Point& position);
	virtual void setFontName_Title(const std::string& name);

	void SetTitleString(const std::string& text, const std::string& font, const Vec2& pos, int size = 32, const Color3B& color = Color3B::BLACK);

	void setFontSize_Msg(int size);     //메시지의 폰트 사이즈를 설정한다.
	void setColor_Msg(const Color3B& color);    //메시지 폰트 색상 설정
	void setPosition_Msg(const Point& position);
	void setFontName_Msg(const std::string& name);

	void SetMsgString(const std::string& text, const std::string& font, const Vec2& pos, int size = 28, const Color3B& color = Color3B::BLACK);

	void setTitleString(const std::string& text);
	void setMessageString(const std::string& text);

	void setBackgroundImagePosition(const Point& position);//백그라운드 이미지에 대한 위치 조정

	void setBackgroundImage(Sprite  *sprBg);//실제 보여질 박스
	void setBackgroundBorard(Sprite  *sprBg);//팝업 아래에 투명이나 머 이런거? 하여간 맨 밑바닥

	Size getContentsSize() { return m_sprBg->getContentSize(); }
protected:
	virtual bool onTouchBegan(Touch *touch, Event *unused_event) { return true; }
	virtual void onTouchMoved(Touch *touch, Event *unused_event) {}
	virtual void onTouchEnded(Touch *touch, Event *unused_event) {}
	virtual void onTouchCancelled(Touch *touch, Event *unused_event) {}

	void setTextInit(); //출력할 문자 UI초기화
protected:
	Sprite  *m_sprBg;   //백그라운드 이미지
	Text    *m_txtTitle;    //타이틀
	Text    *m_txt;         //내용

	long    m_nZorderCnt;
};

#endif
