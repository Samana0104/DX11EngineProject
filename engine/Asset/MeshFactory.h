/*
author : 변한빛
description : 메쉬를 생성 하기 위한 소스 파일

version: 1.0.0
date: 2024-11-17
*/

#pragma once
#include "pch.h"
#include "Mesh/Mesh.h"
#include "Mesh/Box3D.h"
#include "Mesh/Line.h"
#include "Mesh/CubeMap.h"

namespace HBSoft
{
    class MeshFactory
    {
    public:
        static std::shared_ptr<Mesh> Create(std::shared_ptr<D3Device>& device, const wstringV path);
        static std::shared_ptr<Mesh> Create(std::shared_ptr<D3Device>& device, const MeshShape shape);

        static bool IsMeshFormat(const wstringV path);
    };
}  // namespace HBSoft
