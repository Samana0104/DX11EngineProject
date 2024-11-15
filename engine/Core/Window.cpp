/*
author : 변한빛
description : 윈도우 관련 클래스 소스 파일

version: 1.1.0
date: 2024-11-05
*/

#include "pch.h"
#include "Window.h"
using namespace HBSoft;

Window::Window(HINSTANCE hinstance, HPoint windowSize)
{
    m_windowSize = windowSize;

    CreateRegisterClass();
    assert(Create());
}

void Window::CreateRegisterClass()
{
    WNDCLASS wc;
    ZeroMemory(&wc, sizeof(wc));
    {
        wc.lpfnWndProc   = Window::WindowProc;
        wc.hInstance     = m_hinstance;
        wc.lpszClassName = WINDOW_CLASS_NAME;
    }
    RegisterClass(&wc);
}

bool Window::Create()
{
    RECT rt {0, 0, static_cast<LONG>(m_windowSize.x), static_cast<LONG>(m_windowSize.y)};

    AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, FALSE);

    HWND hwnd = CreateWindowEx(
    0,  // Optional Window styles.
    WINDOW_CLASS_NAME,
    WINDOW_NAME,
    WS_OVERLAPPEDWINDOW,                                           // Window style
    GetSystemMetrics(SM_CXSCREEN) / 2 - (rt.right - rt.left) / 2,  // 영역 중앙에 윈도우 생성
    GetSystemMetrics(SM_CYSCREEN) / 2 - (rt.bottom - rt.top) / 2,  // 하단 영역 45px
    rt.right - rt.left,
    rt.bottom - rt.top,
    NULL,         // Parent Window
    NULL,         // Menu
    m_hinstance,  // Instance handle
    NULL          // Additional application data
    );

    if (m_hwnd == NULL)
        return false;

    m_hwnd = hwnd;
    GetClientRect(m_hwnd, &rt);
    m_windowSize = HPoint(rt.right, rt.bottom);

    ShowWindow(hwnd, SW_SHOW);

    return true;
}

bool Window::Run() const
{
    MSG msg = {};
    while (WM_QUIT != msg.message)
    {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            return true;
        }
    }
    return false;
}

bool Window::IsActivate() const
{
    return m_isActivate;
}

HPoint Window::GetSize() const
{
    return m_windowSize;
}

HWND Window::GetHandle() const
{
    return m_hwnd;
}

LRESULT Window::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    ImGui_ImplWin32_WndProcHandler(hwnd, uMsg, wParam, lParam);

    switch (uMsg)
    {
    case WM_ACTIVATE:
        if (LOWORD(wParam) == WA_INACTIVE)
            Window::m_isActivate = false;
        else
            Window::m_isActivate = true;
        return 0;

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    case WM_SIZE:
        RECT rc;
        GetClientRect(hwnd, &rc);
        Window::m_windowSize = HPoint(rc.right, rc.bottom);
        EventHandler::GetInstance().Notify(EventList::WINDOW_RESIZE);
        return 0;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
