#pragma once
#include "pch.h"

namespace HBSoft
{
#define MY_Window_NAME       L"Untitled Goose"
#define MY_Window_CLASS_NAME L"HBSOFT_WINDOW"

    using CALLBACK_ID  = UINT;
    using Wm_size_FUNC = std::function<void(UINT, UINT)>;

    class Window : public Singleton<Window>
    {
    private:
        inline static bool  m_isActivate = false;
        inline static POINT m_windowSize = {0, 0};

        CALLBACK_ID                         m_registerCallbackID = 0;
        std::map<CALLBACK_ID, Wm_size_FUNC> m_callbackWm_size;

        HINSTANCE m_hinstance;
        HWND      m_hwnd;

    private:
        friend class Singleton<Window>;
        Window() = default;

        void CreateRegisterClass(HINSTANCE hInstance);

    public:
        bool CreateWin(LONG width, LONG height);
        bool WindowRun() const;
        bool IsActivate() const;

        void SetHinstance(HINSTANCE hinstance);

        POINT      GetWindowSize() const;
        POINTFLOAT GetWindowSizeF() const;
        glm::vec2  GetWindowSizeVec2() const;
        HWND       GetWindowHandle() const;
    };
}  // namespace HBSoft
