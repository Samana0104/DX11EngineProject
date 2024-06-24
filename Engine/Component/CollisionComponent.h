#pragma once
#include "MyTransformer2D.h"
#include "MyMesh2D.h"
#include "MyResourceManger.h"

namespace MyProject
{
	// 나중에 다중 충돌 구현을 위해 메쉬 헤더만 포함
	class CollisionComponent
	{
	private:
		MyTransformer2D& mObjMat;
		
	public:
		CollisionComponent(MyTransformer2D& _objMat);

		bool IsAABBCollision(MyTransformer2D& _targetM);
		bool IsOBBCollision(MyTransformer2D& _targetM);
	};
}

