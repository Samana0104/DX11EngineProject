/*
author : ���Ѻ�
description : ť�� �� �޽��� ����� �������

version: 1.0.4
date: 2024-11-22
*/

#pragma once

#include "Mesh/Mesh.h"
#include "Mesh/Box3D.h"

namespace HBSoft
{
    class CubeMap : public Mesh
    {
    private:
        bool CreateVertices(std::shared_ptr<D3Device> device);
        bool CreateIndices(std::shared_ptr<D3Device> device);

    public:
        CubeMap(std::shared_ptr<D3Device> device);
        ~CubeMap() = default;
    };
}  // namespace HBSoft
