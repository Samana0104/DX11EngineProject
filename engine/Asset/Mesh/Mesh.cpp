/*
author : 변한빛
description : 메쉬의 기본 리소스를 정의하기 위한 소스 파일

version: 1.0.0
date: 2024-11-08
*/

#include "pch.h"
#include "Mesh.h"
using namespace HBSoft;

Mesh::Mesh(bool hasAnimation)
    : m_hasAnimation(hasAnimation), m_vertexBuffer(nullptr), m_indexBuffer(nullptr)
{}

void Mesh::SetVertices(std::shared_ptr<D3Device>& device, const std::vector<Vertex>& vertices)
{
    device->m_context->UpdateSubresource(m_vertexBuffer.Get(), 0, NULL, &vertices.at(0), 0, 0);
}
