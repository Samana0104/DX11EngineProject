/*
author : ���Ѻ�
description : �ȼ� ���̴��� �⺻ ���Ǹ� �ϱ� ���� ���� ��� ����

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
               context�� ���̴��� �������ش�. ( ���, ���̴� �ڵ� )
               vertex ���̴��� ��� IA���� �ڵ����� ��������
        */
        virtual void SetUpToContext(std::shared_ptr<D3Device> device) override;
    };
}  // namespace HBSoft
