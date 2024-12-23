#pragma once

#include "Core.h"
#include "Shader/ConstantBuffers.h"
#include "3D/Transform3D.h"
#include "3D/Object3D.h"
#include "3D/HeightMapObj.h"

namespace HBSoft
{

    class Gardener : public Object3D
    {
    private:
        std::shared_ptr<Mesh>          m_mesh;
        std::shared_ptr<AnimationClip> m_animation;

        std::vector<mat4> anim;

        float m_speed2 = 1.0f;

    public:
        Gardener();

        virtual void Update(const float deltaTime) override;
        virtual void Render() override;
        virtual void Init();
        virtual void Release();
    };


}  // namespace HBSoft