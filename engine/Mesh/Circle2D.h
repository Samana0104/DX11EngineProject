/*
author : 변한빛
description : 원 메쉬를 만드는 헤더 파일

version: 1.0.0
date: 2024-11-04
*/

#pragma once
#include "Mesh2D.h"

namespace HBSoft
{
    class Circle2D : public Mesh2D
    {
    private:
        size_t m_triangles;

    private:
        void CreateCircle2DVertex();

    public:
        Circle2D(const size_t triangles = 50);

        virtual void SetUVVertexAsRect(const HRect& rect, const vec2& imageSize) override;
    };
}  // namespace HBSoft
