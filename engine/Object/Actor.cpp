/*
author : ���Ѻ�
description : ���͸� �����ϱ� ���� �ҽ� ����
���⼭ ������ ������ ������Ʈ�� �����̴��� ����

version: 1.0.0
date: 2024-11-04
*/

#include "pch.h"
#include "Actor.h"
using namespace HBSoft;

Actor::Actor() {}

void Actor::SetViewedCamera(Camera* _camera)
{
    mCamera = _camera;
}

void Actor::Update(const float _deltaTime) {}

void Actor::Render()
{
    if (mCamera == nullptr)
    {
        Object2D::Render();
    }
}
