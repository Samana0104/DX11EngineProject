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

std::vector<ComPtr<ID3D11Buffer>>& Shader::GetConstantBuffers()
{
    return m_constantBuffers;
}

const ShaderType& Shader::GetShaderType() const
{
    return m_shaderType;
}
