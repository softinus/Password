#include "UIPopupWindowBase.h"

UIPopupWindowBase::UIPopupWindowBase(void)
{

}
UIPopupWindowBase::~UIPopupWindowBase(void)
{

}
bool UIPopupWindowBase::init()
{
	if (!Layer::init())
	{
		return false;
	}
	m_callback = HK_PopupCallback();
	m_callback2 = HK_PopupCallback2();


	m_nResult = 0;    //���ϵ� ���� �ɹ����� �˾��� �ִ� ��ư�̳� �̺�Ʈ���� � ��ư�� Ŭ������� Ȥ�� �ٸ� ���ڿ� ���� �������� ���� �Դϴ�.
	m_ParrentLayer = NULL; //�θ� Node
	onInit();   //�ʱ�ȭ �Լ�
	return true;

}
bool UIPopupWindowBase::onInit()
{

	return true;
}

void UIPopupWindowBase::setCallBackFunc(const HK_PopupCallback& callback)
{
	m_callback = callback; //�ݹ��Լ����� ���ڰ� �ϳ��� �ݹ� �ν��Ͻ� ����
}
void UIPopupWindowBase::setCallBackFunc2(const HK_PopupCallback2& callback)
{
	m_callback2 = callback;//�ݹ��Լ����� ���ڰ� ���� �ݹ� �ν��Ͻ� ����
}

void UIPopupWindowBase::showPopup(cocos2d::Layer  *pParrentLayer)    //�˾�â�� ����
{
	//�˾��� �����ϰ� ������ ȭ�鿡 ���̰��Ҷ� �θ� Layer�� �̺�Ʈ�� ���޵��� ����
	m_ParrentLayer = pParrentLayer;
	if (m_ParrentLayer) {

		m_ParrentLayer->setTouchEnabled(false);
		m_ParrentLayer->addChild(this, INT_MAX);
	}
	else
	{
		Director::getInstance()->getRunningScene()->addChild(this, INT_MAX);
	}
	_touchMode = Touch::DispatchMode::ONE_BY_ONE;
	_swallowsTouches = true;

	setTouchEnabled(true);

}
void UIPopupWindowBase::closePopup()
{
	//�˾�â�� �ݰ����Ҷ� ���� ȣ���Ұ�

	setTouchEnabled(false);

	if (m_ParrentLayer) {
		m_ParrentLayer->setTouchEnabled(true);
	}

	removeAllChildren();
	removeFromParent();

}
void UIPopupWindowBase::onCallBackFunc()   //�ݹ� �Լ� ����
{
	//�Լ��ݹ� ����
	if (m_callback)
		m_callback(this);
	if (m_callback2) {
		m_callback2(this, m_nResult);
	}
}