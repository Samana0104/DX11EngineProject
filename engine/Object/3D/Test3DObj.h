#pragma once

#include "Object3D.h"
#include "Transform3D.h"

namespace HBSoft
{
    class Test3DObj : public Object3D
    {
    private:
        std::shared_ptr<Mesh> m_mesh;

        std::vector<mat4> anim;


        AABB aabb_goose;

    public:
        Test3DObj();

        virtual void Update(const float deltaTime) override;
        virtual void Render() override;
        virtual void Init();
        virtual void Release();
        AABB         GetaabbCollider();
    };
}  // namespace HBSoft
