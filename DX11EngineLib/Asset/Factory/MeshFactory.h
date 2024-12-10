/*
author : 변한빛
description : 메쉬를 생성 하기 위한 소스 파일

version: 1.1.0
date: 2024-11-22
*/

#pragma once
#include "pch.h"
#include "Mesh/Mesh.h"
#include "Mesh/Box3D.h"
#include "Mesh/Box2D.h"
#include "Mesh/Circle.h"
#include "Mesh/Line.h"
#include "Mesh/CubeMap.h"
#include "Mesh/HeightMap.h"
#include "HBSLoader.h"

namespace HBSoft
{
    class MeshFactory
    {
    public:
        static std::shared_ptr<Mesh> Create(std::shared_ptr<D3Device> device, const wstringV path);
        static std::shared_ptr<Mesh> Create(std::shared_ptr<D3Device> device, const MeshShape shape);
        static std::shared_ptr<Mesh> CreateHeightMap(std::shared_ptr<D3Device> device,
                                                     const MapDesc&            desc);

        static bool IsMeshFormat(const wstringV ext);
    };
}  // namespace HBSoft
