#pragma once
#include "CoreAPI.h"
#include "Window.h"

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

    using MOUSE_FLAGS      = UINT;
    using ONMOUSEMOVE_FUNC = std::function<void(POINT_L, POINT_L)>;
    using ONMOUSEPUSH_FUNC = std::function<void(vec2, MOUSE_FLAGS)>;
    using ONMOUSEUP_FUNC   = std::function<void(vec2, MOUSE_FLAGS)>;

    class Input : public Singleton<Input>
    {
    private:
        inline static const UINT  KEY_COUNT   = 256;
        inline static const SHORT PRESSED_KEY = static_cast<SHORT>(0x8000);

        CALLBACK_ID                             m_registerCallbackID = 0;
        std::map<CALLBACK_ID, ONMOUSEMOVE_FUNC> m_callbackOnMouseMove;
        std::map<CALLBACK_ID, ONMOUSEPUSH_FUNC> m_callbackOnMousePush;
        std::map<CALLBACK_ID, ONMOUSEUP_FUNC>   m_callbackOnMouseUP;

        KeyState m_currentKeyState[KEY_COUNT];

        POINT_L m_mousePos    = {0, 0};
        POINT_L m_preMousePos = {0, 0};

    protected:
        Window& mWindow = Window::GetInstance();

    private:
        friend class Singleton<Input>;
        Input();

        void UpdateKeyState(UINT _key);

        void SetKeyUp(const UINT _key);
        void SetKeyDown(const UINT _key);
        void SetKeyFree(const UINT _key);
        void SetKeyHold(const UINT _key);

        void CallEventOnMouseMove();
        void CallEventOnMousePush(MOUSE_FLAGS _mouseFlags);
        void CallEventOnMouseUP(MOUSE_FLAGS _mouseFlags);
        bool DeleteCallbackMouseMove(CALLBACK_ID _id);
        bool DeleteCallbackMousePush(CALLBACK_ID _id);
        bool DeleteCallbackMouseUP(CALLBACK_ID _id);

        void CheckMouseMove();
        void CheckMousePush();
        void CheckMouseUP();

    public:
        KeyState GetCurrentKeyState(const UINT _key) const;
        POINT_L  GetCurrentMousePos() const;
        POINT_F  GetCurrentMousePosF() const;
        vec2     GetCurrentMousePosVec2() const;

        KeyState GetLBState() const;
        KeyState GetRBState() const;
        KeyState GetMBState() const;

        bool IsKeyUp(const UINT key) const;
        bool IsKeyDown(const UINT key) const;
        bool IsKeyFree(const UINT key) const;
        bool IsKeyHold(const UINT key) const;
        bool IsKeyPressed(const SHORT key) const;

        CALLBACK_ID RegisterCallBackOnMouseMove(ONMOUSEMOVE_FUNC func);
        CALLBACK_ID RegisterCallBackOnMousePush(ONMOUSEPUSH_FUNC func);
        CALLBACK_ID RegisterCallBackOnMouseUP(ONMOUSEUP_FUNC func);
        bool        DeleteCallBack(CALLBACK_ID _id);

        void Update();
    };
}  // namespace HBSoft
