#pragma once
#include "pch.h"

namespace HBSoft
{
    // enum class MouseState
    //{
    //	DEFAULT = 0,  // Ŀ���� ���� ���� ��(T_FOCUS���¿��� �ٸ� ���� T_ACTIVE�ϸ� ��ȯ�ȴ�.)
    //	HOVER = 1,	// Ŀ���� ���� ���� ��
    //	FOCUS = 2,	// T_ACTIVE���¿��� ���� ��ư�� �ٸ� ������ ������ ��(���)
    //	ACTIVE = 3,	// ���콺 ���� ��ư ������ ���� ��
    //	SELECTED = 4, // T_ACTIVE ���¿��� ���ʹ�ư ������ ��
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
