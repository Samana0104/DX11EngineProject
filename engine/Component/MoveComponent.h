#pragma once
#include "CoreAPI.h"
#include "Transform2D.h"

namespace HBSoft
{
	class MoveComponent
	{
	private:
		vec2 m_velocity = { 0.f, 0.f };
		vec2 m_acceleration = { 0.f, 0.f };
		vec2 m_offset = { 0.f, 0.f };
		vec2 m_dir = { 0.f, 0.f };
		// °è»ê¿ë

		bool	m_isXposBreaking = false;
		bool	m_isYposBreaking = false;

		Transform2D& m_transform;

	public:
		MoveComponent(Transform2D& transform);

		void SetSpeedX(const float speedX);
		void SetSpeedY(const float speedY);

		void SetAccelX(const float acclerationX);
		void SetAccelY(const float acclerationY);

		const vec2& GetOffset() const;

		void AddSpeedX(const float speed);
		void AddSpeedY(const float speed);
		void AddAccelX(const float acceleration);
		void AddAccelY(const float acceleration);

		void Break(const vec2 scalar);
		void Stop();

		vec2  GetVelocity() const;
		vec2  GetAccel() const;

		void  Update(float deltaTime);
	};
}

