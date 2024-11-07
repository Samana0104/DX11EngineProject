/*
author : ���Ѻ�
description :
HBSoft ���� �Լ��� ��
�⺻ �ڷ��� Ÿ�� ���泻�� ����

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

    // ���� �̸����� Ű ���� �޾ƿ��⿡ �� 3���� wstring���� ���� ���ϸ� ū��
    using MESH_KEY  = std::wstring;
    using FONT_KEY  = std::wstring;
    using SCENE_KEY = std::wstring;

    // ���� �̸����� Ű ���� �޾ƿ��⿡ �� 4���� wstring���� ���� ���ϸ� ū��
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