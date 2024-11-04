#include "pch.h"
#include "Actor.h"
using namespace HBSoft;

Actor::Actor() {}

void Actor::SetViewedCamera(Camera* _camera)
{
    mCamera = _camera;
}

void Actor::Update(const float _deltaTime) {}

void Actor::Render()
{
    if (mCamera == nullptr)
    {
        Object2D::Render();
    }
    else
    {
        m_manager.m_shader[m_shaderKey]->SetUpConfiguration();
        m_manager.m_texture[m_textureKey]->Render();
        m_manager.m_mesh[m_meshKey]->Draw(mCamera->GetViewMat() * m_transform.GetModelMat(), m_color);
    }
}
