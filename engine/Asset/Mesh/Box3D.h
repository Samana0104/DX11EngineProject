/*
author : ���Ѻ�
description : 3d �ڽ� ���� ����� �ڽ� 3d ��� ����

version: 1.0.4
date: 2024-11-22
*/
#pragma once

#include "pch.h"
#include "Mesh\Mesh.h"

namespace HBSoft
{
    class Box3D : public Mesh
    {
    private:
        bool CreateVertices(std::shared_ptr<D3Device> device);
        bool CreateIndices(std::shared_ptr<D3Device> device);
        void CreateAutoCollision();

    public:
        Box3D(std::shared_ptr<D3Device> device);
        ~Box3D() = default;
    };
}  // namespace HBSoft
