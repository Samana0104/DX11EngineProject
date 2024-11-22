/*
author : ���Ѻ�
description : ���ؽ� ���̴��� �����ϱ� ���� ���� ��� ����

version: 1.0.5
date: 2024-11-14
*/

#pragma once
#include "Shader.h"

namespace HBSoft
{
    class VertexShader : public Shader
    {
    public:
        ComPtr<ID3D11VertexShader> m_vertexShader;
        ComPtr<ID3D11InputLayout>  m_vertexLayout;

    private:
        bool CreateShader(std::shared_ptr<D3Device> device);
        bool CreateVertexShader(std::shared_ptr<D3Device> device);
        bool CreateIALayoutAndConstantBuffer(std::shared_ptr<D3Device> device);

    public:
        VertexShader(std::shared_ptr<D3Device> device, const wstringV path, const ShaderType& type);
        /*
           description :
               context�� ���̴��� �������ش�. ( ���, ���̴� �ڵ� )
               vertex ���̴��� ��� IA���� �ڵ����� ��������
       */
        virtual void SetUpToContext(std::shared_ptr<D3Device> device) override;
    };
}  // namespace HBSoft
