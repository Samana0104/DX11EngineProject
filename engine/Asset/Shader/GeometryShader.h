/*
author : ���Ѻ�
description : ���� ���̴��� �⺻ ���Ǹ� �ϱ� ���� ���� ��� ����

version: 1.0.0
date: 2024-12-17
*/

#pragma once

#include "Shader\Shader.h"

namespace HBSoft
{
    class GeometryShader : public Shader
    {
    public:
        ComPtr<ID3D11GeometryShader> m_geometryShader;

    private:
        bool CreateShader(std::shared_ptr<D3Device> device);
        bool CreateConstantBuffer(std::shared_ptr<D3Device> device);
        bool CreateGeometryShader(std::shared_ptr<D3Device> device);

    public:
        GeometryShader(std::shared_ptr<D3Device> device, const wstringV path);
        /*
           description :
               context�� ���̴��� �������ش�. ( ���, ���̴� �ڵ� )
               vertex ���̴��� ��� IA���� �ڵ����� ��������
        */
        virtual void SetUpToContext(std::shared_ptr<D3Device> device) override;
    };
}  // namespace HBSoft
