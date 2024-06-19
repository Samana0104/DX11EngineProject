#include "pch.h"
#include "MyCamera.h"
using namespace MyProject;

const mat3& MyCamera::GetViewMat() const
{
	return mTransform.GetViewMat();
}

void MyCamera::ZoomInCamera(const float _scale)
{
	mTransform.AddScale({-_scale, -_scale});
}

void MyCamera::ZoomOutCamera(const float _scale)
{
	mTransform.AddScale({_scale, _scale});
}
