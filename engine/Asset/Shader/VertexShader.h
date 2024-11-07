/*
author : ���Ѻ�
description : ���ؽ� ���̴��� �����ϱ� ���� ���� ��� ����

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
        ComPtr<ID3D11VertexShader> m_vertexShader;
        ComPtr<ID3D11InputLayout>  m_vertexLayout;

    private:
        bool CreateVertexShader(std::shared_ptr<D3Device>& device);
        bool CreateIALayout(std::shared_ptr<D3Device>& device);

        virtual bool CreateShader(std::shared_ptr<D3Device>& device) override;

    public:
        VertexShader(std::shared_ptr<D3Device>& device, const wstringV path, const ShaderDesc& desc);
    };
}  // namespace HBSoft
