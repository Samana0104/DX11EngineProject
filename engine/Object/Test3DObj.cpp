#include "pch.h"
#include "Test3DObj.h"

using namespace HBSoft;

Test3DObj::Test3DObj()
{
    SetMeshKey(L"cook.fbx");
    SetVSShaderKey(L"VertexShader.hlsl");
    SetPSShaderKey(L"ColorPixelShader.hlsl");
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
        // HDEVICE->m_context->PSSetShaderResources(
        // 0,
        // 1,
        // HASSET->m_textures[m_mesh->m_subMeshes[i]->textureName]->GetSRV().GetAddressOf());
        HDEVICE->m_context->IASetIndexBuffer(m_mesh->m_subMeshes[i]->indexBuffer.Get(),
                                             DXGI_FORMAT_R32_UINT,
                                             0);
        HDEVICE->m_context->DrawIndexed((UINT)m_mesh->m_subMeshes[i]->indices.size(), 0, 0);
    }
}
