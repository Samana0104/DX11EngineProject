/*
author : 변한빛
description : 렌더링 추상화를 위한 헤더 파일

version: 1.0.0
date: 2024-12-16
*/

#pragma once

#include "Core.h"
#include "Shader/VertexShader.h"
#include "Shader/PixelShader.h"

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
        Alpha = 0,
        Merge = 1,
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

    enum class ERBeginState
    {
        DEFAULT = 0,  // 설정 값을 디폴트로 바꿔버림
        HOLD    = 1   // 현재 설정 값을 유지함
    };

    enum class ERTopology
    {
        POINT_LIST     = 0,
        LINE_LIST      = 1,
        LINE_STRIP     = 2,
        TRIANGLE_LIST  = 3,
        TRIANGLE_STRIP = 4
    };

    class EasyRender
    {
    private:
        std::shared_ptr<Shader>  m_vsShader;
        std::shared_ptr<Shader>  m_psShader;
        std::shared_ptr<Shader>  m_gsShader;
        std::shared_ptr<Texture> m_texture;
        std::shared_ptr<Mesh>    m_mesh;

        std::vector<ComPtr<ID3D11Buffer>> m_vsCB;
        std::vector<ComPtr<ID3D11Buffer>> m_psCB;
        std::vector<ComPtr<ID3D11Buffer>> m_gsCB;

        ERRasterRizerState  m_rrs;
        ERDepthStencilState m_dss;
        ERBlendingState     m_bs;
        ERSamplerState      m_ss;
        ERTopology          m_topology;

        inline static bool m_isWireFrame = false;

    private:
        void InitShaderState();
        void InitShaderCBState();
        void SetRRSFromDevice();
        void SetDSSFromDevice();
        void SetBSFromDevice();
        void SetSSFromDevice();
        void SetTopologyFromDevice();
        void DrawMesh();

    public:
        EasyRender();
        ~EasyRender() = default;


        void SetVSShader(const SHADER_KEY shaderKey);
        void SetPSShader(const SHADER_KEY shaderKey);
        void SetGSShader(const SHADER_KEY shaderKey);
        void SetRRS(ERRasterRizerState rrs);
        void SetDSS(ERDepthStencilState dss);
        void SetBS(ERBlendingState bs);
        void SetSS(ERSamplerState ss);
        void SetTopology(ERTopology topology);
        void SetMesh(std::shared_ptr<Mesh> mesh);
        void SetTexture(std::shared_ptr<Texture> texture);
        void SetEntireState();

        void Draw();
        void DrawNormal();
        void DrawAnimationNormal();

        void UpdateVSCB(const void* data, const size_t dataSize, const UINT constantIdx);
        void UpdatePSCB(const void* data, const size_t dataSize, const UINT constantIdx);
        void UpdateGSCB(const void* data, const size_t dataSize, const UINT constantIdx);

        static void Begin(MultiRT renderTarget);
        static void End();
        static void MergeRenderTarget(MultiRT dst, MultiRT src);
        static void SaveScreenShot(MultiRT renderTarget, std::wstring fileName);
        static void SetWireFrame(bool isWire);

        // void DrawInstance()
    };
}  // namespace HBSoft
