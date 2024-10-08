#pragma once
#include "ResourceHandler.h"
#include "Box2D.h"
#include "Circle2D.h"

namespace HBSoft
{
    class MeshHandler : public ResourceHandler<Mesh2D, MESH_KEY>
    {
    private:
        bool CreateBox2DMesh(const MESH_KEY& _key);
        bool CreateCircle2DMesh(const MESH_KEY& _key);

    public:
        bool CreateMeshResource(const MESH_KEY _key, const MeshShape _meshShape);
    };
}  // namespace HBSoft
