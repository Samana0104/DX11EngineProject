/*
author : ���Ѻ�
description : ���� ��ȯ�� �׽�Ʈ �ϱ� ���� ��� ����

version: 1.0.0
date: 2024-11-04
*/

#pragma once
#include "pch.h"
#include "Camera.h"

namespace HBSoft
{
    class SceneLobby : public Scene
    {
    public:
        Object3D test;
        Camera   cameraTest;

    public:
        SceneLobby();

        virtual void Update(float deltaTime) override;
        virtual void Render() override;
        virtual void Release() override;
        virtual void Start() override;
        virtual void End() override;
    };
}  // namespace HBSoft
