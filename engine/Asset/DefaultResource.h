/*
author : ���Ѻ�
description : ���ҽ��� ��� �ۼ��� ���� ����

version: 1.0.0
date: 2024-11-04
*/

#pragma once
#include "Font.h"
#include "Mesh.h"
#include "Shader.h"

namespace HBSoft
{
    inline static const std::wstring g_defaultPath = L"../res/";  // �ǵ��� �� ��

    /*
        struct FontDesc
        {
            std::wstring m_fontName;
            std::wstring m_fontLocaleName;
            FLOAT		 m_fontSize;

            DWRITE_FONT_WEIGHT	m_fontWeight;
            DWRITE_FONT_STYLE	m_fontStyle;
            DWRITE_FONT_STRETCH m_fontStretch;
        };
    */

    // ��Ʈ�� ���� �߰��ؼ� ����� ũ�� ���̵� �ְ�
    inline static const std::map<FONT_KEY, FontDesc> g_defaultFonts = {
        {L"DEBUG_FONT",
         {L"malgun",
         L"ko-kr",
         20.f,
         DWRITE_FONT_WEIGHT_THIN,
         DWRITE_FONT_STYLE_NORMAL,
         DWRITE_FONT_STRETCH_NORMAL}},
    };

    /*
        enum class MeshShape
        {
            BOX = 1,
            SPEHERE = 2
        };
    */

    // �⺻ �޽�
    inline static const std::map<MESH_KEY, MeshShape> g_defaultMeshes = {
        {   L"BOX2D_MESH",    {MeshShape::BOX2D}},
        {L"CIRCLE2D_MESH", {MeshShape::CIRCLE2D}}
    };

    /*
            struct ShaderDesc
            {
                ShaderType		m_shaderType;
                std::string		m_shaderEntry;
            };
    */

    inline static const std::map<SHADER_KEY, ShaderDesc> g_defaultShaders = {
        {L"VertexShader.hlsl", {ShaderType::VERTEX, "VSMain"}},
        { L"PixelShader.hlsl",  {ShaderType::PIXEL, "PSMain"}}
    };
}  // namespace HBSoft
