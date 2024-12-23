/*
author : 이지혁
description : 정적인 오브젝트를 관리하는 헤더 파일

version: 1.1.0
date: 2024-12-23
*/
pragma once

#include "3D/Object3D.h"
#include "3D/Transform3D.h"

namespace HBSoft
{
    enum class TransformType
    {
        OriginalTrans,
        UnityTrans
    };

    class Static3DObj : public Object3D
    {
    private:
        std::shared_ptr<Mesh> m_mesh;

        std::vector<mat4> anim;


    public:
        Static3DObj();

        virtual void Update(const float deltaTime) override;
        void         Update(const float deltaTime, TransformType transType);
        virtual void Render() override;
        virtual void Init();
        void         Init(const std::wstring&);
        virtual void Release();
    };
}  // namespace HBSoft
