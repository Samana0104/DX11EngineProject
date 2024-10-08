#pragma once
#include "Shader.h"

namespace HBSoft
{
    class PixelShader : public Shader
    {
    private:
        ComPtr<ID3D11PixelShader> mPixelShader;

    private:
        bool CreatePixelShader();

    public:
        PixelShader(const ShaderDesc& _desc);

        virtual bool CreateShader() override;
        virtual void SetUpConfiguration() const override;
    };
}  // namespace HBSoft
