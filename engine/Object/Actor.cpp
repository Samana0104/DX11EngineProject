/*
author : 변한빛
description : 액터를 정의하기 위한 소스 파일
여기서 액터의 기준은 오브젝트가 움직이는지 기준

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
