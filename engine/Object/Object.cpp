/*
author : ���Ѻ�
description : Object�� �⺻ ���� �ҽ�����

version: 1.0.4
date: 2024-12-13
*/

#include "pch.h"
#include "Object.h"
using namespace HBSoft;

void Object::SetCamera(std::shared_ptr<Camera> camera)
{
    m_camera = camera;
}
