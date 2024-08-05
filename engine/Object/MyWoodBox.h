#pragma once
#include "MyActor.h"

namespace MyProject
{
	class MyWoodBox : public MyActor
	{
	private:
		virtual void OnCollision(RECT_F& _self, RECT_F& _target, MyActor& _targetObj) override;

	public:
		MyWoodBox();

		virtual void Update(const float _deltaTime) override;
	};
}

