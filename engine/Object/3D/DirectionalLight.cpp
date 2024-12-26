#include "pch.h"
#include "DirectionalLight.h"
using namespace HBSoft;

DirectionalLight::DirectionalLight(const vec3 dir, float lightPower)
{
    m_dir        = glm::normalize(dir);
    m_lightPower = glm::clamp<float>(lightPower, 0.f, 1.f);
}

void DirectionalLight::SetLightDirection(const vec3 dir)
{
    m_dir = glm::normalize(dir);
}
