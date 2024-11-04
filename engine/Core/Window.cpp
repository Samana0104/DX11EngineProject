#include "pch.h"
#include "Window.h"
using namespace HBSoft;

void Window::CreateRegisterClass(HINSTANCE _hInstance)
{
    WNDCLASS wc    = {};
    wc.lpfnWndProc = [](HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) -> LRESULT
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

            Window::m_windowSize.x = rc.right;
            Window::m_windowSize.y = rc.bottom;

            return 0;
        }
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    };

    wc.hInstance     = _hInstance;
    wc.lpszClassName = MY_Window_CLASS_NAME;
    RegisterClass(&wc);
}

bool Window::CreateWin(LONG _width, LONG _height)
{
    m_windowSize = {_width, _height};
    RECT rt {0, 0, _width, _height};

    CreateRegisterClass(m_hinstance);
    AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, FALSE);

    HWND hwnd = CreateWindowEx(
    0,  // Optional Window styles.
    MY_Window_CLASS_NAME,
    MY_Window_NAME,
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

    if (hwnd == NULL)
        return false;

    m_hwnd = hwnd;
    ShowWindow(hwnd, SW_SHOW);

    return true;
}

bool Window::WindowRun() const
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

void Window::SetHinstance(HINSTANCE _hinstance)
{
    m_hinstance = _hinstance;
}

POINT Window::GetWindowSize() const
{
    return m_windowSize;
}

POINTFLOAT Window::GetWindowSizeF() const
{
    return {static_cast<FLOAT>(m_windowSize.x), static_cast<FLOAT>(m_windowSize.y)};
}

glm::vec2 Window::GetWindowSizeVec2() const
{
    return {static_cast<FLOAT>(m_windowSize.x), static_cast<FLOAT>(m_windowSize.y)};
}

HWND Window::GetWindowHandle() const
{
    return m_hwnd;
}
