#include "pch.h"
#include "MyCircle2D.h"
using namespace MyProject;

MyCircle2D::MyCircle2D(const size_t _triangles) : 
	MyMesh2D(MeshShape::CIRCLE2D),
	mTriangles(_triangles)
{
	CreateCircle2DVertex();
}

void MyCircle2D::CreateCircle2DVertex()
{
	// 크기 1 반지름 0.5 원
	const float anglePerTriangles = 360.f / static_cast<float>(mTriangles);
	float angle = 0.f;
	vec2 pos;

	ReserveVertexSize(mTriangles);
	AddVertexAndUV({ 0.f, 0.f }, { 0.5f, 0.5f }); // sphere center
	AddVertexAndUV({ 0.5f, 0.f }, { 1.f, 0.5f }); 

	for (size_t i = 1; i < mTriangles; i++)
	{
		angle = glm::radians(anglePerTriangles * i);
		pos = { 0.5f * glm::cos(angle), 0.5f * glm::sin(angle) };
		AddVertexAndUV(pos, { pos.x + 0.5f, -pos.y + 0.5f });
		AddVertexIndex({ 0, (i + 1), i });
	}

	AddVertexIndex({ 0, 1, mTriangles });
	CreateMesh();
}

void MyCircle2D::SetUVVertexAsRect(const RECT_F& _rect, const vec2& _imageSize)
{
	// 크기 1 반지름 0.5 원
	//const float anglePerTriangles = 360.f / static_cast<float>(mTriangles);
	//float angle = 0.f;
	//vec2 pos;

	//ReserveVertexSize(mTriangles);
	//AddVertexAndUV({ 0.f, 0.f }, { 0.5f, 0.5f }); // sphere center
	//AddVertexAndUV({ 0.5f, 0.f }, { 1.f, 0.5f }); 

	//for (size_t i = 1; i < mTriangles; i++)
	//{
	//	angle = glm::radians(anglePerTriangles * i);
	//	pos = { 0.5f * glm::cos(angle), 0.5f * glm::sin(angle) };
	//	AddVertexAndUV(pos, { pos.x + 0.5f, -pos.y + 0.5f });
	//	AddVertexIndex({ 0, (i + 1), i });
	//}

	//AddVertexIndex({ 0, 1, mTriangles });
	//CreateMesh();
	// 귀찮으니 추후 구현 예정
}

