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
    public:
        ComPtr<ID3D11PixelShader> m_pixelShader;

    private:
        virtual bool CreateShader(std::shared_ptr<D3Device>& device);

    public:
        PixelShader(std::shared_ptr<D3Device>& device, const wstringV path, const ShaderDesc& desc);
    };
}  // namespace HBSoft
