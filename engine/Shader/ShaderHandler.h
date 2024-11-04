/*
author : 변한빛
description : 모든 쉐이더를 관리하기 위해 만든 헤더 파일

version: 1.0.0
date: 2024-11-04
*/

#pragma once
#include "MgrTemplate.h"
#include "VertexShader.h"
#include "PixelShader.h"

namespace HBSoft
{
    class ShaderHandler : public MgrTemplate<Shader, SHADER_KEY>
    {
    private:
        bool CreateVertexShader(const MESH_KEY& _key, const ShaderDesc& _desc);
        bool CreatePixelShader(const MESH_KEY& _key, const ShaderDesc& _desc);

    public:
        bool CreateShaderResource(const ShaderDesc _desc);
    };
}  // namespace HBSoft
