#pragma once
#include "Mesh2D.h"

namespace HBSoft
{
	class Box2D : public Mesh2D
	{
	private:
		void CreateBox2DVertex();

	public:
		Box2D();

		virtual void SetUVVertexAsRect(const RECT_F& _rect, const vec2& _imageSize) override;
	};
}

