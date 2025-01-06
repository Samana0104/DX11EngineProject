/*
author : ���Ѻ�, ������
description : ���� Ÿ��Ʋ �� ��� ����
              v1.0.1 : BGM �߰� (������)

version: 1.0.1
date: 2024-11-30
*/


#pragma once

#include "Scene.h"
#include "Camera/Camera.h"
#include "Button.h"
#include "LobbyButton.h"
#include "2D/MainTitle.h"
#include "Sound/HSound.h"

namespace HBSoft
{
    class SceneLobby : public Scene
    {
    private:
        std::shared_ptr<HSound> m_lobbyBGM;

    public:
        MainTitle   m_title;
        LobbyButton m_lobbyBtn;
        bool        isWire = false;

    public:
        SceneLobby();
        virtual void Update(float deltaTime);
        virtual void Render() override;
        virtual void Release() override;
        virtual void Start() override;
        virtual void End() override;
    };

}  // namespace HBSoft
