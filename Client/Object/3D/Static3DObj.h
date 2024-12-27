/*
author : 이지혁
description : 정적인 오브젝트를 관리하는 헤더 파일

version: 1.1.0
date: 2024-12-23
*/
#pragma once

#include "3D/Object3D.h"
#include "3D/Transform3D.h"
#include "CollisionComponent.h"

namespace HBSoft
{
    enum class TransformType
    {
        DefaultTrans,
        GooseGameTrans,
        UnityTrans
    };

    class Static3DObj : public Object3D
    {
    private:
        std::shared_ptr<Mesh>    m_mesh;
        std::shared_ptr<Texture> m_cubeTex;

        std::vector<mat4> m_anim;
        std::string       m_name;
        TransformType     m_transType = TransformType::DefaultTrans;

    public:
        CollisionComponent m_component;


    public:
        Static3DObj();

        Static3DObj(const std::string& n)
            : m_name(n), m_component(m_transform)
        {}

        std::string GetName();
        void        SetTransType(TransformType);

        virtual void Update(const float deltaTime) override;
        virtual void Render() override;
        virtual void Init();
        void         Init(const std::wstring&);
        virtual void Release();
    };
}  // namespace HBSoft
