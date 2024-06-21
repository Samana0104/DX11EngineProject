#pragma once
#include "MyCoreAPI.h"

namespace MyProject
{
	class MyColor
	{
	public:
		static const vec4 LinearToHSV(const vec4 _linearColor);
		static const vec4 HSVToLinear(const vec4 _hsvColor);
	};
}

