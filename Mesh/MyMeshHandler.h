#pragma once
#include "Handler.h"
#include "Box2D.h"

namespace MyProject
{
	class MyMeshHandler : public Handler<MyMesh2D>
	{
		void CreateBox2DMesh(const std::string _key, POINT_F _rectSize);
		void AddMesh(const std::string _key, std::shared_ptr<MyMesh2D>& _texture);
	};
}

