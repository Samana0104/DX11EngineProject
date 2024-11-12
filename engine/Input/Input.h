/*
author : ���Ѻ�
description : ��ǲ ó���� ���� ��� ����

version: 1.0.0
date: 2024-11-04
*/

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

    class Input
    {
    private:
        inline static const UINT  KEY_COUNT   = 256;
        inline static const SHORT PRESSED_KEY = static_cast<SHORT>(0x8000);

        std::shared_ptr<Window> m_window;

        KeyState m_keyState[KEY_COUNT];
        HPoint   m_mousePos      = {0, 0};
        HPoint   m_mouseDeltaPos = {0, 0};

        bool m_isDrag = false;

    private:
        void UpdateKeyState(UINT key);

        void SetKeyUp(const UINT key);
        void SetKeyDown(const UINT key);
        void SetKeyFree(const UINT key);
        void SetKeyHold(const UINT key);

    public:
        Input(std::shared_ptr<Window>& window);

        KeyState      GetKeyState(const UINT key) const;
        const HPoint& GetMousePos() const;
        const HPoint& GetDeltaMousePos() const;

        bool IsKeyUp(const UINT key) const;
        bool IsKeyDown(const UINT key) const;
        bool IsKeyFree(const UINT key) const;
        bool IsKeyHold(const UINT key) const;
        bool IsKeyPressed(const SHORT key) const;

        void Update();
    };
}  // namespace HBSoft
