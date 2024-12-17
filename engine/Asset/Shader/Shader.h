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
    enum class ShaderType : uint8
    {
        VERTEX = 1,
        PIXEL,
        GEOMETRY
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
           description :
               context�� ���̴��� �������ش�. ( ���, ���̴� �ڵ� )
               vertex ���̴��� ��� IA���� �ڵ����� ��������
       */
        virtual void SetUpToContext(std::shared_ptr<D3Device> device) = 0;

        size_t GetConstantCount() const;

        std::vector<ComPtr<ID3D11Buffer>>& GetConstantBuffers();

        /*
            param : data -> ��� ���ۿ� ���� void�� ������ | dataSize -> ��� ���ۿ� ���� �������� ũ��
                    constantIdx -> ��� ���� �������� ��ȣ
            description :
               ��� ���۸� ���Ž����ش�.
        */
        const ShaderType& GetShaderType() const;
    };
}  // namespace HBSoft
