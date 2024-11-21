#include "pch.h"
#include "Test3DObj.h"

using namespace HBSoft;

Test3DObj::Test3DObj()
{
    SetMeshKey(L"Goose.fbx");
    SetVSShaderKey(L"AnimationVertex.hlsl");
    // SetVSShaderKey(L"VertexShader.hlsl");

    // SetPSShaderKey(L"PixelShader.hlsl"); //텍스쳐 있는 놈
    SetPSShaderKey(L"ColorPixelShader.hlsl");  // 텍스쳐 없는 놈
}

void Test3DObj::Render()
{
    UINT pStrides = sizeof(Vertex);  // 1개의 정점 크기
    UINT pOffsets = 0;               // 버퍼에 시작 인덱스
    // m_mesh->m_bindPoseMat *= m_mesh->m_aniClip[1].keys[1][0].
    m_vsShader->SetUpToContext(HDEVICE);
    m_psShader->SetUpToContext(HDEVICE);
    m_vsShader->SetConstantBuffer(HDEVICE,
                                  (void*)&m_mesh->m_bindPoseMat.at(0),
                                  sizeof(mat4) * m_mesh->m_bindPoseMat.size(),
                                  1);

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
            // HDEVICE->m_context->PSSetShaderResources(
            // 0,
            // 1,
            // HASSET->m_textures[m_mesh->m_subMeshes[i]->textureName]->GetSRV().GetAddressOf());
        }
        HDEVICE->m_context->IASetIndexBuffer(m_mesh->m_subMeshes[i]->indexBuffer.Get(),
                                             DXGI_FORMAT_R32_UINT,
                                             0);
        HDEVICE->m_context->DrawIndexed((UINT)m_mesh->m_subMeshes[i]->indices.size(), 0, 0);
    }
}
