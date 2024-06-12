#pragma once
#include "Component.h"

namespace MyProject
{
	struct MyTransformer2D
	{
	public:
		vec2	mLocation	= { 0.f, 0.f }; //¿Ãµø
		vec2	mScale	    = { 1.f, 1.f };
		float	mAngle		= 0.f;

		vec2		CalculateTRS(const vec2& _pos);

		static vec2		WorldToNDC(const vec2& _pos, const vec2& _rectSize, float _aspect);
		static vec2		PixelToNDC(const vec2 &_pos, const vec2 &_rectSize);
		static vec2		DescartesToPolar(const vec2 _pos);
		static vec2		PolarToDescartes(const vec2 _pos);
		static float	AngleToRadian(const float _angle);
		static vec2		RotateAsAngle(const vec2 _pos, const float _angle);
		static vec2		RotateAsRadian(const vec2 _pos, const float _radian);
		static vec2		ResizeScale(const vec2 _pos, const vec2 _scale);
	};
}
