#pragma once
#include "MyMesh2D.h"

namespace MyProject
{
	class MyBox2D : public MyMesh2D
	{
	private:
		void CreateBox2DVertex();

	public:
		MyBox2D();

		virtual void SetUVVertexAsRect(const RECT_F& _rect, const vec2& _imageSize) override;
	};
}

