#include "pch.h"
#include "MyBox2D.h"
using namespace MyProject;

MyBox2D::MyBox2D() :
	MyMesh2D(MeshShape::BOX2D)
{
	CreateBox2DVertex();
}

void MyBox2D::CreateBox2DVertex()
{
	RECT_F rect = {-0.5f, 0.5f, 0.5f, -0.5f};
	ReserveVertexSize(4);
	AddVertexAndUV({rect.left, rect.top}, {0, 0});
	AddVertexAndUV({rect.right, rect.top},  {1, 0});
	AddVertexAndUV({rect.left, rect.bottom}, {0, 1});
	AddVertexAndUV({rect.right, rect.bottom}, {1, 1});
	AddVertexIndex({ 0, 1, 2, 1, 3, 2 });
	CreateMesh({ 0.f, 0.f });
}

/*
2D 아니고는 안쓸 방식
*/

void MyBox2D::SetUVVertexAsRect(const RECT_F& _rect, const vec2& _imageSize)
{
	SetUVVertex(0, { _rect.left / _imageSize.x, _rect.top / _imageSize.y });
	SetUVVertex(1, { _rect.right / _imageSize.x, _rect.top / _imageSize.y });
	SetUVVertex(2, { _rect.left / _imageSize.x, _rect.bottom / _imageSize.y });
	SetUVVertex(3, { _rect.right / _imageSize.x, _rect.bottom / _imageSize.y });
}
