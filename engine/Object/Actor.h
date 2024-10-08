#pragma once
#include "Object.h"
#include "MyCamera.h"
#include "CollisionComponent.h"
#include "MoveComponent.h"

namespace HBSoft
{
	class Actor : public Object
	{
	protected:
		CollisionComponent mCollision;
		MoveComponent	   mMove;

		MyCamera*		   mCamera = nullptr;

	private:
		virtual void OnCollision(RECT_F& _self, RECT_F& _target, Actor& _targetObj) = 0;

	protected:
		Actor();

	public:
		void SetViewedCamera(MyCamera* _camera);

		CollisionComponent& GetCollisionComponent();
		MoveComponent&		GetMoveComponent();
		
		//virtual void Front(vec2 _move) = 0;
		//virtual void Back(vec2 _move) = 0;
		//virtual void Right(vec2 _move) = 0;
		//virtual void Left(vec2 _move) = 0;

		virtual void Update(const float _deltaTime) override;
		virtual void Render() override;
	};
}

