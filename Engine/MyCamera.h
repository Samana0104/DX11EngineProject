#pragma once
#include "MyTransformer2D.h"

namespace MyProject
{
	class MyCamera
	{
	public:
		MyTransformer2D mTransform;
		
	public:
		const mat3x3& GetViewMat() const;
	};
}

