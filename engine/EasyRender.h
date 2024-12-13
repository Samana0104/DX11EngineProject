#pragma once

#include "Core/Core.h"

namespace HBSoft
{
    // ���� �� �𸣸� ������ 0�� ��������

    enum class RasterRizerState
    {
        SOLID_BACK_FACE = 0,
        SOLID_NO_CULL   = 1,
        WIRE_BACK_FACE  = 2,
        WIRE_NO_CULL    = 3,
    };

    enum class BlendingState
    {
        DEFAULT     = 0,
        DUAL_SOURCE = 1
    };

    enum class DepthStencilState
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
        static void Begin();

        void Draw();

        // void DrawInstance()
    };
}  // namespace HBSoft