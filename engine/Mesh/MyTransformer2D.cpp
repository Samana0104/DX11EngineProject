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

MyTransformer2D& MyTransformer2D::AddLocation(const vec2 _pos)
{
	SetLocation(mLocation + _pos);
	return *this;
}

MyTransformer2D& MyTransformer2D::AddRotation(const float _angle)
{
	SetRotation(mAngle + _angle);
	return *this;
}

MyTransformer2D& MyTransformer2D::AddScale(const vec2 _scale)
{
	SetScale(mScale + _scale);
	return *this;
}

MyTransformer2D& MyTransformer2D::AddScaleAsRatio(const float _ratio)
{
	SetScale(mScale * _ratio);
	return *this;
}

MyTransformer2D& MyTransformer2D::SetLocation(const vec2 _pos)
{
	mLocation = _pos;
	mTRSMat[2][0] = _pos.x;
	mTRSMat[2][1] = _pos.y;
	return *this;
}

MyTransformer2D& MyTransformer2D::SetRotation(const float _angle)
{
	if (glm::abs(_angle) >= 360.f)
	{
		// [-360, 360]
		const int angleDivison = glm::abs(static_cast<int>(_angle / 360.f));
		mAngle = _angle - static_cast<float>(angleDivison);
	}

	mAngle = _angle;
	CalculateScaleRotationMat();
	return *this;
}

MyTransformer2D& MyTransformer2D::SetScale(const vec2 _scale)
{
	mScale = { glm::max(_scale.x, 0.f), glm::max(_scale.y, 0.f) };
	CalculateScaleRotationMat();
	return *this;
}

void MyTransformer2D::MultiplyToTRSMat(const mat3& _mat)
{
	mTRSMat = _mat * mTRSMat;
}

const mat3& MyTransformer2D::GetModelMat() const
{
	return mTRSMat;
}

const mat3 MyTransformer2D::GetViewMat() const
{
	return glm::inverse(mTRSMat);
}

const mat3 MyTransformer2D::GetTransposMat() const
{
	mat3 _mat(1.f);
	_mat[2][0] = mLocation.x;
	_mat[2][1] = mLocation.y;

	return _mat;
}

const mat3 MyTransformer2D::GetScaleMat() const
{
	mat3 _mat(1.f);
	_mat[0][0] = mScale.x;
	_mat[1][1] = mScale.y;
	return _mat;
}

const mat3 MyTransformer2D::GetRotationMat() const
{
	mat3 _mat(1.f);
	float cos = glm::cos(glm::radians(mAngle));
	float sin = glm::sin(glm::radians(mAngle));

	_mat[0][0] = cos;
	_mat[0][1] = sin;
	_mat[1][0] = -sin;
	_mat[1][1] = cos;
	return _mat;
}

const vec2& MyTransformer2D::GetLocation() const
{
	return mLocation;
}

const vec2& MyTransformer2D::GetScale() const
{
	return mScale;
}

float MyTransformer2D::GetAngle() const
{
	return mAngle;
}

RECT_F MyTransformer2D::GetCartesianRectF() const
{
	return {
		mLocation.x - mScale.x * 0.5f,
		mLocation.y + mScale.y * 0.5f,
		mLocation.x + mScale.x * 0.5f,
		mLocation.y - mScale.y * 0.5f
	};
}

RECT_F MyTransformer2D::GetCartesianScaleRectF() const
{
	return { 
		-mScale.x * 0.5f, 
		mScale.y * 0.5f, 
		mScale.x * 0.5f,
		-mScale.y * 0.5f 
	};
}

RECT_F MyTransformer2D::GetPixelRectF() const
{
	RECT_F cartesianRect = GetCartesianRectF();
	vec2 leftTop = CartesianToPixel({ cartesianRect.left, cartesianRect.top });
	vec2 rightBottom = CartesianToPixel({ cartesianRect.right, cartesianRect.bottom });
	
	return { leftTop.x, leftTop.y, rightBottom.x, rightBottom.y };
}

MyTransformer2D* MyTransformer2D::operator->()
{
	return this;
}

MyTransformer2D& MyTransformer2D::operator=(const MyTransformer2D& _ref)
{
	vec2	mLocation = _ref.mLocation;
	vec2	mScale = _ref.mScale;
	float	mAngle = _ref.mAngle;
	mat3	mTRSMat = _ref.mTRSMat;

	return *this;
}

void MyTransformer2D::SetCartesianSize(const vec2 _pos)
{
	MyTransformer2D::mCartesianSize = _pos;
}

vec2 MyTransformer2D::GetCartesianSize()
{
	return mCartesianSize;
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

vec2 MyTransformer2D::CalculateTRSAsVec(const vec2 _pos)
{
	const vec2 scaledVec = MyTransformer2D::ResizeScale(_pos, mScale);
	const vec2 rotatedVec = MyTransformer2D::RotateAsAngle(scaledVec, mAngle);
	return rotatedVec + mLocation;
}

RECT_F MyTransformer2D::CartesianToPixelRect(const RECT_F _rect)
{
	vec2 leftTop = CartesianToPixel({ _rect.left, _rect.top });
	vec2 rightBottom = CartesianToPixel({ _rect.right, _rect.bottom });
	return { leftTop.x, leftTop.y, rightBottom.x, rightBottom.y };
}

vec2 MyTransformer2D::CartesianToNDC(const vec2 _pos)
{
	return (_pos / mCartesianSize) * 2.f;
}

vec2 MyTransformer2D::CartesianToPixel(const vec2 _pos)
{
	float leftTopX = D3Device::GetInstance().mViewPort.TopLeftX;
	float leftTopY = D3Device::GetInstance().mViewPort.TopLeftY;

	const vec2 viewportSize = D3Device::GetInstance().GetViewportSize();

	return { leftTopX + _pos.x * viewportSize.x / mCartesianSize.x + 0.5f * viewportSize.x,
			leftTopY - _pos.y * viewportSize.y / mCartesianSize.y + 0.5f * viewportSize.y };
}

vec2 MyTransformer2D::PixelToCartesian(const vec2 _pos)
{
	// pixel to cartesian in window range
	// -> (Pos.x - Window.X/2,  -Pos.y + Window.Y/2) => [-window/2, window/2]
	// -> (Pos.x - Window.X/2,  -Pos.y + Window.Y/2) / Window => [-1, 1]
	// -> (cartesian/2) *((Pos.x - Window.X/2,  -Pos.y + Window.Y/2) / Window) => [-cartesianSize/2, cartesianSize/2]
	/* column major, matrix expression
	[ cartesian/window(x)		0			-cartesian/2(x)
	     0			  cartesian/window(y)	-cartesian/2(y)
		 0						0				1	
	*/
	// viewport 기준으로 맞춤
	float leftTopX = D3Device::GetInstance().mViewPort.TopLeftX;
	float leftTopY = D3Device::GetInstance().mViewPort.TopLeftY;

	const vec2 viewportSize = D3Device::GetInstance().GetViewportSize();

	return { mCartesianSize.x * (_pos.x-leftTopX) / viewportSize.x - mCartesianSize.x / 2,
			-mCartesianSize.y * (_pos.y-leftTopY) / viewportSize.y + mCartesianSize.y / 2};

}

vec2 MyTransformer2D::PixelToNDC(const vec2 _pos, const vec2 _rectSize)
{
	const vec2 normalizedVec = _pos / _rectSize;
	return { normalizedVec.x * 2.f - 1.f, -(normalizedVec.y * 2.f - 1.f) };
}

vec2 MyTransformer2D::CartesianToPolar(const vec2 _pos)
{
	return { glm::length(_pos), glm::atan(_pos.y / _pos.x) };
}

vec2 MyTransformer2D::PolarToCartesian(const vec2 _pos)
{
	// _pos = (r,theta)
	return { _pos.x * glm::cos(_pos.y), _pos.x * glm::sin(_pos.y) };
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

vec2 MyTransformer2D::Slerp(const vec2 _pos1, const vec2 _pos2, float t)
{
	/*
		sin((1-t)Θ)*a  + sin(t*Θ) * b
		  sin(Θ)		sin(Θ)	
	*/
	t = glm::clamp(t, 0.f, 1.f);

	const vec2 normalizedPos1 = glm::normalize(_pos1);
	const vec2 normalizedPos2 = glm::normalize(_pos2);

	const float theta = glm::acos(glm::dot(normalizedPos1, normalizedPos2));
	
	const float T1 = glm::sin((1 - t) * theta) / glm::sin(theta);
	const float T2 = glm::sin((t) * theta) / glm::sin(theta);
	const vec2 slerpedVec = normalizedPos1 * T1 + normalizedPos2 * T2;
	// slerpedVec [0, 1]

	return glm::length(_pos1) * slerpedVec;
}
