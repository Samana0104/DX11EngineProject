#pragma once
#include "MyObject.h"
#include "CollisionComponent.h"

namespace MyProject
{
	class MyActor : public MyObject
	{

	protected:
		MyActor() = default;

	public:
		virtual void Update(const float _deltaTime) = 0;
		virtual void Render(const mat3& _viewMat) = 0;
	};
}

