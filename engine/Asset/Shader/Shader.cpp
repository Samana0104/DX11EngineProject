/*
author : ���Ѻ�
description : ���̴���� �⺻ ���Ǹ� �ϱ� ���� ���� ����
��� ���̴��� �� ������ ����Ѵ�

version: 1.0.0
date: 2024-11-04
*/

#include "pch.h"
#include "Shader.h"
#include "Mesh2D.h"
using namespace HBSoft;

Shader::Shader(const wstringV path, const ShaderDesc& desc)
    : m_shaderDesc(desc), m_path(path)
{}

const ShaderDesc& Shader::GetShaderDesc() const
{
    return m_shaderDesc;
}
