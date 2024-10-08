#pragma once
#include "CoreAPI.h"

namespace HBSoft
{
    class Color
    {
    public:
        static const vec4 LinearToHSV(const vec4 linearColor);
        static const vec4 HSVToLinear(const vec4 hsvColor);
    };
}  // namespace HBSoft
