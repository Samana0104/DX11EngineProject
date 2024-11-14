/*
author : 변한빛
description : 쉐이더라는 기본 정의를 하기 위해 만든 파일
모든 쉐이더는 이 파일을 상속한다

version: 1.0.0
date: 2024-11-04
*/

#include "pch.h"
#include "Shader.h"
using namespace HBSoft;

Shader::Shader(const wstringV path, const ShaderType& type)
    : m_shaderType(type), m_path(path)
{}

size_t Shader::GetConstantCount() const
{
    return m_constantBuffers.size();
}

void Shader::SetConstantBuffer(std::shared_ptr<D3Device>& device, const void* data,
                               const size_t dataSize, const UINT constantIdx)
{
    if (m_constantBuffers.size() <= 0)
        return;

    D3D11_MAPPED_SUBRESOURCE ms;
    HRESULT                  hr;

    hr = device->m_context->Map(m_constantBuffers[constantIdx].Get(),
                                NULL,
                                D3D11_MAP_WRITE_DISCARD,
                                NULL,
                                &ms);
    memcpy(ms.pData, data, dataSize);
    device->m_context->Unmap(m_constantBuffers[constantIdx].Get(), NULL);
}

const ShaderType& Shader::GetShaderType() const
{
    return m_shaderType;
}
