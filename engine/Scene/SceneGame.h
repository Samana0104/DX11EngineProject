/*
author : 변한빛
description : 게임 내부 씬을 정의하는 헤더 파일

version: 1.1.0
date: 2024-11-30
*/

#pragma once
#include "pch.h"
#include "Camera.h"
#include "3D/LineObj.h"
#include "3D/CubeMapObj.h"
#include "3D/Test3DObj.h"
#include "3D/HeightMapObj.h"

namespace HBSoft
{
    class SceneGame : public Scene
    {
    public:
        CubeMapObj              cube;
        std::shared_ptr<Camera> cameraTest;
        LineObj                 m_line;
        HeightMapObj            m_map;

        bool isWire = false;

    public:
        SceneGame();

        virtual void Update(float deltaTime) override;
        virtual void Render() override;
        virtual void Release() override;
        virtual void Start() override;
        virtual void End() override;
    };
}  // namespace HBSoft
