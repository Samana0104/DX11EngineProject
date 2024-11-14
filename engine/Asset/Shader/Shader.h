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
        VERTEX = 1,
        PIXEL,
    };

    class Shader
    {
    protected:
        ComPtr<ID3DBlob>                  m_shaderByteCode;
        std::vector<ComPtr<ID3D11Buffer>> m_constantBuffers;

        std::wstring m_path;
        ShaderType   m_shaderType;


    protected:
        Shader(const wstringV path, const ShaderType& type);

    public:
        /*
           description :
               context에 쉐이더를 설정해준다. ( 상수, 쉐이더 코드 )
               vertex 쉐이더의 경우 IA까지 자동으로 설정해줌
       */
        virtual void SetUpToContext(std::shared_ptr<D3Device>& device) = 0;

        size_t GetConstantCount() const;
        void   SetConstantBuffer(std::shared_ptr<D3Device>& device, const void* data,
                                 const size_t dataSize, const UINT constantIdx);

        const ShaderType& GetShaderType() const;
    };
}  // namespace HBSoft
