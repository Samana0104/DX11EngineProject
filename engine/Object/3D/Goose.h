#pragma once

#include "Core.h"
#include "3D/Object3D.h"
#include "3D/Transform3D.h"
#include "Shader/ConstantBuffers.h"
#include "HeightMapObj.h"

namespace HBSoft
{
    class Goose : public Object3D
    {
    private:
        std::shared_ptr<Mesh> m_mesh;
        float                 m_speed1 = 1.0f;
        std::vector<mat4>     anim;
        AABB                  aabb_goose;


    public:
        Goose();

        virtual void Update(const float deltaTime) override;
        virtual void Render() override;
        virtual void Release() override;
        virtual void Init() override;

        float GetLocationX();
        float GetLocationZ();
        AABB  GetaabbCollider();

        vec3 GetGooseTransform();
    };


}  // namespace HBSoft