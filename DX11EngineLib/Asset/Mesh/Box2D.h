/*
author : ������
description : �ڽ�2D�� ����� ��� ����

version: 1.0.0
date: 2024-11-27
*/

#pragma once
#include "Mesh.h"

namespace HBSoft
{
    class Box2D : public Mesh
    {
    private:
        bool CreateVertices(std::shared_ptr<D3Device>& device);
        bool CreateIndices(std::shared_ptr<D3Device>& device);

    public:
        Box2D(std::shared_ptr<D3Device> device);
        ~Box2D() = default;
    };
}  // namespace HBSoft
