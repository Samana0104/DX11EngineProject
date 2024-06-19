#include "pch.h"
#include "MyBox2D.h"
using namespace MyProject;

MyBox2D::MyBox2D() : 
	MyMesh2D(MeshShape::BOX2D)
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
2D 아니고는 안쓸 방식;;;
*/
void MyBox2D::SetUVVertexAsRange(const RECT_F _rect, MyTexture& _texture)
{
	vec2 imageSize = _texture.GetTextureSizeVec2();
	SetUVVertex(0, { _rect.left / imageSize.x, _rect.top / imageSize.y });
	SetUVVertex(1, { _rect.right / imageSize.x, _rect.top / imageSize.y });
	SetUVVertex(2, { _rect.left / imageSize.x, _rect.bottom / imageSize.y });
	SetUVVertex(3, { _rect.right / imageSize.x, _rect.bottom / imageSize.y });
}

void MyBox2D::Update()
{
}
