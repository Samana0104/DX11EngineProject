#include "pch.h"
#include "ShaderHandler.h"
using namespace HBSoft;

bool ShaderHandler::CreateVertexShader(const MESH_KEY& _key, const ShaderDesc& _desc)
{
    std::shared_ptr<Shader> vertexShader = std::make_shared<VertexShader>(_desc);
    return Add(_key, vertexShader);
}

bool ShaderHandler::CreatePixelShader(const MESH_KEY& _key, const ShaderDesc& _desc)
{
    std::shared_ptr<Shader> pixelShader = std::make_shared<PixelShader>(_desc);
    return Add(_key, pixelShader);
}

bool ShaderHandler::CreateShaderResource(const ShaderDesc _desc)
{
    auto         fileInfo = CoreAPI::GetFileNameAndExt(_desc.m_shaderPath);
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
