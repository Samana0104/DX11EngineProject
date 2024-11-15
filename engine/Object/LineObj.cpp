#include "pch.h"
#include "LineObj.h"
using namespace HBSoft;

LineObj::LineObj()
{
    m_textureKey  = L"";
    m_meshKey     = L"LINE";
    m_vsShaderKey = L"LineVertex.hlsl";
    m_psShaderKey = L"LinePixel.hlsl";
    m_color       = {1.f, 1.f, 1.f, 1.f};
}

void LineObj::Draw(vec3 start, vec3 end, vec4 color)
{
    std::shared_ptr<Mesh> mesh = HASSET->m_meshes[m_meshKey];
    Vertex                v1, v2;

    v1.p = start;
    v1.c = color;
    v2.p = end;
    v2.c = color;

    mesh->SetVertices(HDEVICE, {v1, v2});

    UINT pStrides = sizeof(Vertex);  // 1개의 정점 크기
    UINT pOffsets = 0;               // 버퍼에 시작 인덱스

    HASSET->m_shaders[m_vsShaderKey]->SetUpToContext(HDEVICE);
    HASSET->m_shaders[m_psShaderKey]->SetUpToContext(HDEVICE);

    HDEVICE->m_context->IASetVertexBuffers(0,
                                           1,
                                           mesh->m_vertexBuffer.GetAddressOf(),
                                           &pStrides,
                                           &pOffsets);
    HDEVICE->m_context->IASetIndexBuffer(mesh->m_indexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
    HDEVICE->m_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
    HDEVICE->m_context->DrawIndexed((UINT)mesh->m_indices.size(), 0, 0);
}

void LineObj::SetMatrix(mat4 viewMat, mat4 projMat)
{
    m_vsConstant.view  = viewMat;
    m_vsConstant.proj  = projMat;
    m_vsConstant.model = m_transform.m_worldMat;

    HASSET->m_shaders[m_vsShaderKey]->SetConstantBuffer(HDEVICE,
                                                        (void*)&m_vsConstant,
                                                        sizeof(m_vsConstant),
                                                        0);
}
