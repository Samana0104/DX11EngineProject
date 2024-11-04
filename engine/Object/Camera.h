/*
author : ���Ѻ�
description : ī�޶� �����ϱ� ���� ��� ����

version: 1.0.0
date: 2024-11-04
*/

#pragma once
#include "Object2D.h"

namespace HBSoft
{
    class Camera
    {
    public:
        Transform2D m_transform;

    public:
        const mat3 GetViewMat() const;

        void ZoomIn(const float scale);
        void ZoomOut(const float scale);

        void LookAtObject(Object2D& obj);
    };
}  // namespace HBSoft
