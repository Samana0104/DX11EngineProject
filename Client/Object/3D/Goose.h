/*
author : 정찬빈, 이지혁
description : Goose 오브젝트를 정의하기 위한 헤더 파일
              1.1.1 - 사운드 추가 (이지혁)

version: 1.1.1
date: 2024-11-30
*/

#pragma once

#include "Core.h"
#include "3D/Object3D.h"
#include "3D/Transform3D.h"
#include "3D/HeightMapObj.h"
#include "3D/Dynamic3DObj.h"
#include "Test3DObj.h"
#include "CollisionComponent.h"
#include "Sound/HSound.h"

namespace HBSoft
{
    enum GooseState
    {
        fancywalk = 0,
        gooseGallop,
        gooseGallopDown,
        gooseSneakIdle,
        goose_idle_proud,
        angryflapping,
        gooseMouthOpen,
        gooseHalfFlap,
        gooseHalfFlapWalking,
        gooseGallopDownHalfFlap,
        gooseSneakIdleHalfFlap
    };

    class Goose : public Object3D
    {
    private:
        std::shared_ptr<Mesh>                       m_mesh;
        std::shared_ptr<Object3D>                   m_socketObj;
        std::shared_ptr<HSound>                     m_sound;
        std::shared_ptr<HSound>                     m_soundFootstep_2_5;
        std::shared_ptr<HSound>                     m_soundFootstep_3_0;
        std::shared_ptr<HSound>                     m_grabSound;
        std::vector<std::shared_ptr<AnimationClip>> m_gooseAnis;

        float             m_speed1 = 1.f;
        std::vector<mat4> anim;

        GooseState                    m_animstate;
        std::shared_ptr<HeightMapObj> m_mapObj;

        float currentFrame = 0.f;
        int   startFrame   = 0;
        int   lastFrame    = 0;
        float speed1       = 30.f;

        int tempStartFrame = 0;
        int tempLastFrame  = 0;
        int m_socketBornIdx;

        vec3 m_moveDirection;
        vec3 moveVec;

        AABB m_gooseStand;
        AABB m_gooseCrounching;

        bool m_isInit;
        bool m_isInit2;

    public:
        bool m_isGameClear = false;

    public:
        Goose();

        virtual void Update(const float deltaTime) override;
        virtual void Render() override;
        virtual void Release() override;
        virtual void Init() override;

        float GetLocationX();
        float GetLocationZ();

        vec3 GetPos();
        void SetHeightMap(std::shared_ptr<HeightMapObj> mapObj);
        void SetSocket(std::shared_ptr<Object3D> socketObj);
        void UnSocket();

        bool HasSocket() const;

        virtual void ProcessCollision(std::shared_ptr<Object3D> obj) override;
    };


}  // namespace HBSoft