/*
author : 변한빛
description : 쉐이더의 기본 정의를 하기 위해 만든 헤더 파일
모든 쉐이더는 이 파일을 상속한다

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
