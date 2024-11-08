/*
author : 변한빛
description : 박스2D를 만드는 헤더 파일

version: 1.0.0
date: 2024-11-04
*/

#pragma once
#include "Mesh.h"

namespace HBSoft
{
    class Box2D : public Mesh
    {
    private:
        void CreateBox2DVertex();

    public:
        Box2D();
    };
}  // namespace HBSoft
