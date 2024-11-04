#pragma once
#include "Object2D.h"

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
