#include "pch.h"
#include "MyCamera.h"
#include "pch.h"
using namespace MyProject;

const mat3x3& MyCamera::GetViewMat() const
{
	return mTransform.GetViewMat();
}
