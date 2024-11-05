/*
author : 변한빛
description : 윈도우 관련 헤더 파일

version: 1.0.0
date: 2024-11-05
*/

#pragma once
#include "pch.h"

namespace HBSoft
{
#define WINDOW_NAME       L"Untitled Goose"
#define WINDOW_CLASS_NAME L"HBSOFT_WINDOW"

    using CALLBACK_ID  = UINT;
    using Wm_size_FUNC = std::function<void(UINT, UINT)>;

    class Window
    {
    private:
        inline static bool   m_isActivate = false;
        inline static HPoint m_windowSize = {0.f, 0.f};

        CALLBACK_ID                         m_registerCallbackID = 0;
        std::map<CALLBACK_ID, Wm_size_FUNC> m_callbackWm_size;

        HINSTANCE m_hinstance;
        HWND      m_hwnd;

    private:
        void CreateRegisterClass();
        bool CreateWin();

    public:
        void Init(HINSTANCE hinstance, HPoint windowSize);
        bool Run() const;
        bool IsActivate() const;

        HPoint GetSize() const;
        HWND   GetHandle() const;

        static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
    };
}  // namespace HBSoft
