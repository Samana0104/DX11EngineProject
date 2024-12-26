/*
author : 변한빛, 정찬빈, 이지혁
description : 게임 내부 씬을 정의하는 헤더 파일

version: 1.1.1
date: 2024-12-23
*/

#pragma once
#include "pch.h"

#include "Camera.h"
#include "3D/LineObj.h"
#include "3D/CubeMapObj.h"
#include "3D/QuadTree.h"
#include "3D/Test3DObj.h"
#include "3D/Goose.h"
#include "3D/Gardener.h"
#include "3D/AABBCollider.h"
#include "GameButton.h"
#include "3D/Static3DObj.h"
#include "HBSAutoLoader.h"
#include "3D/DirectionalLight.h"
#include "2D/GridMap.h"

namespace HBSoft
{
    class SceneGame : public Scene
    {
    public:
        GameButton                 m_escButton;
        CubeMapObj                 cube;
        LineObj                    m_line;
        QuadTree                   m_tree;
        Goose                      m_goose;
        Gardener                   m_gardener;
        GridMap                    m_grid;
        HBSAutoLoader<Static3DObj> m_staticObjs;

        std::shared_ptr<Camera>           cameraTest;
        std::shared_ptr<DirectionalLight> lightTest;
        std::shared_ptr<HeightMapObj>     mapTest;

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
