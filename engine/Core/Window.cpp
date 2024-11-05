/*
author : ���Ѻ�
description : ������ ���� Ŭ���� �ҽ� ����

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
    assert(CreateWin());
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

bool Window::CreateWin()
{
    RECT rt {0, 0, static_cast<float>(m_windowSize.x), static_cast<float>(m_windowSize.y)};
    AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, FALSE);

    HWND hwnd = CreateWindowEx(
    0,  // Optional Window styles.
    WINDOW_CLASS_NAME,
    WINDOW_NAME,
    WS_OVERLAPPEDWINDOW,                                           // Window style
    GetSystemMetrics(SM_CXSCREEN) / 2 - (rt.right - rt.left) / 2,  // ���� �߾ӿ� ������ ����
    GetSystemMetrics(SM_CYSCREEN) / 2 - (rt.bottom - rt.top) / 2,  // �ϴ� ���� 45px
    rt.right - rt.left,
    rt.bottom - rt.top,
    NULL,         // Parent Window
    NULL,         // Menu
    m_hinstance,  // Instance handle
    NULL          // Additional application data
    );

    if (hwnd == NULL)
        return false;

    m_hwnd = hwnd;
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

        Window::m_windowSize = HPoint(static_cast<float>(rc.right), static_cast<float>(rc.bottom));
        return 0;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
