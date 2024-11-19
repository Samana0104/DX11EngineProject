/*
author : 변한빛
description : 쉐이더를 생성하는 소스파일

version: 1.0.0
date: 2024-11-17
*/

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
