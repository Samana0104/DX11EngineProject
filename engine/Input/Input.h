#pragma once
#include "pch.h"

namespace HBSoft
{
    // enum class MouseState
    //{
    //	DEFAULT = 0,  // 커서가 위에 없을 때(T_FOCUS상태에서 다른 곳을 T_ACTIVE하면 전환된다.)
    //	HOVER = 1,	// 커서가 위에 있을 때
    //	FOCUS = 2,	// T_ACTIVE상태에서 왼쪽 버튼을 다른 곳에서 놓았을 때(취소)
    //	ACTIVE = 3,	// 마우스 왼쪽 버튼 누르고 있을 때
    //	SELECTED = 4, // T_ACTIVE 상태에서 왼쪽버튼 놓았을 때
    // };

    enum class KeyState
    {
        KEY_FREE = 0,
        KEY_UP,
        KEY_DOWN,
        KEY_HOLD
    };

    class Input : public Singleton<Input>
    {
    private:
        inline static const UINT  KEY_COUNT   = 256;
        inline static const SHORT PRESSED_KEY = static_cast<SHORT>(0x8000);

        KeyState m_keyState[KEY_COUNT];

        POINT_L m_mousePos    = {0, 0};
        POINT_L m_preMousePos = {0, 0};

    protected:
        Window& m_window = Window::GetInstance();

    private:
        friend class Singleton<Input>;
        Input();

        void UpdateKeyState(UINT _key);

        void SetKeyUp(const UINT _key);
        void SetKeyDown(const UINT _key);
        void SetKeyFree(const UINT _key);
        void SetKeyHold(const UINT _key);

    public:
        KeyState GetKeyState(const UINT _key) const;
        POINT_L  GetMousePos() const;
        POINT_F  GetMousePosF() const;
        vec2     GetMousePosVec2() const;

        bool IsKeyUp(const UINT key) const;
        bool IsKeyDown(const UINT key) const;
        bool IsKeyFree(const UINT key) const;
        bool IsKeyHold(const UINT key) const;
        bool IsKeyPressed(const SHORT key) const;

        void Update();
    };
}  // namespace HBSoft
