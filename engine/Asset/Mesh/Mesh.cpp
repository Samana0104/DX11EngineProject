/*
author : 변한빛
description : 메쉬의 기본 리소스를 정의하기 위한 소스 파일

version: 1.0.0
date: 2024-11-08
*/

#include "pch.h"
#include "Mesh.h"
using namespace HBSoft;

Mesh::Mesh(bool hasAnimation)
    : m_hasAnimation(hasAnimation)
{}

Mesh::Mesh(std::shared_ptr<D3Device>& device, const wstringV path) {}
