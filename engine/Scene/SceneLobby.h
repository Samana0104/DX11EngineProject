/*
author : ���Ѻ�
description : ���� ��ȯ�� �׽�Ʈ �ϱ� ���� ��� ����

version: 1.0.0
date: 2024-11-04
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
    class SceneLobby : public Scene
    {
    public:
        Object3D     test;
        CubeMapObj   cube;
        Camera       cameraTest;
        LineObj      m_line;
        Test3DObj    m_zelda;
        HeightMapObj m_map;

        bool isWire = false;

    public:
        SceneLobby();

        virtual void Update(float deltaTime) override;
        virtual void Render() override;
        virtual void Release() override;
        virtual void Start() override;
        virtual void End() override;
    };
}  // namespace HBSoft
