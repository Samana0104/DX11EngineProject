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
	// ũ�� 1 ������ 0.5 ��
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
	// ũ�� 1 ������ 0.5 ��
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
	// �������� ���� ���� ����
}
