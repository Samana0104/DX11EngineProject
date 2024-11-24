/*
author : ���Ѻ�
description : �޽��� ���� �ϱ� ���� �ҽ� ����

version: 1.1.1
date: 2024-11-22
*/

#include "pch.h"
#include "MeshFactory.h"
using namespace HBSoft;

std::shared_ptr<Mesh> MeshFactory::Create(std::shared_ptr<D3Device> device, const wstringV path)
{
    static FbxLoader fbxLoader;

    std::shared_ptr<Mesh> mesh = fbxLoader.Load(device, path);

    if (mesh == nullptr)
        assert(false);

    return mesh;
}

std::shared_ptr<Mesh> MeshFactory::Create(std::shared_ptr<D3Device> device, const MeshShape shape)
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

    default:  // ����� ����Ʈ �޽� �߰� ���ϸ� ���� �߰���
        assert(false);
    }

    return mesh;
}

std::shared_ptr<Mesh> MeshFactory::CreateHeightMap(std::shared_ptr<D3Device> device, const MapDesc& desc)
{
    std::shared_ptr<Mesh> mesh = std::make_shared<HeightMap>(device, desc);
    return mesh;
}

bool MeshFactory::IsMeshFormat(const wstringV ext)
{
    if (ext.compare(L".fbx") == 0)
        return true;
    else if (ext.compare(L".obj") == 0)
        return true;

    return false;
}
