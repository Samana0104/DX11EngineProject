#pragma once
#include "MyTransformer2D.h"

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
	};
}

