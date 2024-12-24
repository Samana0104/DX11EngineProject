/*
author : ���Ѻ�
description : ���̴���� �⺻ ���Ǹ� �ϱ� ���� ���� ����
��� ���̴��� �� ������ ����Ѵ�

version: 1.0.0
date: 2024-11-04
*/

#include "pch.h"
#include "Shader.h"
using namespace HBSoft;

Shader::Shader(const wstringV path, const ShaderType& type)
    : m_shaderType(type), m_path(path)
{}

std::vector<D3D11_BUFFER_DESC>& Shader::GetCBDescs()
{
    return m_cbDesc;
}

const ShaderType& Shader::GetShaderType() const
{
    return m_shaderType;
}
