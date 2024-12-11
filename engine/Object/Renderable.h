/*
author : ���Ѻ�
description : ������ ������ composite&prototype���� ��� ����

version: 1.0.5
date: 2024-11-17
*/

#pragma once
#include "pch.h"

namespace HBSoft
{
    class Renderable
    {
    protected:
        virtual void Init()                        = 0;
        virtual void Release()                     = 0;
        virtual void Update(const float deltaTime) = 0;
        virtual void Render()                      = 0;
        // virtual void Clone()   = 0; ������Ÿ�� ������ ���� ���
    };
}  // namespace HBSoft