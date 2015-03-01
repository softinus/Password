#include "ButtonN.h"


ButtonN::ButtonN()
{
}


ButtonN::~ButtonN()
{
}

ButtonN* ButtonN::create()
{
	ButtonN* widget = new (std::nothrow) ButtonN();
	if (widget && widget->init())
	{
		widget->autorelease();
		return widget;
	}
	CC_SAFE_DELETE(widget);
	return nullptr;
}

ButtonN* ButtonN::create(const std::string &normalImage,
	const std::string& selectedImage,
	const std::string& disableImage,
	TextureResType texType)
{
	ButtonN *btn = new (std::nothrow) ButtonN;
	if (btn && btn->init(normalImage, selectedImage, disableImage, texType))
	{
		btn->autorelease();
		return btn;
	}
	CC_SAFE_DELETE(btn);
	return nullptr;
}
