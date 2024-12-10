/*
author : ���Ѻ�
description : ������ ����� ���� ��� ����

version: 1.0.0
date: 2024-11-07
*/

#pragma once

#include "Mesh.h"

namespace HBSoft
{
    class Line : public Mesh
    {
    private:
        bool CreateVertices(std::shared_ptr<D3Device> device);
        bool CreateIndices(std::shared_ptr<D3Device> device);

    public:
        Line(std::shared_ptr<D3Device> device);
        ~Line() = default;
    };
}  // namespace HBSoft
