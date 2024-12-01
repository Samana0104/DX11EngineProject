/*
author : 정찬빈, 변한빛
description : 게임 타이틀 씬 헤더 파일

version: 1.0.0
date: 2024-11-30
*/


#pragma once

#include "Scene.h"
#include "Camera.h"
#include "MainButton.h"
#include "2D/MainTitle.h"
#include "MainButton.h"

namespace HBSoft
{
    class SceneLobby : public Scene
    {
    public:
        MainTitle  m_title;
        MainButton m_button;
        bool       isWire = false;

    public:
        SceneLobby();
        virtual void Update(float deltaTime);
        virtual void Render() override;
        virtual void Release() override;
        virtual void Start() override;
        virtual void End() override;
    };

}  // namespace HBSoft
