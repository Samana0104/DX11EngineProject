#pragma once
#include "MyObject.h"
#include "CollisionComponent.h"

namespace MyProject
{
	class MyActor : public MyObject
	{
	private:

	public:
		CollisionComponent collision;
		COLOR_F				mColor;

		MyActor() : collision(mTransform) { mColor = { 1.f, 1.f,1.f,1.f }; }

		void SetColor(COLOR_F _color);
		COLOR_F GetColor() const;

		virtual void Update(const float _deltaTime);
		virtual void Render(const mat3 _viewMat);
	};
}

