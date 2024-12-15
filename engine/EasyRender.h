#pragma once

#include "Core/Core.h"

namespace HBSoft
{
    // 상태 값 모르면 무지성 0번 ㄱㄱㄱㄱ

    enum class ERRasterRizerState
    {
        SOLID_BACK_CULL  = 0,
        SOLID_FRONT_CULL = 1,
        SOLID_NO_CULL    = 2,
        WIRE_BACK_CULL   = 3,
        WIRE_FRONT_CULL  = 4,
        WIRE_NO_CULL     = 5,
    };

    enum class ERBlendingState
    {
        DEFAULT = 0,
    };

    enum class ERSamplerState
    {
        POINT       = 0,
        LINEAR      = 1,
        ANISOTROPIC = 2
    };

    enum class ERDepthStencilState
    {
        LESS     = 0,
        GREATER  = 1,
        NO_WRITE = 2,
        DISABLE  = 3
    };

    class EasyRender
    {
    private:
        ComPtr<ID3D11VertexShader>   m_vsShader;
        ComPtr<ID3D11PixelShader>    m_psShader;
        ComPtr<ID3D11GeometryShader> m_gsShader;
        ComPtr<ID3D11ComputeShader>  m_computeShader;


    public:
        static void Begin();
        static void End();

        void Draw();

        // void DrawInstance()
    };
}  // namespace HBSoft
