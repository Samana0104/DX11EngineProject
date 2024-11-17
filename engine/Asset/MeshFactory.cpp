/*
author : 변한빛
description : 메쉬를 생성 하기 위한 소스 파일

version: 1.0.0
date: 2024-11-04
*/

#include "pch.h"
#include "MeshFactory.h"
using namespace HBSoft;

std::shared_ptr<Mesh> MeshFactory::Create(std::shared_ptr<D3Device>& device, const wstringV path)
{
    return nullptr;
}

std::shared_ptr<Mesh> MeshFactory::Create(std::shared_ptr<D3Device>& device, const MeshShape shape)
{
    std::shared_ptr<Mesh> mesh;

    switch (shape)
    {
    case MeshShape::BOX3D:
        mesh = std::make_shared<Box3D>(device);
        break;

    case MeshShape::LINE:
        mesh = std::make_shared<Line>(device);
        break;

    case MeshShape::CUBEMAP:
        mesh = std::make_shared<CubeMap>(device);
        break;

    default:  // 여기다 만든 메쉬 추가 안하면 에러 뜨게함
        assert(0);
    }

    return mesh;
}

bool MeshFactory::IsMeshFormat(const wstringV path)
{
    auto [fileName, fileExt] = HBSoft::GetFileNameAndExt(path);
    // modern c++ 기능인데 구조적 바인딩이라고 pair 객체 바로 변수 값에다 쏴주는 기능임

    if (fileExt.compare(L"fbx") == 0)
        return true;

    return false;
}
