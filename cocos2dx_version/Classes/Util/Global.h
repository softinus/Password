#pragma once
#include "cocos2d.h"

#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
#include "platform/android/jni/JniHelper.h"
#include <jni.h>
#include <android/log.h>
#endif

using namespace std;

static string to_string2(int num)
{
	ostringstream convert; // stream used for the conversion

	convert << num; // insert the textual representation of ¡®Number¡¯ in the characters    in the stream

	return convert.str();
}

//class AdUtil
//{
//public:
//	static void ShowFullAd();
//};
