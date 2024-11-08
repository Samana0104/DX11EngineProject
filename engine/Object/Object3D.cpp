#include "pch.h"
#include "Object3D.h"
using namespace HBSoft;

void Object3D::Update(const float deltaTime) {}

void Object3D::Render()
{
    std::shared_ptr<Mesh> mesh = HASSET->m_meshes[m_meshKey];

    std::shared_ptr<VertexShader> vsShader =
    std::dynamic_pointer_cast<VertexShader>(HASSET->m_shaders[m_vsShaderKey]);

    std::shared_ptr<PixelShader> psShader =
    std::dynamic_pointer_cast<PixelShader>(HASSET->m_shaders[m_psShaderKey]);

    HDEVICE->m_context->IASetInputLayout(vsShader->m_vertexLayout.Get());
}
