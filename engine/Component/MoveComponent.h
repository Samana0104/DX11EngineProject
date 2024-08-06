#pragma once
#include "MyCoreAPI.h"
#include "MyTransformer2D.h"

namespace MyProject
{
	class MoveComponent
	{
	private:
		vec2	mVelocity	  = { 0.f, 0.f };
		vec2 	mAcceleration = { 0.f, 0.f };
		vec2 	mOffset		  = { 0.f, 0.f };
		vec2	mDir		  = { 0.f, 0.f };
		// °è»ê¿ë

		bool	mIsXposBreaking = false;
		bool	mIsYposBreaking = false;

		MyTransformer2D & mTransform;

	public:
		MoveComponent(MyTransformer2D & _transform);

		void SetSpeedX(const float _speedX);
		void SetSpeedY(const float _speedY);

		void SetAccelX(const float _acclerationX);
		void SetAccelY(const float _acclerationY);

		const vec2& GetOffset() const;
		
		void AddSpeedX(const float _speed);
		void AddSpeedY(const float _speed);
		void AddAccelX(const float _acceleration);
		void AddAccelY(const float _acceleration);

		void Break(const vec2 _scalar);
		void Stop();

		vec2  GetVelocity() const;
		vec2  GetAccel() const;

		void  Update(float _deltaTime);
	};
}

