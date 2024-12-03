#pragma once

#include "Button.h"
#include "Renderable.h"

namespace HBSoft
{
    class LobbyButton : public Renderable
    {
    private:
        Button m_startBtn;
        Button m_endBtn;
        Button m_optionBtn;

    private:
        void SetStartBtn();
        void SetEndBtn();
        void SetOptionBtn();

    public:
        LobbyButton();

        virtual void Init();
        virtual void Release();
        virtual void Update(const float deltaTime);
        virtual void Render();
    };
}  // namespace HBSoft
