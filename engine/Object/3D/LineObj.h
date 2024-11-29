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
        std::shared_ptr<Mesh> m_mesh;

    private:
        virtual void Render() override;
        virtual void Init() override;
        virtual void Release() override;

    public:
        LineObj();

        virtual void Update(const float deltaTime);
        void         Draw(vec3 start, vec3 end, vec4 color);
    };

}  // namespace HBSoft
