#include "pch.h"
#include "MeshHandler.h"
using namespace HBSoft;

bool MeshHandler::CreateMeshResource(const MESH_KEY key, MeshShape meshShape)
{
    switch (meshShape)
    {
    case MeshShape::BOX2D:
        return CreateBox2DMesh(key);

    case MeshShape::CIRCLE2D:
        return CreateCircle2DMesh(key);
    }

    return false;
}

bool MeshHandler::CreateBox2DMesh(const MESH_KEY& key)
{
    std::shared_ptr<Mesh2D> boxMesh = std::make_shared<Box2D>();
    return Add(key, boxMesh);
}

bool MeshHandler::CreateCircle2DMesh(const MESH_KEY& key)
{
    std::shared_ptr<Mesh2D> circleMesh = std::make_shared<Circle2D>();
    return Add(key, circleMesh);
}
