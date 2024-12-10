/*
author : 변한빛
description : 라인을 만들기 위한 헤더 파일

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
