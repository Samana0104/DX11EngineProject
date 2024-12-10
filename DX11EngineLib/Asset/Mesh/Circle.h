/*
author : 정찬빈, 변한빛
description : 원을 만드는 헤더 파일

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
