/*
author : ���Ѻ�
description : �޽��� �Ŵ�¡ �ϱ� ���� ��� ����

version: 1.0.0
date: 2024-11-04
*/

#pragma once
#include "MgrTemplate.h"
#include "Box2D.h"
#include "Circle2D.h"

namespace HBSoft
{
    class MeshHandler : public MgrTemplate<Mesh, MESH_KEY>
    {
    private:
        bool CreateBox2DMesh(const MESH_KEY& key);
        bool CreateCircle2DMesh(const MESH_KEY& key);

    public:
        bool CreateMeshResource(const MESH_KEY key, const MeshShape meshShape);
    };
}  // namespace HBSoft
