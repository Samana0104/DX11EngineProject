#pragma once

#include "Core.h"
#include "3D/Object3D.h"
#include "3D/Transform3D.h"
#include "3D/HeightMapObj.h"
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
        std::shared_ptr<HSound>                     m_sound;
        std::vector<std::shared_ptr<AnimationClip>> m_gooseAnis;

        float             m_speed1 = 1.f;
        std::vector<mat4> anim;

        GooseState                    m_animstate;
        std::shared_ptr<HeightMapObj> m_mapObj;

        float currentFrame = 0.f;
        int   startFrame   = 0;
        int   lastFrame    = 0;
        float speed1       = 30.f;

        int  tempStartFrame = 0;
        int  tempLastFrame  = 0;
        vec3 moveDirection;
        vec3 moveVec;

        AABB m_gooseStand;
        AABB m_gooseCrounching;

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

        virtual void ProcessCollision(std::shared_ptr<Object3D> obj) override;
    };


}  // namespace HBSoft