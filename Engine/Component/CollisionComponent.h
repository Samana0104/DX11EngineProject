#pragma once
#include "MyTransformer2D.h"
#include "MyMesh2D.h"
#include "MyResourceManger.h"

namespace MyProject
{
	// 나중에 다중 충돌 구현을 위해 메쉬 헤더만 포함
	class CollisionComponent
	{
	public:
		static bool IsPointInRect(const RECT_F rt1, const vec2 pt);
		static bool IsAABBCollision(const RECT_F rt1, const RECT_F rt2);
		static bool IsAABBCollision(const MyTransformer2D& _objM, const MyTransformer2D& _targetM);
		static bool IsOBBCollision(const MyTransformer2D& _objM, const MyTransformer2D& _targetM);
	};
}

