/*
author : Á¤Âùºó
description : ±×¸®µå¸Ê °»

version: 1.0.4
date: 2024-12-11
*/


#pragma once
#include "Core.h"
#include "3D/Object3D.h"
#include "GridMap.h"

namespace HBSoft
{

    class GridMap : public Object3D
    {
    private:
        std::shared_ptr<Mesh> m_gridMesh;

    public:
        GridMap();

        virtual void Update(const float deltaTime) override;
        virtual void Render() override;
        virtual void Init() override;
        virtual void Release() override;
    };
}  // namespace HBSoft