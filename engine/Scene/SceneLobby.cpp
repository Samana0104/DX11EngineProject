/*
author : ���Ѻ�
description : ���� ��ȯ�� �׽�Ʈ �ϱ� ���� ���� ����

version: 1.0.0
date: 2024-11-04
*/

#include "pch.h"
#include "SceneLobby.h"
using namespace HBSoft;

SceneLobby::SceneLobby()
{
    test.m_transform.SetScale({100.f, 100.f});
    test.m_transform.SetLocation({0.f, 0.f});
    test.SetColor({1.f, 0.f, 1.f, 1.f});
}

void SceneLobby::Update(float deltaTime) {}

void SceneLobby::Render()
{
    test.Render();
}

void SceneLobby::Release() {}

void SceneLobby::Reset() {}

void SceneLobby::Start() {}

void SceneLobby::End() {}
