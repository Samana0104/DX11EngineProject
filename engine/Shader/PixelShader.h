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
    private:
        ComPtr<ID3D11PixelShader> m_pixelShader;

    private:
        bool CreatePixelShader();

    public:
        PixelShader(const ShaderDesc& _desc);

        virtual bool CreateShader() override;
        virtual void SetUpConfiguration() const override;
    };
}  // namespace HBSoft
