#pragma once
#include "ResourceHandler.h"
#include "MyBox2D.h"

namespace MyProject
{
	class MyMeshHandler : public ResourceHandler<MyMesh2D, MESH_KEY>
	{
	public:
		bool CreateMesh(const MESH_KEY _key, const MeshShape _meshShape, const POINT_F _meshSize);
		bool CreateBox2DMesh(const MESH_KEY _key, const POINT_F _meshSize);
	};
}

