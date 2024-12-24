/*
author : ���Ѻ�
description : ���ҽ��� ��� �ۼ��� ���� ����

version: 1.0.0
date: 2024-11-04
*/

#pragma once
#include "Font/Font.h"
#include "Mesh/Mesh.h"
#include "Shader/Shader.h"

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

    inline static const std::map<SHADER_KEY, ShaderType> g_defaultShaders = {
        {    L"BasicVS.hlsl",   ShaderType::VERTEX},
        { L"BasicAniVS.hlsl",   ShaderType::VERTEX},
        {    L"BasicPS.hlsl",    ShaderType::PIXEL},
        {    L"LinePS.hlsl ",    ShaderType::PIXEL},
        {     L"LineVS.hlsl",   ShaderType::VERTEX},
        {     L"CubeVS.hlsl",   ShaderType::VERTEX},
        {     L"CubePS.hlsl",    ShaderType::PIXEL},
        {    L"ColorPS.hlsl",    ShaderType::PIXEL},
        {  L"2DBasicVS.hlsl",   ShaderType::VERTEX},
        {    L"MergeVS.hlsl",   ShaderType::VERTEX},
        {   L"MergePS.hlsl ",    ShaderType::PIXEL},
        {   L"NormalGS.hlsl", ShaderType::GEOMETRY},
        {   L"NormalVS.hlsl",   ShaderType::VERTEX},
        {L"NormalAniVS.hlsl",   ShaderType::VERTEX}
    };
}  // namespace HBSoft
