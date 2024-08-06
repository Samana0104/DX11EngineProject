#pragma once
#include "MyObject.h"

namespace MyProject
{
	class MyCamera
	{
	public:
		MyTransformer2D mTransform;

	public:
		const mat3 GetViewMat() const;

		void ZoomIn(const float _scale);
		void ZoomOut(const float _scale);

		void LookAtObject(MyObject & _obj);
	};
}

