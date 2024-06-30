#include "pch.h"
#include "MyCamera.h"
using namespace MyProject;

const mat3 MyCamera::GetViewMat() const
{
	return mTransform.GetViewMat();
}

void MyCamera::ZoomIn(const float _scale)
{
	mTransform.AddScale({-_scale, -_scale});
}

void MyCamera::ZoomOut(const float _scale)
{
	mTransform.AddScale({_scale, _scale});
}

void MyCamera::LookAtObject(MyObject& _obj)
{
	mTransform.SetLocation(_obj->GetLocation());
}

void MyCamera::Update(const float _deltaTime)
{
}

void MyCamera::Render()
{
}
