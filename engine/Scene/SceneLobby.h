/*
author : 변한빛
description : 씬의 전환을 테스트 하기 위한 헤더 파일

version: 1.0.0
date: 2024-11-04
*/

#pragma once
#include "Scene.h"
#include "Camera.h"
#include "Object3D.h"

namespace HBSoft
{
    class SceneLobby : public Scene
    {
    public:
        Object3D test;


    public:
        SceneLobby();

        virtual void Update(float deltaTime) override;
        virtual void Render() override;
        virtual void Release() override;
        virtual void Reset() override;
        virtual void Start() override;
        virtual void End() override;
    };
}  // namespace HBSoft
