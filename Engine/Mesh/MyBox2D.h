#pragma once
#include "MyMesh2D.h"

namespace MyProject
{
	class MyBox2D : public MyMesh2D
	{
	public:
		MyBox2D();

		virtual void SetUVVertexAsRange(const RECT_F _rect, MyTexture& _texture) override;
		virtual void Update() override;
	};
}

