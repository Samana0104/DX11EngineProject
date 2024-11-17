/*
author : ���Ѻ�
description : �޽��� ���� �ϱ� ���� �ҽ� ����

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

    default:  // ����� ���� �޽� �߰� ���ϸ� ���� �߰���
        assert(0);
    }

    return mesh;
}

bool MeshFactory::IsMeshFormat(const wstringV path)
{
    auto [fileName, fileExt] = HBSoft::GetFileNameAndExt(path);
    // modern c++ ����ε� ������ ���ε��̶�� pair ��ü �ٷ� ���� ������ ���ִ� �����

    if (fileExt.compare(L"fbx") == 0)
        return true;

    return false;
}
