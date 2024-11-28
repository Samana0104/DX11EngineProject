#include "pch.h"
#include "Test3DObj.h"
#include "Camera.h"

using namespace HBSoft;

Test3DObj::Test3DObj()
{
    SetMeshKey(L"gardener_model.fbx");
    SetVSShaderKey(L"AnimationVertex.hlsl");
    // SetVSShaderKey(L"VertexShader.hlsl");

    // SetPSShaderKey(L"PixelShader.hlsl");  // 텍스쳐 있는 놈
    SetPSShaderKey(L"ColorPixelShader.hlsl");  // 텍스쳐 없는 놈

    anim.resize(m_mesh->m_bindPoseMat.size());
}

void Test3DObj::Update(const float deltaTime)
{
    static float startFrame = 0.f;

    startFrame += deltaTime * 10.f;
    int frame   = static_cast<int>(startFrame);

    for (int i = 0; i < m_mesh->m_bindPoseMat.size(); i++)
    {
        // anim[i] = m_mesh->m_animationMat[i][frame] * m_mesh->m_bindPoseMat[i];
    }

    if (startFrame > 20.f)
    {
        startFrame = 0.f;
    }

    if (m_camera != nullptr)
    {
        m_cb0.view = m_camera->GetViewMat();
        m_cb0.proj = m_camera->GetProjMat();
    }
    else
    {
        m_cb0.view = mat4(1.0f);
        m_cb0.proj = mat4(1.0f);
    }
    m_cb0.world    = m_transform.m_worldMat;
    m_cb0.invWorld = glm::inverse(m_transform.m_worldMat);
    m_vsShader->SetConstantBuffer(HDEVICE, (void*)&m_cb0, sizeof(m_cb0), 0);
    m_vsShader->SetConstantBuffer(HDEVICE, (void*)&anim.at(0), sizeof(mat4) * anim.size(), 1);
}

void Test3DObj::Render()
{
    UINT pStrides = sizeof(Vertex);  // 1개의 정점 크기
    UINT pOffsets = 0;               // 버퍼에 시작 인덱스

    m_vsShader->SetUpToContext(HDEVICE);
    m_psShader->SetUpToContext(HDEVICE);


    HDEVICE->m_context->IASetVertexBuffers(0,
                                           1,
                                           m_mesh->m_vertexBuffer.GetAddressOf(),
                                           &pStrides,
                                           &pOffsets);

    // DXGI_FORMAT_R32_UINT는 인덱스 버퍼의 타입이 UINT라 그럼
    HDEVICE->m_context->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);


    HDEVICE->m_context->PSSetSamplers(0, 1, HDEVICE->m_samplerState.GetAddressOf());
    HDEVICE->m_context->OMSetRenderTargets(1, HDEVICE->m_rtv.GetAddressOf(), HDEVICE->m_dsv.Get());

    for (size_t i = 0; i < m_mesh->m_subMeshes.size(); i++)
    {
        // if (m_mesh->m_subMeshes[i]->hasTexture)
        //{
        //     HDEVICE->m_context->PSSetShaderResources(
        //     0,
        //     1,
        //     HASSET->m_textures[m_mesh->m_subMeshes[i]->textureName]->GetSRV().GetAddressOf());
        // }
        HDEVICE->m_context->IASetIndexBuffer(m_mesh->m_subMeshes[i]->indexBuffer.Get(),
                                             DXGI_FORMAT_R32_UINT,
                                             0);
        HDEVICE->m_context->DrawIndexed((UINT)m_mesh->m_subMeshes[i]->indices.size(), 0, 0);
    }
}
