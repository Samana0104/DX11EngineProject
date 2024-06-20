#pragma once
#include "MyMesh2D.h"

namespace MyProject
{
	class MyCircle2D : public MyMesh2D
	{
	private:
		void CreateCircle2DVertex(const size_t _triangles);

	public:
		MyCircle2D(const size_t _triangles = 100);

		virtual void SetUVVertexAsRect(const RECT_F _rect, MyTexture& _texture) override;
	};
}


