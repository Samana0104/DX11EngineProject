/*
author : 이지혁
description(이지혁) : mapObjects 를 배치하기 위한 헤더

version: 1.0.0
date: 2024-12-2
*/

#pragma once

#include "Object3D.h"

namespace HBSoft
{
    class Test3DObj : public Object3D
    {
    private:
        std::shared_ptr<Mesh> m_mesh;

        std::vector<mat4> anim;

    public:
        Test3DObj();

        virtual void Update(const float deltaTime) override;
        virtual void Render() override;
        virtual void Init();
        virtual void Release();
    };
}  // namespace HBSoft
