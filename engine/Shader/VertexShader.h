/*
author : 변한빛
description : 버텍스 쉐이더를 정의하기 위해 만든 헤더 파일

version: 1.0.0
date: 2024-11-04
*/

#pragma once
#include "Shader.h"

namespace HBSoft
{
    class VertexShader : public Shader
    {
    private:
        ComPtr<ID3D11VertexShader> mVertexShader;
        ComPtr<ID3D11InputLayout>  mVertexLayout;

    private:
        bool CreateVertexShader();
        bool CreateIALayout();

    public:
        VertexShader(const ShaderDesc& _desc);

        virtual bool CreateShader() override;
        virtual void SetUpConfiguration() const override;
    };
}  // namespace HBSoft
