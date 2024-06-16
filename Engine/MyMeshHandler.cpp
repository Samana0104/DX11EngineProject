#include "pch.h"
#include "MyMeshHandler.h"
using namespace MyProject;

bool MyMeshHandler::CreateMesh(const MESH_KEY _key, MeshShape _meshShape, POINT_F _meshSize)
{
	switch (_meshShape)
	{
	case MeshShape::BOX2D:
		return CreateBox2DMesh(_key, _meshSize);
	}
}

bool MyMeshHandler::CreateBox2DMesh(const MESH_KEY _key, const POINT_F _meshSize)
{
	auto boxMesh = std::make_shared<MyMesh2D>(MyBox2D(_meshSize));
	return AddResource(_key, boxMesh);
}
