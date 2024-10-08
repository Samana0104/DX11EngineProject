#pragma once
#include "CoreAPI.h"

namespace HBSoft
{
    enum class ShaderType
    {
        VERTEX = 0,
        PIXEL,
    };

    struct ShaderDesc
    {
        ShaderType   m_shaderType;
        std::wstring m_shaderPath;
        std::string  m_shaderEntry;
    };

    class Shader
    {
    protected:
        ComPtr<ID3DBlob> m_shaderByteCode;
        ShaderDesc       m_shaderDesc;

    protected:
        inline static D3Device& m_device = D3Device::GetInstance();

    protected:
        Shader(const ShaderDesc& _desc);

    public:
        const ShaderDesc& GetShaderDesc() const;

        virtual bool CreateShader()             = 0;
        virtual void SetUpConfiguration() const = 0;
    };
}  // namespace HBSoft
