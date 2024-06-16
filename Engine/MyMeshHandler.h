#pragma once
#include "ResourceHandler.h"
#include "Box2D.h"

namespace MyProject
{
	class MyMeshHandler : public ResourceHandler<MyMesh2D>
	{
		void CreateBox2DMesh(const std::string _key, POINT_F _rectSize);
		void AddMesh(const std::string _key, std::shared_ptr<MyMesh2D>& _texture);
	};
}

