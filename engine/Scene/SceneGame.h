/*
author : 변한빛
description : 게임 내부 씬을 정의하는 헤더 파일

version: 1.1.0
date: 2024-12-03
*/

#pragma once
#include "pch.h"
#include "Camera.h"
#include "3D/LineObj.h"
#include "3D/CubeMapObj.h"
#include "3D/HeightMapObj.h"
#include "3D/Test3DObj.h"
#include "3D/Goose.h"
#include "GameButton.h"
#include "3D/Gardener.h"
#include "AABBCollider.h"
#include "3D/Line1.h"
#include "../Line1.h"

namespace HBSoft
{
    class SceneGame : public Scene
    {
    public:
        GameButton              m_escButton;
        CubeMapObj              cube;
        std::shared_ptr<Camera> cameraTest;
        LineObj                 m_line;
        HeightMapObj            m_map;
        Goose                   m_goose;
        Gardener                m_gardener;
        AABBCollider            m_aabbCollider;
        LineObj                 m_line1;

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
