#ifndef UIPopupWindow_h
#define UIPopupWindow_h

#include "ui/cocosgui.h"
#include "PopupWindowBase.h"

using namespace cocos2d::ui;
class UIPopupWindow : public UI_PopupWindowBase
{
public:
	static UIPopupWindow * create(Sprite  *sprBackgroundImg); //�⺻������ ��׶��� �̹�����  ���濡 ������ �̹����� �����Ѵ�.
	virtual bool onInit();

	void addPlist(const std::string& filename);

	void addText(const std::string& text, const std::string& font, const Vec2& pos, int size = 28, const Color3B& color = Color3B::BLACK);
	void addSlideButton(const std::string& track, const std::string& progress, const std::string& normal, const std::string& pressed, const std::string& disable, Widget::TextureResType texType, const float percentage, const Point &pos, const int nTag);
	void addButton(const char* normalTexture, const char* selectedTexture, const char* disabledTexture, Widget::TextureResType texType, const Point &pos, const std::string& text, const int nTag); //�˾�â�� ��ư�� �߰��Ѵ�.
	virtual void onBtnCallback(Ref *pSender, ui::Button::TouchEventType touchType);//�߰��Ǵ� ��ư�鿡 ���� �ݹ��Լ� ����
	virtual void onSldCallback(Ref *pSender, ui::Slider::EventType touchType);// �����̵�.

	void addGuideRect(Vec2 vStartPonit, Size sRectSize);	// guide�� [3/20/2015 ChoiJunHyeok]

	//CREATE_FUNC(UIPopupWindow);    //�⺻ create()�Լ� ����
public:
	virtual void setFontSize_Title(int size);   //Ÿ��Ʋ ��Ʈ ����� �����Ѵ�.
	virtual void setColor_Title(const Color3B& color);  //Ÿ��Ʋ ��Ʈ ���� ����
	virtual void setPosition_Title(const Point& position);
	virtual void setFontName_Title(const std::string& name);

	void SetTitleString(const std::string& text, const std::string& font, const Vec2& pos, int size = 32, const Color3B& color = Color3B::BLACK);

	void setFontSize_Msg(int size);     //�޽����� ��Ʈ ����� �����Ѵ�.
	void setColor_Msg(const Color3B& color);    //�޽��� ��Ʈ ���� ����
	void setPosition_Msg(const Point& position);
	void setFontName_Msg(const std::string& name);

	void SetMsgString(const std::string& text, const std::string& font, const Vec2& pos, int size = 28, const Color3B& color = Color3B::BLACK);

	void setTitleString(const std::string& text);
	void setMessageString(const std::string& text);

	void setBackgroundImagePosition(const Point& position);//��׶��� �̹����� ���� ��ġ ����

	void setBackgroundImage(Sprite  *sprBg);//���� ������ �ڽ�
	void setBackgroundBorard(Sprite  *sprBg);//�˾� �Ʒ��� �����̳� �� �̷���? �Ͽ��� �� �عٴ�

	Size getContentsSize() { return m_sprBg->getContentSize(); }
protected:
	virtual bool onTouchBegan(Touch *touch, Event *unused_event) { return true; }
	virtual void onTouchMoved(Touch *touch, Event *unused_event) {}
	virtual void onTouchEnded(Touch *touch, Event *unused_event) {}
	virtual void onTouchCancelled(Touch *touch, Event *unused_event) {}

	void setTextInit(); //����� ���� UI�ʱ�ȭ
protected:
	Sprite  *m_sprBg;   //��׶��� �̹���
	Text    *m_txtTitle;    //Ÿ��Ʋ
	Text    *m_txt;         //����

	long    m_nZorderCnt;
};

#endif
