#pragma once

#include "pch.h"

namespace HBSoft
{
    class DirectionalLight
    {
    public:
        vec3  m_dir;
        float m_lightPower;

    public:
        DirectionalLight(const vec3 dir, float lightPower);

        void SetLightDirection(const vec3 dir);
    };
}  // namespace HBSoft
