/*
author : 변한빛
description : 박스2D 메쉬를 만드는 소스 파일

version: 1.0.0
date: 2024-11-04
*/

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
    HRect rect = {-0.5f, 0.5f, 0.5f, -0.5f};
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
