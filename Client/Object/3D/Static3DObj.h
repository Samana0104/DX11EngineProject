/*
author : 이지혁
description : 정적인 오브젝트를 관리하는 헤더 파일

version: 1.1.0
date: 2024-12-23
*/
#pragma once

#include "3D/Object3D.h"
#include "3D/Transform3D.h"

namespace HBSoft
{
    enum class StaticTransformType
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
        DirtRightLow1,
        Cabbage0,
        Cabbage1,
        Cabbage2,
        Cabbage3,
    };

    class Static3DObj : public Object3D
    {
    private:
        std::shared_ptr<Mesh> m_mesh;
        std::vector<mat4>     m_anim;
        std::string           m_name;
        std::string           m_key;
        //std::shared_ptr<Texture> m_picnicRugTexture;
        std::shared_ptr<Texture> m_texCube1;
        StaticTransformType            m_transType = StaticTransformType::DefaultTrans;

    public:
        float x     = -7;
        float y     = 0;
        float z     = -12;
        float rotX  = 1.57;
        float rotY  = 0;
        float rotZ  = 0;
        float scale = 1;

        Static3DObj();

        Static3DObj(const std::string& n)
            : m_name(n)
        {}

        float generateRandomValue(float min, float max)
        {
            // Random number generator
            std::random_device                    rd;
            std::mt19937                          gen(rd());
            std::uniform_real_distribution<float> dist(min, max);
            return dist(gen);
        }

        std::string GetName();
        std::string GetKey();
        void        SetTransType(StaticTransformType);
        Transform3D GetTransform();

        virtual void Init();
        void         Init(const std::string&);
        virtual void Update(const float deltaTime) override;
        virtual void Render() override;
        virtual void Release();
    };
}  // namespace HBSoft
