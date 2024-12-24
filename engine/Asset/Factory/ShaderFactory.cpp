/*
author : ���Ѻ�
description : ���̴��� �����ϴ� �ҽ�����

version: 1.0.0
date: 2024-11-17
*/
#include "pch.h"
#include "ShaderFactory.h"
using namespace HBSoft;

std::shared_ptr<Shader> ShaderFactory::Create(std::shared_ptr<D3Device> device, wstringV path,
                                              ShaderType type)
{
    std::shared_ptr<Shader> shader;

    switch (type)
    {
    case ShaderType::VERTEX:
        shader = std::make_shared<VertexShader>(device, path, type);
        break;

    case ShaderType::PIXEL:
        shader = std::make_shared<PixelShader>(device, path, type);
        break;

    case ShaderType::GEOMETRY:
        shader = std::make_shared<GeometryShader>(device, path, type);
        break;

    default:
        assert(false);  // ���� ���̴����� ����� �����Ͻÿ�
    }

    return shader;
}

bool ShaderFactory::IsShaderFormat(const wstringV ext)
{
    if (ext.compare(L".hlsl") == 0)
        return true;

    return false;
}
