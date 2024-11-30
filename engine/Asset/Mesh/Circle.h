/*
author : ������, ���Ѻ�
description : ���� ����� ��� ����

version: 1.0.0
date: 2024-11-30
*/

#pragma once
#include "Mesh.h"

namespace HBSoft
{
    class Circle : public Mesh
    {
    public:
        int m_triangles;

    private:
        bool CreateVertices(std::shared_ptr<D3Device> device);
        bool CreateIndices(std::shared_ptr<D3Device> device);

    public:
        Circle(std::shared_ptr<D3Device> device);
        ~Circle() = default;
    };
}  // namespace HBSoft
