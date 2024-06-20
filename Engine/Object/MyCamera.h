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

		void ZoomInCamera(const float _scale);
		void ZoomOutCamera(const float _scale);
	};
}

