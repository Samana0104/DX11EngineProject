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
        VERTEX  = 1,
        PIXEL,
    };

    class Shader
    {
    protected:
        ComPtr<ID3DBlob> m_shaderByteCode;

        std::wstring m_path;
        ShaderType   m_shaderType;


    protected:
        Shader(const wstringV path, const ShaderType& type);

    public:
        virtual bool CreateShader(std::shared_ptr<D3Device>& device) = 0;

        const ShaderType& GetShaderType() const;
    };
}  // namespace HBSoft
