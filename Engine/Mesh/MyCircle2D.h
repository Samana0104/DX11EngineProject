#pragma once
#include "MyMesh2D.h"

namespace MyProject
{
	class MyCircle2D : public MyMesh2D
	{
	private:
		size_t mTriangles;

	private:
		void CreateCircle2DVertex();

	public:
		MyCircle2D(const size_t _triangles = 50);

		virtual void SetUVVertexAsRect(const RECT_F& _rect, const vec2& _imageSize) override;
	};
}


