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
