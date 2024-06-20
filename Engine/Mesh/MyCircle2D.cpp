#include "pch.h"
#include "MyCircle2D.h"
using namespace MyProject;

MyCircle2D::MyCircle2D(const size_t _triangles)
	: MyMesh2D(MeshShape::CIRCLE2D)
{
	CreateCircle2DVertex(_triangles);
}

void MyCircle2D::CreateCircle2DVertex(const size_t _triangles)
{
	// 크기 1 반지름 0.5 원
	const float anglePerTriangles = 360.f / static_cast<float>(_triangles);
	float angle = 0.f;
	vec2 pos;

	ReserveVertexSize(_triangles);
	AddVertexAndUV({ 0.f, 0.f }, { 0.5f, 0.5f }); // sphere center
	AddVertexAndUV({ 0.5f, 0.f }, { 1.f, 0.5f }); // sphere center

	for (size_t i = 1; i < _triangles; i++)
	{
		angle = glm::radians(anglePerTriangles * i);
		pos = { 0.5f * glm::cos(angle), 0.5f * glm::sin(angle) };
		AddVertexAndUV(pos, { pos.x + 0.5f, -pos.y + 0.5f });
		AddVertexIndex({ 0, (i + 1), i });
	}

	AddVertexIndex({ 0, 1, _triangles });
	CreateMesh();
}

void MyCircle2D::SetUVVertexAsRect(const RECT_F _rect, MyTexture& _texture)
{
}
