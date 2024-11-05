/*
author : ���Ѻ�
description : ���͸� �����ϱ� ���� ��� ����
���⼭ ������ ������ ������Ʈ�� �����̴��� ����

version: 1.0.0
date: 2024-11-04
*/

#pragma once
#include "Object2D.h"
#include "Camera.h"

namespace HBSoft
{
    class Actor : public Object2D
    {
    protected:
        Camera* mCamera = nullptr;

    private:
        virtual void OnCollision(HRect& _self, HRect& _target, Actor& _targetObj) = 0;

    protected:
        Actor();

    public:
        void SetViewedCamera(Camera* _camera);

        // virtual void Front(vec2 _move) = 0;
        // virtual void Back(vec2 _move) = 0;
        // virtual void Right(vec2 _move) = 0;
        // virtual void Left(vec2 _move) = 0;

        virtual void Update(const float _deltaTime) override;
        virtual void Render() override;
    };
}  // namespace HBSoft
