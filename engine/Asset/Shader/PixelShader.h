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
        bool CreateShader(std::shared_ptr<D3Device>& device);
        bool CreateConstantBuffer(std::shared_ptr<D3Device>& device);
        bool CreatePixelShader(std::shared_ptr<D3Device>& device);

    public:
        PixelShader(std::shared_ptr<D3Device>& device, const wstringV path, const ShaderType& type);

        /*
            return : Pixelshader obj
            description :
                �ش� ���̴��� �ȼ� ���̴��� ��� �ȼ� ���̴� ������ �ѱ��.
                �� ���ؽ� ���̴��� ��� nullptr�� ��ȯ�Ѵ�.
        */
        virtual ComPtr<ID3D11PixelShader> GetPixselShader() override;

        /*
            return : Vertexshader obj
            description :
                �ش� ���̴��� ���ؽ� ���̴��� ��� ���ؽ� ���̴� ������ �ѱ��.
                �� �ȼ� ���̴��� ��� nullptr�� ��ȯ�Ѵ�.
        */
        virtual ComPtr<ID3D11VertexShader> GetVertexShader() override;

        /*
            return : IALayout obj
            description :
                �ش� ���̴��� ���ؽ� ���̴��� ��� ��ǲ ���̾ƿ��� �ѱ��.
                �� �ȼ� ���̴��� ��� nullptr�� ��ȯ�Ѵ�.
        */
        virtual ComPtr<ID3D11InputLayout> GetIALayout() override;
    };
}  // namespace HBSoft
