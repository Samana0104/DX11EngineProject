/*
author : ���Ѻ�
description : �ڽ�2D�� ����� ��� ����

version: 1.0.0
date: 2024-11-04
*/

#pragma once
#include "Mesh2D.h"

namespace HBSoft
{
    class Box2D : public Mesh2D
    {
    private:
        void CreateBox2DVertex();

    public:
        Box2D();

        virtual void SetUVVertexAsRect(const HRect& _rect, const vec2& _imageSize) override;
    };
}  // namespace HBSoft
