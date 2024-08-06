#pragma once
#include "ResourceHandler.h"
#include "MyBox2D.h"
#include "MyCircle2D.h"

namespace MyProject
{
	class MyMeshHandler : public ResourceHandler<MyMesh2D, MESH_KEY>
	{
	private:
		bool CreateBox2DMesh(const MESH_KEY& _key);
		bool CreateCircle2DMesh(const MESH_KEY& _key);

	public:
		bool CreateMeshResource(const MESH_KEY _key, const MeshShape _meshShape);
	};
}

