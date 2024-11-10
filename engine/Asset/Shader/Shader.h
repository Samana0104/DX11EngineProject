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
