#pragma once

#include "Core.h"
#include "Object3D.h"
#include "Transform3D.h"
#include "Shader/ConstantBuffers.h"
#include "3D/HeightMapObj.h"

namespace HBSoft
{

    class Gardener : public Object3D
    {
    private:
        std::shared_ptr<Mesh> m_mesh;

        std::vector<mat4> anim;

        float m_speed2 = 1.0f;
        AABB  aabb_gardener;

        // std::shared_ptr<HeightMapObj> m_heightmap;

    public:
        Gardener();

        virtual void Update(const float deltaTime) override;
        virtual void Render() override;
        virtual void Init();
        virtual void Release();
        AABB         GetaabbCollider();
    };


}  // namespace HBSoft