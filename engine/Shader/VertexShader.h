#pragma once
#include "Shader.h"

namespace HBSoft
{
    class VertexShader : public Shader
    {
    private:
        ComPtr<ID3D11VertexShader> mVertexShader;
        ComPtr<ID3D11InputLayout>  mVertexLayout;

    private:
        bool CreateVertexShader();
        bool CreateIALayout();

    public:
        VertexShader(const ShaderDesc& _desc);

        virtual bool CreateShader() override;
        virtual void SetUpConfiguration() const override;
    };
}  // namespace HBSoft
