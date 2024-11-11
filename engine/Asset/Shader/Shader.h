/*
author : ���Ѻ�
description : ���̴��� �⺻ ���Ǹ� �ϱ� ���� ���� ��� ����
��� ���̴��� �� ������ ����Ѵ�

version: 1.0.0
date: 2024-11-04
*/

#pragma once
#include "pch.h"

namespace HBSoft
{
    enum class ShaderType
    {
        VERTEX = 1,
        PIXEL,
    };

    class Shader
    {
    protected:
        ComPtr<ID3DBlob>                  m_shaderByteCode;
        std::vector<ComPtr<ID3D11Buffer>> m_constantBuffers;

        std::wstring m_path;
        ShaderType   m_shaderType;


    protected:
        Shader(const wstringV path, const ShaderType& type);

    public:
        /*
            return : Pixelshader obj
            description :
                �ش� ���̴��� �ȼ� ���̴��� ��� �ȼ� ���̴� ������ �ѱ��.
                �� ���ؽ� ���̴��� ��� nullptr�� ��ȯ�Ѵ�.
        */
        virtual ComPtr<ID3D11PixelShader> GetPixselShader() = 0;

        /*
            return : Vertexshader obj
            description :
                �ش� ���̴��� ���ؽ� ���̴��� ��� ���ؽ� ���̴� ������ �ѱ��.
                �� �ȼ� ���̴��� ��� nullptr�� ��ȯ�Ѵ�.
        */
        virtual ComPtr<ID3D11VertexShader> GetVertexShader() = 0;

        /*
            return : IALayout obj
            description :
                �ش� ���̴��� ���ؽ� ���̴��� ��� ��ǲ ���̾ƿ��� �ѱ��.
                �� �ȼ� ���̴��� ��� nullptr�� ��ȯ�Ѵ�.
        */
        virtual ComPtr<ID3D11InputLayout> GetIALayout() = 0;

        ComPtr<ID3D11Buffer>& GetConstantBuffer(const UINT constantIdx);
        size_t                GetConstantCount() const;

        void SetConstantBuffer(std::shared_ptr<D3Device> device, const void* data, const size_t dataSize,
                               const UINT constantIdx);

        const ShaderType& GetShaderType() const;
    };
}  // namespace HBSoft
