#pragma once
#include "MyActor.h"
#include "SpriteComponent.h"

namespace MyProject
{
	class TestObj : public MyActor
	{
	private:
		SpriteComponent mSprite;

	public:
		TestObj();

		virtual void Update(const float _deltaTime) override;
		virtual void Render(const mat3& _viewMat) override;
	};
}

