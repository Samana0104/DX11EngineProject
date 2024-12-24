#include "pch.h"
#include "DirectionalLight.h"
using namespace HBSoft;

DirectionalLight::DirectionalLight(vec3 dir, float lightStrength)
{
    m_dir           = glm::normalize(dir);
    m_lightStrength = glm::clamp<float>(lightStrength, 0.f, 1.f);
}
