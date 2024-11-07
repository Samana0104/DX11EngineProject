/*
author : ���Ѻ�
description : ���̴��� �⺻ ���Ǹ� �ϱ� ���� ���� ��� ����
��� ���̴��� �� ������ ����Ѵ�

version: 1.0.0
date: 2024-11-04
*/

#pragma once
#include "pch.h"

namespace HBSoft
{
    enum class ShaderType
    {
        VERTEX = 0,
        PIXEL,
    };

    struct ShaderDesc
    {
        ShaderType   m_shaderType;
        std::wstring m_shaderPath;
        std::string  m_shaderEntry;
    };

    class Shader
    {
    protected:
        ComPtr<ID3DBlob> m_shaderByteCode;
        ShaderDesc       m_shaderDesc;

    protected:
        Shader(const ShaderDesc& desc);

    public:
        const ShaderDesc& GetShaderDesc() const;

        virtual bool CreateShader()             = 0;
        virtual void SetUpConfiguration() const = 0;
    };
}  // namespace HBSoft
