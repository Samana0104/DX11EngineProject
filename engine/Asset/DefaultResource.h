/*
author : 변한빛
description : 리소스의 경로 작성을 위한 파일

version: 1.0.0
date: 2024-11-04
*/

#pragma once
#include "Font/Font.h"
#include "Mesh/Mesh.h"
#include "Shader/Shader.h"

namespace HBSoft
{
    inline static const std::wstring g_defaultPath = L"../res/";  // 건들지 말 것

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

    // 폰트는 직접 추가해서 써야함 크기 차이도 있고
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

    // 기본 메쉬
    inline static const std::map<MESH_KEY, MeshShape> g_defaultMeshes = {
        {  L"BOX2D",   {MeshShape::BOX2D}},
        {  L"BOX3D",   {MeshShape::BOX3D}},
        { L"CIRCLE",  {MeshShape::CIRCLE}},
        {   L"LINE",    {MeshShape::LINE}},
        {L"CUBEMAP", {MeshShape::CUBEMAP}}
    };

    /*
            struct ShaderType
            {
                ShaderType		m_shaderType;
                std::string		m_shaderEntry;
            };
    */

}  // namespace HBSoft
