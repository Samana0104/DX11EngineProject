#include "pch.h"
#include "Test3DObj.h"
#include "Camera.h"

using namespace HBSoft;

Test3DObj::Test3DObj()
{
    m_mesh     = HASSET->m_meshes[L"20241203result(merged).fbx"];
    m_vsShader = HASSET->m_shaders[L"VertexShader.hlsl"];

    aabb_goose =
    m_aabbcollider->CalculateAABB(aabb_goose, vec3(100.0f, 0.0f, 100.0f), vec3(0.5f, 0.5f, 0.5f));

    // SetPSShaderKey(L"PixelShader.hlsl");  // 텍스쳐 있는 놈
    m_psShader = HASSET->m_shaders[L"ColorPixelShader.hlsl"];  // 텍스쳐 없는 놈
}

void Test3DObj::Update(const float deltaTime)
{
    UpdateDefaultCB();
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
        if (m_mesh->m_subMeshes[i]->hasTexture)
        {
            HDEVICE->m_context->PSSetShaderResources(
            0,
            1,
            HASSET->m_textures[m_mesh->m_subMeshes[i]->textureName]->GetSRV().GetAddressOf());
        }
        HDEVICE->m_context->IASetIndexBuffer(m_mesh->m_subMeshes[i]->indexBuffer.Get(),
                                             DXGI_FORMAT_R32_UINT,
                                             0);
        HDEVICE->m_context->DrawIndexed((UINT)m_mesh->m_subMeshes[i]->indices.size(), 0, 0);
    }
}

void Test3DObj::Init() {}

void Test3DObj::Release() {}

AABB HBSoft::Test3DObj::GetaabbCollider()
{
    return aabb_goose;
}
