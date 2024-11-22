/*
author : ���Ѻ�
description : ������ �׸��� ���� Ŭ���� ��� ����

version: 1.0.7
date: 2024-11-12
*/

#pragma once

#include "Object3D.h"

namespace HBSoft
{
    class LineObj : public Object3D
    {
    private:
        virtual void Render() {}

    public:
        LineObj();

        void Draw(vec3 start, vec3 end, vec4 color);
    };

}  // namespace HBSoft
