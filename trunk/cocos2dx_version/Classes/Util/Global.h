#pragma once
#include "cocos2d.h"

using namespace std;

static string to_string2(int num)
{
	ostringstream convert; // stream used for the conversion

	convert << num; // insert the textual representation of ¡®Number¡¯ in the characters    in the stream

	return convert.str();
}
