#pragma once
#include "MyMesh2D.h"

namespace MyProject
{
	class MyBox2D : public MyMesh2D
	{
	public:
		MyBox2D(POINT_F _rectSize);

		virtual void UpdateComponent() override;
		virtual void RenderComponent() override;
	};
}

