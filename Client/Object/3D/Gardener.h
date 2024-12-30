#pragma once

#include "Core.h"
#include "3D/Object3D.h"
#include "3D/HeightMapObj.h"
#include "3D/Goose.h"
#include "Astar.h"

namespace HBSoft
{
    class Gardener : public Object3D
    {
    private:
        std::shared_ptr<Mesh> m_mesh;

        std::vector<mat4> anim;
        float             m_speed2 = 1.5f;

        std::vector<std::shared_ptr<AnimationClip>> m_gardenerAni;

    public:
        Gardener();

        virtual void Update(const float deltaTime) override;
        virtual void Render() override;
        virtual void Init();
        virtual void Release();

        Goose m_goose1;

        Transform3D m_trans;
        Astar       m_astar;
        int         idx = 0;

        float pathIdx_x  = 0;
        float pathIdx_z  = 0;
        float gardener_x = 0;
        float gardener_z = 0;

        float gridLength = 61.44f;
        int   gridNum    = 40;

        float GetLocationX();
        float GetLocationZ();

        int  GRID_OFFSET = 20;
        vec3 GetmPos();
        void SetmPos(float a, float b);
    };


}  // namespace HBSoft