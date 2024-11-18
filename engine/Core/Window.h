/*
author : 변한빛
description : 윈도우 관련 헤더 파일

version: 1.0.0
date: 2024-11-05
*/

#pragma once
#include "Windows.h"
#include "HPoint.h"

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam,
                                                             LPARAM lParam);

namespace HBSoft
{
#define WINDOW_NAME       L"Untitled Goose"
#define WINDOW_CLASS_NAME L"HBSOFT_WINDOW"

    class Window
    {
    private:
        inline static bool   m_isActivate = false;
        inline static HPoint m_windowSize;

        HINSTANCE m_hinstance;
        HWND      m_hwnd;

    private:
        void CreateRegisterClass();
        bool Create();

    public:
        Window(HINSTANCE hinstance, HPoint windowSize);
        bool Run() const;
        bool IsActivate() const;

        HPoint GetSize() const;
        HWND   GetHandle() const;

        static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
    };
}  // namespace HBSoft
