/*
author : 변한빛
description : 인풋 처리를 위한 헤더 파일

version: 1.0.0
date: 2024-11-04
*/

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
