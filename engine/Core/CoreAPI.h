/*
author : 변한빛
description :
HBSoft 전역 함수들 및
기본 자료형 타입 변경내역 모음

version: 1.0.0
date: 2024-11-04
*/

#pragma once
#include "pch.h"

namespace HBSoft
{
    using COLOR_F = D2D1_COLOR_F;

    using stringV  = std::string_view;
    using wstringV = std::wstring_view;

    // 파일 이름으로 키 값을 받아오기에 이 3개는 wstring으로 선언 안하면 큰일
    using MESH_KEY  = std::wstring;
    using FONT_KEY  = std::wstring;
    using SCENE_KEY = std::wstring;

    // 파일 이름으로 키 값을 받아오기에 이 4개는 wstring으로 선언 안하면 큰일
    using SHADER_KEY  = std::wstring;
    using TEXTURE_KEY = std::wstring;
    using SOUND_KEY   = std::wstring;
    using SPRITE_KEY  = std::wstring;

    const float TOLERANCE = 1e-4f;

    static std::wstring ToUnicode(const stringV _src)
    {
        USES_CONVERSION;
        return std::wstring(A2W(_src.data()));
    }

    static std::string ToMultiByte(const wstringV _src)
    {
        USES_CONVERSION;
        return std::string(W2A(_src.data()));
    }

    static std::pair<std::wstring, std::wstring> GetFileNameAndExt(const wstringV filePath)
    {
        wchar_t szDrive[MAX_PATH] = {
            0,
        };
        wchar_t szDir[MAX_PATH] = {
            0,
        };
        wchar_t szFileName[MAX_PATH] = {
            0,
        };
        wchar_t szFileExt[MAX_PATH] = {
            0,
        };
        _tsplitpath_s(filePath.data(), szDrive, szDir, szFileName, szFileExt);
        // fileNameKey = szFileName;
        // fileNameKey += szFileExt;

        return std::make_pair(szFileName, szFileExt);
    }
}  // namespace HBSoft