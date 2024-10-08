#pragma once
#include "Object2D.h"
#include "CollisionComponent.h"

namespace HBSoft
{
    enum SelectState
    {
        DEFAULT = 0,  // Ŀ���� ���� ���� ��(T_FOCUS���¿��� �ٸ� ���� T_ACTIVE�ϸ� ��ȯ�ȴ�.)
        HOVER    = 1,  // Ŀ���� ���� ���� ��
        FOCUS    = 2,  // T_ACTIVE���¿��� ���� ��ư�� �ٸ� ������ ������ ��(���)
        ACTIVE   = 3,  // ���콺 ���� ��ư ������ ���� ��
        SELECTED = 4,  // T_ACTIVE ���¿��� ���ʹ�ư ������ ��
    };

    class Button : public Object2D
    {
    private:
        SelectState m_currentState = SelectState::DEFAULT;

        bool m_isMovable = false;
        bool m_isDisable = true;

        CALLBACK_ID m_onMouseMoveID;
        CALLBACK_ID m_onMousePushID;
        CALLBACK_ID m_onMouseUpID;

        std::function<void()> mCallSelectedBtn;

    private:
        virtual void OnMouseMove(POINT_L _prePos, POINT_L _postPos);
        virtual void OnMousePush(vec2 _pos, MOUSE_FLAGS _flag);
        virtual void OnMouseUp(vec2 _pos, MOUSE_FLAGS _flag);

    protected:
        virtual void SetDefaultMode();
        virtual void SetHoverMode();
        virtual void SetFocusMode();
        virtual void SetActiveMode();
        virtual void SetSelectedMode();

    public:
        Button();
        virtual ~Button();

        SelectState GetCurrentState() const;
        void        SetCurrentState(SelectState _state);
        void        SetMovable(bool _isMovable);
        void        SetDisable(bool _isDisable);
        void        SetSelectedBtn(std::function<void()> _func);

        virtual void Update(const float _deltaTime) override;
        virtual void Render() override;
    };
}  // namespace HBSoft
