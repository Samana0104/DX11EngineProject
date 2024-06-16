#include "pch.h"
#include "MyBox2D.h"
using namespace MyProject;

MyBox2D::MyBox2D(POINT_F _rectSize)
	: MyMesh2D(MeshShape::BOX2D, _rectSize)
{
	RECT_F rect = { -_rectSize.x / 2, -_rectSize.y / 2, _rectSize.x / 2, _rectSize.y / 2 };
	ReserveVertexSize(4);
	AddVertexAndColorAndUV({rect.left, rect.top}, {1.f, 0.f, 1.f, 1.f}, {0, 0});
	AddVertexAndColorAndUV({rect.right, rect.top}, {1.f, 1.f, 0.f, 1.f}, {1, 0});
	AddVertexAndColorAndUV({rect.left, rect.bottom}, {1.f, 1.f, 1.f, 1.f}, {0, 1});
	AddVertexAndColorAndUV({rect.right, rect.bottom}, {1.f, 1.f, 1.f, 1.f}, {1, 1});
	AddVertexIndex({ 0, 1, 2, 1, 3, 2 });
	_ASSERT(CreateVertexBuffer());
}

void MyBox2D::UpdateComponent()
{
}

void MyBox2D::RenderComponent()
{
	MyMesh2D::RenderComponent();
}
