#pragma once
#include "Object.h"

namespace HBSoft
{
	class MyCamera
	{
	public:
		Transform2D mTransform;

	public:
		const mat3 GetViewMat() const;

		void ZoomIn(const float _scale);
		void ZoomOut(const float _scale);

		void LookAtObject(Object & _obj);
	};
}

