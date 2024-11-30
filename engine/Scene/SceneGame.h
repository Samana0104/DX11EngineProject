/*
author :  ������
description : ������ �������� �׽�Ʈ �ϱ� ���� ��� ����

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
