#pragma once
#include "MyMesh2D.h"

namespace MyProject
{
	class Box2D : public MyMesh2D
	{
	public:
		Box2D(POINT_F _size, const std::wstring _textureName);

		virtual void UpdateComponent() override;
		virtual void RenderComponent() override;
		virtual void ReleaseComponent() override;
		virtual bool IsMeshCollision(MyMesh2D& _mesh) override { return true; }
		virtual bool IsRectCollision(RECT_F _rect) override { return true; }
		virtual bool IsSphereCollision(vec2 _center, float _radius) override { return true; }
	};
}

