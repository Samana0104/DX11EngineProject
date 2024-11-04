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
    auto boxMesh = std::make_unique<Box2D>();
    return Add(key, std::move(boxMesh));
}

bool MeshHandler::CreateCircle2DMesh(const MESH_KEY& key)
{
    auto circleMesh = std::make_unique<Circle2D>();
    return Add(key, std::move(circleMesh));
}
