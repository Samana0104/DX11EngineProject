/*
author : ���Ѻ�
description : �� �޽��� ����� ��� ����

version: 1.0.0
date: 2024-11-04
*/

#pragma once
#include "Mesh.h"

namespace HBSoft
{
    class Circle2D : public Mesh
    {
    private:
        size_t m_triangles;

    private:
        void CreateCircle2DVertex();

    public:
        Circle2D(const size_t triangles = 50);
    };
}  // namespace HBSoft
