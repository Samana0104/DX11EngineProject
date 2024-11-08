/*
author : 변한빛
description : 원 메쉬를 만드는 소스 파일

version: 1.0.0
date: 2024-11-04
*/

#include "pch.h"
#include "Circle2D.h"
using namespace HBSoft;

Circle2D::Circle2D(const size_t triangles)
    : Mesh(false), m_triangles(triangles)
{
    CreateCircle2DVertex();
}

void Circle2D::CreateCircle2DVertex()
{
    //// 크기 1 반지름 0.5 원
    // const float anglePerTriangles = 360.f / static_cast<float>(m_triangles);
    // float       angle             = 0.f;
    // vec2        pos;

    // ReserveVertexSize(m_triangles);
    // AddVertexAndUV({0.f, 0.f}, {0.5f, 0.5f});  // sphere center
    // AddVertexAndUV({0.5f, 0.f}, {1.f, 0.5f});

    // for (size_t i = 1; i < m_triangles; i++)
    //{
    //     angle = glm::radians(anglePerTriangles * i);
    //     pos   = {0.5f * glm::cos(angle), 0.5f * glm::sin(angle)};
    //     AddVertexAndUV(pos, {pos.x + 0.5f, -pos.y + 0.5f});
    //     AddVertexIndex({0, (i + 1), i});
    // }

    // AddVertexIndex({0, 1, m_triangles});
    //// CreateMesh();
}
