#pragma once

#include "3D/Object3D.h"
#include "3D/Transform3D.h"

namespace HBSoft
{
    class PlanterFenceGrass : public Object3D
    {
    private:
        std::shared_ptr<Mesh> m_mesh;
        std::vector<mat4> anim;
        float                 m_scale = 100.0f;
        float                 m_transX = -7.0f;
        float                 m_transY = 0.0f;
        float                 m_transZ = -12.0f;


    public:
        PlanterFenceGrass();

        virtual void Update(const float deltaTime) override;
        virtual void Render() override;
        virtual void Init();
        virtual void Release();
    };
}