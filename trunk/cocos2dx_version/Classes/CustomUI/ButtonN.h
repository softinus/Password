#pragma once
#include "ui\CocosGUI.h"
USING_NS_CC;
using namespace ui;
class ButtonN :
	public Button
{
public:
	ButtonN();
	~ButtonN();

	ButtonN* create();
	static ButtonN* create(const std::string& normalImage,
		const std::string& selectedImage = "",
		const std::string& disableImage = "",
		TextureResType texType = TextureResType::LOCAL);

public:
	void SetDisable(bool _bDisable)	{ m_bDisabled = _bDisable; };
	void SetSelect(bool _bSel) { m_bSelected = _bSel; };
	void SetNumber(int _nNum) { m_nNumber = _nNum; };
	int GetNumber() { return m_nNumber; };
	bool IsDisabled() { return m_bDisabled; };
	bool IsSelected() { return m_bSelected; };
protected:
	bool m_bDisabled;
	bool m_bSelected;
	int m_nNumber;
};

