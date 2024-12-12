/*
author : 변한빛
description : 게임 타이틀 씬 헤더 파일

version: 1.0.0
date: 2024-11-30
*/


#pragma once

#include "Scene.h"
#include "Camera.h"
#include "Button.h"
#include "LobbyButton.h"
#include "2D/MainTitle.h"

namespace HBSoft
{
    class SceneLobby : public Scene
    {
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
