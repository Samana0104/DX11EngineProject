#pragma once

#include "pch.h"
#include "Shader/Shader.h"
#include "Shader/VertexShader.h"
#include "Shader/PixelShader.h"

namespace HBSoft
{
    class ShaderFactory
    {
    public:
        static std::shared_ptr<Shader> Create(std::shared_ptr<D3Device>& device, wstringV path,
                                              ShaderType type);

        static bool IsShaderFormat(const wstringV ext);
    };
}  // namespace HBSoft
