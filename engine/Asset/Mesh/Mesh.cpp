/*
author : ���Ѻ�
description : �޽��� �⺻ ���ҽ��� �����ϱ� ���� �ҽ� ����

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
