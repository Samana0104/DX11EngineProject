/*
author :  정찬빈
description : 거위의 움직임을 테스트 하기 위한 헤더 파일

version: 1.0.0
date: 2024-11-22
*/


#pragma once

#include "Scene.h"
#include "3D/Goose.h"
#include "Camera.h"
#include "Button.h"

namespace HBSoft
{
    class SceneGame : public Scene
    {
    public:
        Camera camera;

        bool isWire = false;

    public:
        SceneGame();
        virtual void Update(float deltaTime);
        virtual void Render() override;
        virtual void Release() override;
        virtual void Start() override;
        virtual void End() override;
    };

}  // namespace HBSoft
