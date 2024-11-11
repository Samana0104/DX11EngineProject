/*
author : 변한빛
description : 픽셀 쉐이더의 기본 정의를 하기 위해 만든 헤더 파일

version: 1.0.0
date: 2024-11-04
*/

#pragma once
#include "Shader.h"

namespace HBSoft
{
    class PixelShader : public Shader
    {
    public:
        ComPtr<ID3D11PixelShader> m_pixelShader;

    private:
        bool CreateShader(std::shared_ptr<D3Device>& device);
        bool CreateConstantBuffer(std::shared_ptr<D3Device>& device);
        bool CreatePixelShader(std::shared_ptr<D3Device>& device);

    public:
        PixelShader(std::shared_ptr<D3Device>& device, const wstringV path, const ShaderType& type);

        /*
            return : Pixelshader obj
            description :
                해당 쉐이더가 픽셀 쉐이더의 경우 픽셀 쉐이더 파일을 넘긴다.
                단 버텍스 쉐이더의 경우 nullptr을 반환한다.
        */
        virtual ComPtr<ID3D11PixelShader> GetPixselShader() override;

        /*
            return : Vertexshader obj
            description :
                해당 쉐이더가 버텍스 쉐이더의 경우 버텍스 쉐이더 파일을 넘긴다.
                단 픽셀 쉐이더의 경우 nullptr을 반환한다.
        */
        virtual ComPtr<ID3D11VertexShader> GetVertexShader() override;

        /*
            return : IALayout obj
            description :
                해당 쉐이더가 버텍스 쉐이더의 경우 인풋 레이아웃을 넘긴다.
                단 픽셀 쉐이더의 경우 nullptr을 반환한다.
        */
        virtual ComPtr<ID3D11InputLayout> GetIALayout() override;
    };
}  // namespace HBSoft
