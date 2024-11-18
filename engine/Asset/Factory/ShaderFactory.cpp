#include "pch.h"
#include "ShaderFactory.h"
using namespace HBSoft;

std::shared_ptr<Shader> ShaderFactory::Create(std::shared_ptr<D3Device>& device, wstringV path,
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

    default:
        assert(false);  // 무슨 쉐이더인지 제대로 기입하시오
    }

    return shader;
}

bool ShaderFactory::IsShaderFormat(const wstringV ext)
{
    if (ext.compare(L".hlsl") == 0)
        return true;

    return false;
}
