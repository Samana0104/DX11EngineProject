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

    // ��Ʈ�� ���� �߰��ؼ� ����� ũ�� ���̵� �ְ� ������ �ܼ� ��Ʈ �޸𸮿� �÷��ִ� �� ��
    inline static const std::map<FONT_KEY, FontDesc> g_defaultFonts = {
        {L"DEBUG_FONT",
         {L"���� ���",
         L"ko-kr",
         20.f,
         DWRITE_FONT_WEIGHT_THIN,
         DWRITE_FONT_STYLE_NORMAL,
         DWRITE_FONT_STRETCH_NORMAL}},
    };

    /*
        enum class MeshShape
        {
            CUSTOM = 0, �� ����� 3D�� ���� ����
            BOX = 1,
            SPEHERE = 2
        };
    */
    // ���� UV���� ���� �ְ� ������ �޽� ���� �߰��ؼ� ���� ��
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
