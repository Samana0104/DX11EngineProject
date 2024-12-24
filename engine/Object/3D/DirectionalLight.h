#pragma once

#include "pch.h"

namespace HBSoft
{
    class DirectionalLight
    {
    public:
        vec3  m_dir;
        float m_lightStrength;

    public:
        DirectionalLight(vec3 dir, float lightStrength);
    };
}  // namespace HBSoft
