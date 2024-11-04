#pragma once
#include "Object2D.h"

namespace HBSoft
{
    enum SelectState
    {
        DEFAULT = 0,  // 커서가 위에 없을 때(T_FOCUS상태에서 다른 곳을 T_ACTIVE하면 전환된다.)
        HOVER    = 1,  // 커서가 위에 있을 때
        FOCUS    = 2,  // T_ACTIVE상태에서 왼쪽 버튼을 다른 곳에서 놓았을 때(취소)
        ACTIVE   = 3,  // 마우스 왼쪽 버튼 누르고 있을 때
        SELECTED = 4,  // T_ACTIVE 상태에서 왼쪽버튼 놓았을 때
    };

    class Button : public Object2D
    {
    private:
        SelectState m_state = SelectState::DEFAULT;

        bool m_isMovable = false;
        bool m_isDisable = true;

    protected:
        virtual void SetDefaultMode();
        virtual void SetHoverMode();
        virtual void SetFocusMode();
        virtual void SetActiveMode();
        virtual void SetSelectedMode();

    public:
        Button();
        virtual ~Button();

        SelectState GetState() const;
        void        SetState(SelectState state);
        void        SetMovable(bool isMovable);
        void        SetDisable(bool isDisable);

        virtual void Update(const float _deltaTime) override;
        virtual void Render() override;
    };
}  // namespace HBSoft
