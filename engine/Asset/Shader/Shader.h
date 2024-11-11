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
            return : Pixelshader obj
            description :
                해당 쉐이더가 픽셀 쉐이더의 경우 픽셀 쉐이더 파일을 넘긴다.
                단 버텍스 쉐이더의 경우 nullptr을 반환한다.
        */
        virtual ComPtr<ID3D11PixelShader> GetPixselShader() = 0;

        /*
            return : Vertexshader obj
            description :
                해당 쉐이더가 버텍스 쉐이더의 경우 버텍스 쉐이더 파일을 넘긴다.
                단 픽셀 쉐이더의 경우 nullptr을 반환한다.
        */
        virtual ComPtr<ID3D11VertexShader> GetVertexShader() = 0;

        /*
            return : IALayout obj
            description :
                해당 쉐이더가 버텍스 쉐이더의 경우 인풋 레이아웃을 넘긴다.
                단 픽셀 쉐이더의 경우 nullptr을 반환한다.
        */
        virtual ComPtr<ID3D11InputLayout> GetIALayout() = 0;

        ComPtr<ID3D11Buffer>& GetConstantBuffer(const UINT constantIdx);
        size_t                GetConstantCount() const;

        void SetConstantBuffer(std::shared_ptr<D3Device> device, const void* data, const size_t dataSize,
                               const UINT constantIdx);

        const ShaderType& GetShaderType() const;
    };
}  // namespace HBSoft
