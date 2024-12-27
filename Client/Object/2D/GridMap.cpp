/*
author : Á¤Âùºó
description : ±×¸®µå¸Ê °»

version: 1.0.4
date: 2024-12-11
*/


#include "pch.h"
#include "GridMap.h"

using namespace HBSoft;

GridMap::GridMap()
{
    m_gridMesh = HASSET->m_meshes[L"GRID"];
    m_easyRender.SetVSShader(L"BasicVS.hlsl");
    m_easyRender.SetPSShader(L"ColorPS.hlsl");
    m_easyRender.SetMesh(m_gridMesh);
}

void GridMap::Update(const float deltaTime)
{
    m_transform.SetRotation(vec3(1.f, 0.f, 0.f), glm::radians(90.f));
    UpdateDefaultCB();
}

void GridMap::Render()
{
    m_easyRender.Draw();
}

void GridMap::Init() {}

void GridMap::Release() {}
