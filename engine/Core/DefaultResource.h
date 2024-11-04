#pragma once
#include "Font.h"
#include "Mesh2D.h"
#include "Shader.h"

namespace HBSoft
{
    /*
        struct FontDesc
        {
            std::wstring m_fontName;
            std::wstring m_fontLocalName;
            FLOAT		 m_fontSize;

            DWRITE_FONT_WEIGHT	m_fontWeight;
            DWRITE_FONT_STYLE	m_fontStyle;
            DWRITE_FONT_STRETCH m_fontStretch;
        };
    */
    inline static const std::vector<std::wstring> g_fontPath = {{L"../res/Font/"}};

    // 폰트는 직접 추가해서 써야함 크기 차이도 있고 위에는 단순 폰트 메모리에 올려주는 거 뿐
    inline static const std::map<FONT_KEY, FontDesc> g_defaultFonts = {
        {L"DEBUG_FONT",
         {L"맑은 고딕",
         L"ko-kr",
         20.f,
         DWRITE_FONT_WEIGHT_THIN,
         DWRITE_FONT_STYLE_NORMAL,
         DWRITE_FONT_STRETCH_NORMAL}},
    };

    /*
        enum class MeshShape
        {
            CUSTOM = 0, 이 기능은 3D때 구현 예정
            BOX = 1,
            SPEHERE = 2
        };
    */
    // 만약 UV값을 따로 주고 싶으면 메쉬 따로 추가해서 넣을 것
    inline static const std::map<MESH_KEY, MeshShape> g_defaultMeshes = {
        { L"DEFAULT_MESH",    {MeshShape::BOX2D}},
        {   L"BOX2D_MESH",    {MeshShape::BOX2D}},
        {L"CIRCLE2D_MESH", {MeshShape::CIRCLE2D}}
    };


    // using TexturePath = std::wstring;
    // inline static const std::vector<TexturePath> gDefaultTextures = {
    //	{ L"../data/KGCA1.png"},
    //	{ L"../data/Default.jpg"}
    // };

    inline static const std::vector<std::wstring> g_texturePath = {{L"../res/Image/"}};

    /*
        struct ShaderDesc
        {
            ShaderType		m_shaderType;
            std::wstring	m_shaderPath;
            std::string		m_shaderEntry;
        };
    */

    inline static const std::vector<ShaderDesc> g_defaultShaders = {
        {ShaderType::VERTEX, L"../res/Shader/VertexShader.hlsl", "VSMain"},
        { ShaderType::PIXEL,  L"../res/Shader/PixelShader.hlsl", "PSMain"}
    };

    inline static const std::vector<std::wstring> g_soundPath = {{L"../res/Sound/"}};
}  // namespace HBSoft
