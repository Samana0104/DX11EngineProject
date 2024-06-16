#include "pch.h"
#include "Box2D.h"
using namespace MyProject;

Box2D::Box2D(POINT_F _size)
	: MyMesh2D(MeshShape::BOX)
{
	RECT_F rect = { -_size.x / 2, -_size.y / 2, _size.x / 2, _size.y / 2 };
	ReserveVertexSize(4);
	AddVertexAndColorAndUV({rect.left, rect.top}, {1.f, 0.f, 1.f, 1.f}, {0, 0});
	AddVertexAndColorAndUV({rect.right, rect.top}, {1.f, 1.f, 0.f, 1.f}, {1, 0});
	AddVertexAndColorAndUV({rect.left, rect.bottom}, {1.f, 1.f, 1.f, 1.f}, {0, 1});
	AddVertexAndColorAndUV({rect.right, rect.bottom}, {1.f, 1.f, 1.f, 1.f}, {1, 1});
	AddVertexIndex({ 0, 1, 2, 1, 3, 2 });
	_ASSERT(CreateVertexBuffer());
}

void Box2D::UpdateComponent()
{
}

void Box2D::RenderComponent()
{
	MyMesh2D::RenderComponent();
}
