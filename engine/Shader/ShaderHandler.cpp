/*
author : 변한빛
description : 모든 쉐이더를 관리하기 위한 매니징 소스 파일

version: 1.0.0
date: 2024-11-04
*/

#include "pch.h"
#include "ShaderHandler.h"
using namespace HBSoft;

bool ShaderHandler::CreateVertexShader(const MESH_KEY& _key, const ShaderDesc& _desc)
{
    auto vertexShader = std::make_unique<VertexShader>(_desc);
    return Add(_key, std::move(vertexShader));
}

bool ShaderHandler::CreatePixelShader(const MESH_KEY& _key, const ShaderDesc& _desc)
{
    auto pixelShader = std::make_unique<PixelShader>(_desc);
    return Add(_key, std::move(pixelShader));
}

bool ShaderHandler::CreateShaderResource(const ShaderDesc _desc)
{
    auto         fileInfo = HBSoft::GetFileNameAndExt(_desc.m_shaderPath);
    std::wstring key      = fileInfo.first + fileInfo.second;

    switch (_desc.m_shaderType)
    {
    case ShaderType::VERTEX:
        return CreateVertexShader(key, _desc);

    case ShaderType::PIXEL:
        return CreatePixelShader(key, _desc);
    }

    return false;
}
