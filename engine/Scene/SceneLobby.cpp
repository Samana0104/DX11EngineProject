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
    : cameraTest(glm::radians(90.f), 0.1f, 10000.f)
{}

void SceneLobby::Update(float deltaTime)
{
    cameraTest.Update(deltaTime);
    test.Update(deltaTime);
    test.SetMatrix(cameraTest.GetViewMat(), cameraTest.GetProjMat());
}

void SceneLobby::Render()
{
    test.Render();
}

void SceneLobby::Release() {}

void SceneLobby::Start() {}

void SceneLobby::End() {}
