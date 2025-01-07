/*
author : 이지혁
description : 돗자리 오브젝트를 관리하는 헤더 파일

version: 1.1.0
date: 2025-01-07
*/

#pragma once

#include "3D/Object3D.h"
#include "3D/Transform3D.h"

namespace HBSoft
{
    class PicnicRug : public Object3D
    {
    private:
        std::shared_ptr<Mesh> m_mesh;
        std::shared_ptr<Texture> m_picnicRugTexture;
        std::shared_ptr<Texture> m_texCube;

    public:
        PicnicRug();

        virtual void Update(const float deltaTime) override;
        virtual void Render() override;
        virtual void Init();
        virtual void Release();
    };
}  // namespace HBSoft
