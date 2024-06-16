#pragma once
#include "Component.h"

namespace MyProject
{
	class MyTransformer2D
	{
	private:
		static inline vec2 mCartesianSize = { 160.f, 90.f };

		vec2	mLocation;
		vec2	mScale;
		float	mAngle;
		mat3x3  mModelMatrix;

	private:
		void CalculateScaleRotationMat();
		vec2 CalculateScreenTRS(const vec2& _pos);
		
	public:
		MyTransformer2D();

		void InitTransform();
		MyTransformer2D& AddTranslationInMat(const vec2 _pos);
		MyTransformer2D& AddRotationInMat(const float _angle);
		MyTransformer2D& AddScaleInMat(const vec2 _scale);
		MyTransformer2D& SetTranslationInMat(const vec2 _pos);
		MyTransformer2D& SetRotationInMat(const float _angle);
		MyTransformer2D& SetScaleInMat(const vec2 _scale);
		const mat3x3& GetModelMat() const;

		static void		SetCartesianSize(const vec2 _pos);
		static vec2		GetCartesianSize(const vec2 _pos);

		static vec2		CartesianToNDC(const vec2& _pos);
		static vec2		CartesianToPolar(const vec2 _pos);
		static vec2		PolarToCartesian(const vec2 _pos);
		static vec2		PixelToCartesian(const vec2& _pos, const vec2& _windowSize);
		static vec2		PixelToNDC(const vec2 &_pos, const vec2 &_rectSize);

		static vec2		RotateAsAngle(const vec2 _pos, const float _angle);
		static vec2		RotateAsRadian(const vec2 _pos, const float _radian);
		static vec2		ResizeScale(const vec2 _pos, const vec2 _scale);
		static vec2		lerp(const vec2 _pos1, const vec2 _pos2, float t);
		static float	lerp(float const a, const float b, float t);
		static vec2		Slerp(const vec2 _pos1, const vec2 _pos2, float t);
	};
}
