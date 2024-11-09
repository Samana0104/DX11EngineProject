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

	UINT startSlot = 0;
	UINT numBuffers = 1;
	UINT pStrides = sizeof(Vertex); // 1개의 정점 크기
	UINT pOffsets = 0; // 버퍼에 시작 인덱스

    HDEVICE->m_context->IASetInputLayout(vsShader->m_vertexLayout.Get());
    HDEVICE->m_context->IASetVertexBuffers(startSlot,
                                           numBuffers,
                                           mesh->m_vertexBuffer.GetAddressOf(),
                                           &pStrides,
                                           &pOffsets);
    HDEVICE->m_context->IASetIndexBuffer(mesh->m_indexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
	HDEVICE->m_context->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    HDEVICE->m_context->PSSetShaderResources(0,
                                             1,
                                             HASSET->m_textures[m_textureKey]->GetSRV().GetAddressOf());
    HDEVICE->m_context->PSSetSamplers(0, 1, HDEVICE->m_samplerState.GetAddressOf());
    HDEVICE->m_context->VSSetShader(vsShader->m_vertexShader.Get(), nullptr, 0);
    HDEVICE->m_context->PSSetShader(psShader->m_pixelShader.Get(), nullptr, 0);
    HDEVICE->m_context->RSSetViewports(1, &HDEVICE->m_viewPort);
    HDEVICE->m_context->RSSetState(HDEVICE->m_rsState.Get());
    HDEVICE->m_context->OMSetDepthStencilState(HDEVICE->m_dsState.Get(), 0);
    HDEVICE->m_context->OMSetRenderTargets(1, HDEVICE->m_rtv.GetAddressOf(), HDEVICE->m_dsv.Get());
    // DXGI_FORMAT_R32_UINT는 인덱스 버퍼의 타입이 UINT라 그럼
    HDEVICE->m_context->DrawIndexed((UINT)mesh->m_indices.size(), 0, 0);
}
