/*
author : 변한빛
description : Collision 모음 소스파일

version: 1.0.0
date: 2024-12-29
*/
#include "pch.h"
#include "Collision.h"
using namespace HBSoft;

void Plane::Set(vec3 v0, vec3 v1, vec3 v2)
{
    vec3 e0 = v1 - v0;
    vec3 e1 = v2 - v0;
    vec3 normal;
    normal = glm::cross(e0, e1);
    normal = glm::normalize(normal);

    a = normal.x;
    b = normal.y;
    c = normal.z;
    d = -glm::dot(normal, v0);
}

void Plane::Set(vec3 v0, vec3 normal)
{
    a = normal.x;
    b = normal.y;
    c = normal.z;
    d = -glm::dot(normal, v0);
}
