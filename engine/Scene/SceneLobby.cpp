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
    : cameraTest(90, 1.f, 10000.f)
{}

void SceneLobby::Update(float deltaTime)
{
    test.Update(deltaTime);
}

void SceneLobby::Render()
{
    test.Render();
}

void SceneLobby::Release() {}

void SceneLobby::Start() {}

void SceneLobby::End() {}
