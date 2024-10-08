#include "pch.h"
#include "MeshHandler.h"
using namespace HBSoft;

bool MeshHandler::CreateMeshResource(const MESH_KEY _key, MeshShape _meshShape)
{
    switch (_meshShape)
    {
    case MeshShape::BOX2D:
        return CreateBox2DMesh(_key);

    case MeshShape::CIRCLE2D:
        return CreateCircle2DMesh(_key);
    }

    return false;
}

bool MeshHandler::CreateBox2DMesh(const MESH_KEY& _key)
{
    std::shared_ptr<Mesh2D> boxMesh = std::make_shared<MyBox2D>();
    return AddResource(_key, boxMesh);
}

bool MeshHandler::CreateCircle2DMesh(const MESH_KEY& _key)
{
    std::shared_ptr<Mesh2D> circleMesh = std::make_shared<MyCircle2D>();
    return AddResource(_key, circleMesh);
}
