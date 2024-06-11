#include "MyTransformer2D.h"
using namespace MyProject;

vec2 MyTransformer2D::CalculateTRS(const vec2& _pos)
{
	const vec2 scaledVec = MyTransformer2D::ResizeScale(_pos, mScale);
	const vec2 rotatedVec = MyTransformer2D::RotateAsAngle(scaledVec, mAngle);
	return rotatedVec + mLocation;
}

vec2 MyTransformer2D::PixelToNDC(const vec2& _pos, const vec2 &_rectSize)
{
	const vec2 normalizedVec = _pos / _rectSize;
	return { normalizedVec.x * 2.f - 1.f, -(normalizedVec.y * 2.f - 1.f) };
}

vec2 MyTransformer2D::DescartesToPolar(const vec2 _pos)
{
	return { glm::length(_pos), glm::atan(_pos.x / _pos.y) };
}

vec2 MyTransformer2D::PolarToDescartes(const vec2 _pos)
{
	return { _pos.x * glm::cos(_pos.y), _pos.y * glm::sin(_pos.y) };
}

float MyTransformer2D::AngleToRadian(const float _angle)
{
	return glm::radians(_angle);
}

vec2 MyTransformer2D::RotateAsAngle(const vec2 _pos, const float _angle)
{
	return RotateAsRadian(_pos, glm::radians(_angle));
}

vec2 MyTransformer2D::RotateAsRadian(const vec2 _pos, const float _radian)
{
	return { _pos.x * glm::cos(_radian) - _pos.y * glm::sin(_radian),
			 _pos.x * glm::sin(_radian) + _pos.y * glm::cos(_radian) };
}

vec2 MyTransformer2D::ResizeScale(const vec2 _pos, const vec2 _scale)
{
	return { _pos.x * _scale.x, _pos.y * _scale.y };
}
