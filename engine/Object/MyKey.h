#pragma once
#include "MyActor.h"
#include "SpriteComponent.h"
#include "MyObjectManager.h"

namespace MyProject
{
	class MyKey : public MyActor
	{
	private:
		SpriteComponent  mSprite;
		MyObjectManager& mObjManager;

	private:
		virtual void OnCollision(RECT_F& _self, RECT_F& _target, MyActor& _targetObj) override;

	public:
		MyKey(MyObjectManager&  _objManager);

		virtual void Update(const float _deltaTime) override;
		virtual void Render() override;

	};
};

