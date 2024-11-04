/*
author : 변한빛
description : 박스2D를 만드는 헤더 파일

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

        virtual void SetUVVertexAsRect(const RECT_F& _rect, const vec2& _imageSize) override;
    };
}  // namespace HBSoft
