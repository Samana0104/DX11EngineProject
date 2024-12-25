/*
author : 변한빛
description : 픽셀 쉐이더의 기본 정의를 하기 위해 만든 헤더 파일

version: 1.0.5
date: 2024-11-14
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
        bool CreateShader(std::shared_ptr<D3Device> device);
        bool CreateConstantBuffer(std::shared_ptr<D3Device> device);
        bool CreatePixelShader(std::shared_ptr<D3Device> device);

    public:
        PixelShader(std::shared_ptr<D3Device> device, const wstringV path);
        /*
           description :
               context에 쉐이더를 설정해준다. ( 상수, 쉐이더 코드 )
               vertex 쉐이더의 경우 IA까지 자동으로 설정해줌
        */
        virtual void SetUpToContext(std::shared_ptr<D3Device> device) override;
    };
}  // namespace HBSoft
