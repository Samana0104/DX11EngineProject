/*
author : 변한빛, 정찬빈, 이지혁
description : 게임 내부 씬을 정의하는 헤더 파일

version: 1.1.1
date: 2024-12-23
*/

#pragma once
#include "pch.h"

#include "EventHandler.h"
#include "Camera/DebugCamera.h"
#include "Camera/GooseCamera.h"
#include "2D/GridMap.h"
#include "3D/LineObj.h"
#include "3D/CubeMapObj.h"
#include "3D/QuadTree.h"
#include "3D/Test3DObj.h"
#include "3D/Goose.h"
#include "3D/Gardener.h"
#include "3D/CollisionObj.h"
#include "3D/Static3DObj.h"
#include "3D/Dynamic3DObj.h"
#include "3D/DirectionalLight.h"
#include "HBSAutoLoader.h"
#include "GameButton.h"
#include "QuestGUI.h"

namespace HBSoft
{
    class SceneGame : public Scene, Observer
    {
    public:
        GameButton                    m_escButton;
        QuestGUI                      m_questGUI;
        CubeMapObj                    cube;
        QuadTree                      m_tree;
        Gardener                      m_gardener;
        GridMap                       m_grid;
        std::shared_ptr<CollisionObj> m_colObjs;

        HBSAutoLoader<std::shared_ptr<Static3DObj>>  m_staticObjs;
        HBSAutoLoader<std::shared_ptr<Dynamic3DObj>> m_dynamicObjs;

#ifdef _DEBUG
        std::shared_ptr<DebugCamera> cameraTest;
#else
        std::shared_ptr<GooseCamera> cameraTest;
#endif
        std::shared_ptr<DirectionalLight> lightTest;
        std::shared_ptr<HeightMapObj>     mapTest;
        std::shared_ptr<LineObj>          m_line;
        std::shared_ptr<Goose>            m_goose;

        bool isWire        = false;
        bool m_isGameClear = false;

        float m_isTimer = 0.f;

    public:
        SceneGame();

        virtual void Update(float deltaTime) override;
        virtual void Render() override;
        virtual void Release() override;
        virtual void Start() override;
        virtual void End() override;

        virtual void OnNotice(EventList event, void* entity);
    };
}  // namespace HBSoft
