#include "pch.h"
#include "Box2D.h"
using namespace HBSoft;

Box2D::Box2D()
    : Mesh2D(MeshShape::BOX2D)
{
    CreateBox2DVertex();
}

void Box2D::CreateBox2DVertex()
{
    RECT_F rect = {-0.5f, 0.5f, 0.5f, -0.5f};
    ReserveVertexSize(4);
    AddVertexAndUV({rect.left, rect.top}, {0, 0});
    AddVertexAndUV({rect.right, rect.top}, {1, 0});
    AddVertexAndUV({rect.left, rect.bottom}, {0, 1});
    AddVertexAndUV({rect.right, rect.bottom}, {1, 1});
    AddVertexIndex({0, 1, 2, 1, 3, 2});
    CreateMesh({0.f, 0.f});
}

/*
2D 아니고는 안쓸 방식
*/

void Box2D::SetUVVertexAsRect(const RECT_F& rect, const vec2& imageSize)
{
    SetUVVertex(0, {rect.left / imageSize.x, rect.top / imageSize.y});
    SetUVVertex(1, {rect.right / imageSize.x, rect.top / imageSize.y});
    SetUVVertex(2, {rect.left / imageSize.x, rect.bottom / imageSize.y});
    SetUVVertex(3, {rect.right / imageSize.x, rect.bottom / imageSize.y});
}
