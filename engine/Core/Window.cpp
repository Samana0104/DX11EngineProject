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
            Window::GetInstance().CallEventWMActivate(hwnd, uMsg, wParam, lParam);
            return 0;

        case WM_DESTROY:
            Window::GetInstance().CallEventWMDestroy(hwnd, uMsg, wParam, lParam);
            return 0;

        case WM_SIZE:
            Window::GetInstance().CallEventWm_size(hwnd, uMsg, wParam, lParam);
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

void Window::CallEventWMActivate(HWND _hwnd, UINT _uMsg, WPARAM _wParam, LPARAM _lParam)
{
    if (LOWORD(_wParam) == WA_INACTIVE)
        Window::m_isActivate = false;
    else
        Window::m_isActivate = true;
}

void Window::CallEventWMDestroy(HWND _hwnd, UINT _uMsg, WPARAM _wParam, LPARAM _lParam)
{
    PostQuitMessage(0);
}

void Window::CallEventWm_size(HWND _hwnd, UINT _uMsg, WPARAM _wParam, LPARAM _lParam)
{
    RECT rc;

    GetClientRect(_hwnd, &rc);

    Window::m_windowSize.x = rc.right;
    Window::m_windowSize.y = rc.bottom;

    for (auto& obj : m_callbackWm_size)
        obj.second(Window::m_windowSize.x, Window::m_windowSize.y);
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

CALLBACK_ID Window::RegisterCallBackWm_size(Wm_size_FUNC _func)
{
    m_registerCallbackID++;
    m_callbackWm_size.insert(std::make_pair(m_registerCallbackID, _func));
    return m_registerCallbackID;
}

bool Window::DeleteCallBack(CALLBACK_ID _id)
{
    if (m_callbackWm_size.contains(_id))
    {
        m_callbackWm_size.erase(_id);
        return true;
    }
    else
    {
        MessageBoxA(NULL, "Not existed event id[id Error]", "[WM Size event]", MB_OK);
        return false;
    }
}
