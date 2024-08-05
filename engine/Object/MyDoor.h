#pragma once
#include "MyActor.h"
#include "SpriteComponent.h"

namespace MyProject
{
	class MyDoor : public MyActor
	{
	private:
		SpriteComponent mLock;
		SpriteComponent mUnLock;
		
		bool mIsLock = true;

	private:
		virtual void OnCollision(RECT_F& _self, RECT_F& _target, MyActor& _targetObj) override;

	public:
		MyDoor();

		virtual void Update(const float _deltaTime) override;
		virtual void Render() override;
	};
}

