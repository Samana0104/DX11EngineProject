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
        CMTrans,
        UnityTrans,
        BackyardTrans,
        FrontHouse,
        Store,
        Test,
        Bollard,
        Parkcube,
        Bench,
        PondRetainers,
        ConcretePath,
        Concrete22,
        Bridge,

    };

    class Static3DObj : public Object3D
    {
    private:
        std::shared_ptr<Mesh> m_mesh;
        std::vector<mat4>     m_anim;
        std::string           m_name;
        std::shared_ptr<Texture> m_picnicRugTexture;
        TransformType         m_transType = TransformType::DefaultTrans;


    public:
        float x = -7;
        float y = 0;
        float z = -12;
        float rotX = 1.57;
        float rotY = 0;
        float rotZ = 0;
        float scale = 1;

        Static3DObj();
        Static3DObj(const std::string& n)
            : m_name(n) {}

        std::string GetName();
        void        SetTransType(TransformType);
        Transform3D GetTransform();

        virtual void Update(const float deltaTime) override;
        void         UpdateLocation(const float deltaTime, float, float, float);
        virtual void Render() override;
        virtual void Init();
        void         Init(const std::wstring&);
        virtual void Release();
    };
}  // namespace HBSoft
