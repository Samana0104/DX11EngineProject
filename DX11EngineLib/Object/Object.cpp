#include "pch.h"
#include "Object.h"
using namespace HBSoft;

void Object::SetCamera(std::shared_ptr<Camera> camera)
{
    m_camera = camera;
}
