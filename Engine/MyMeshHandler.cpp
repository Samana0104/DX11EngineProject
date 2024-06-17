#include "pch.h"
#include "MyMeshHandler.h"
using namespace MyProject;

bool MyMeshHandler::CreateMesh(const MESH_KEY _key, MeshShape _meshShape)
{
	switch (_meshShape)
	{
	case MeshShape::BOX2D:
		return CreateBox2DMesh(_key);
	}
	
	return false;
}

bool MyMeshHandler::CreateBox2DMesh(const MESH_KEY _key)
{
	auto boxMesh = std::make_shared<MyMesh2D>(MyBox2D());
	return AddResource(_key, boxMesh);
}
