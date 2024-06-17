#include "pch.h"
#include "MyTransformer2D.h"
using namespace MyProject;

MyTransformer2D::MyTransformer2D()
{
	InitTransform();
}

void MyTransformer2D::InitTransform()
{
	mLocation = { 0.f, 0.f };
	mAngle = 0.f;
	mScale = { 1.f, 1.f };
	mTRSMat = glm::mat3(1.0f);
}

MyTransformer2D& MyTransformer2D::AddTranslationInMat(const vec2 _pos)
{
	SetTranslationInMat(mLocation + _pos);
	return *this;
}

MyTransformer2D& MyTransformer2D::AddRotationInMat(const float _angle)
{
	SetRotationInMat(mAngle + _angle);
	return *this;
}

MyTransformer2D& MyTransformer2D::AddScaleInMat(const vec2 _scale)
{
	SetScaleInMat(mScale + _scale);
	return *this;
}

MyTransformer2D& MyTransformer2D::SetTranslationInMat(const vec2 _pos)
{
	mLocation = _pos;
	mTRSMat[2][0] = _pos.x;
	mTRSMat[2][1] = _pos.y;
	return *this;
}

MyTransformer2D& MyTransformer2D::SetRotationInMat(const float _angle)
{
	if (_angle >= 360.f)
	{
		// [-360, 360]
		const int angleDivison = glm::abs(static_cast<int>(_angle / 360.f));
		mAngle = _angle - static_cast<float>(angleDivison);
	}

	mAngle = _angle;
	CalculateScaleRotationMat();
	return *this;
}

MyTransformer2D& MyTransformer2D::SetScaleInMat(const vec2 _scale)
{
	mScale = _scale;
	CalculateScaleRotationMat();
	return *this;
}

const mat3& MyTransformer2D::GetModelMat() const
{
	return mTRSMat;
}

const mat3& MyTransformer2D::GetViewMat() const
{
	return glm::inverse(mTRSMat);
}

const vec2 MyProject::MyTransformer2D::GetLocation() const
{
	return mLocation;
}

const vec2 MyProject::MyTransformer2D::GetScale() const
{
	return mScale;
}

float MyProject::MyTransformer2D::GetAngle() const
{
	return mAngle;
}

void MyTransformer2D::SetCartesianSize(const vec2 _pos)
{
	MyTransformer2D::mCartesianSize = _pos;
}

vec2 MyTransformer2D::GetCartesianSize(const vec2 _pos)
{
	return MyTransformer2D::mCartesianSize;
}

void MyTransformer2D::CalculateScaleRotationMat()
{
	float cos = glm::cos(glm::radians(mAngle));
	float sin = glm::sin(glm::radians(mAngle));

	mTRSMat[0][0] = cos * mScale.x;
	mTRSMat[0][1] = sin * mScale.x;

	mTRSMat[1][0] = -sin * mScale.y;
	mTRSMat[1][1] = cos * mScale.y;
}

vec2 MyTransformer2D::CalculateScreenTRS(const vec2& _pos)
{
	const vec2 scaledVec = MyTransformer2D::ResizeScale(_pos, mScale);
	const vec2 rotatedVec = MyTransformer2D::RotateAsAngle(scaledVec, mAngle);
	return rotatedVec + mLocation;
}

vec2 MyTransformer2D::CartesianToNDC(const vec2& _pos)
{
	return (_pos / mCartesianSize) * 2.f;
}

vec2 MyTransformer2D::PixelToCartesian(const vec2 _pos)
{
	// pixel to cartesian in window range
	// -> (Pos.x - Window.X/2,  -Pos.y + Window.Y/2) => [-window/2, window/2]
	// -> (Pos.x - Window.X/2,  -Pos.y + Window.Y/2) / Window => [-1, 1]
	// -> (cartesian/2) *((Pos.x - Window.X/2,  -Pos.y + Window.Y/2) / Window) => [-cartesianSize/2, cartesianSize/2]
	/* column major
	[ cartesian/window(x)		0			cartesian/2(x)
	     0			  cartesian/window(y)	cartesian/2(y)
		 0						0				1	
	*/
	const vec2 windowSize = MyWindow::GetInstance().GetWindowSizeVec2();
	return { mCartesianSize.x * _pos.x / windowSize.x - mCartesianSize.x / 2,
			-mCartesianSize.y * _pos.y / windowSize.y + mCartesianSize.y / 2 };
}

vec2 MyTransformer2D::PixelToNDC(const vec2& _pos, const vec2 &_rectSize)
{
	const vec2 normalizedVec = _pos / _rectSize;
	return { normalizedVec.x * 2.f - 1.f, -(normalizedVec.y * 2.f - 1.f) };
}

vec2 MyTransformer2D::CartesianToPolar(const vec2 _pos)
{
	return { glm::length(_pos), glm::atan(_pos.x / _pos.y) };
}

vec2 MyTransformer2D::PolarToCartesian(const vec2 _pos)
{
	return { _pos.x * glm::cos(_pos.y), _pos.y * glm::sin(_pos.y) };
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

// 작성예정 3개 
vec2 MyTransformer2D::lerp(const vec2 _pos1, const vec2 _pos2, float t)
{
	return vec2();
}

float MyTransformer2D::lerp(float const a, const float b, float t)
{
	return 0.0f;
}

vec2 MyTransformer2D::Slerp(const vec2 _pos1, const vec2 _pos2, float t)
{
	return vec2();
}
