/*
author : 변한빛
description : 렌더가 가능한 composite&prototype패턴 헤더 파일

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
        // virtual void Clone()   = 0; 프로토타입 패턴을 위해 대비
    };
}  // namespace HBSoft