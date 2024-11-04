/*
author : ���Ѻ�
description : �ȼ� ���̴��� �⺻ ���Ǹ� �ϱ� ���� ���� ��� ����

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
