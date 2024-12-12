/*
author : 변한빛
description : 큐브맵을 그리기 위한 클래스 헤더 파일

version: 1.0.8
date: 2024-11-29
*/

#pragma once

#include "3D/Object3D.h"

namespace HBSoft
{
    class CubeMapObj : public Object3D
    {
    private:
        std::shared_ptr<Texture> m_texture;
        std::shared_ptr<Mesh>    m_cubeMesh;

    public:
        CubeMapObj();

        virtual void Render() override;
        virtual void Update(const float deltaTime) override;
        virtual void Release() override;
        virtual void Init() override;
    };

}  // namespace HBSoft
