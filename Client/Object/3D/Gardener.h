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

        std::vector<std::vector<std::shared_ptr<Node>>> m_grid;
        std::vector<std::shared_ptr<AnimationClip>>     m_gardenerAni;
        std::shared_ptr<Goose>                          m_goose1;

        inline static const UINT GRID_ROW = 160;
        inline static const UINT GRID_COL = 160;

    public:
        Transform3D m_trans;
        Astar       m_astar;
        int         idx = 0;

        float pathIdx_x  = 0;
        float pathIdx_z  = 0;
        float gardener_x = 0;
        float gardener_z = 0;

        float gridLength  = 92.160003584f;
        int   gridNum     = 160;
        int   GRID_OFFSET = 80;

    public:
        Gardener();

        virtual void Update(const float deltaTime) override;
        virtual void Render() override;
        virtual void Init();
        virtual void Release();

        float GetLocationX();
        float GetLocationZ();

        vec3 GetPos();
        void SetPos(float a, float b);

        void SetGooseObj(std::shared_ptr<Goose> gooseObj);
        /*std::vector<std::vector<std::shared_ptr<Node>>> grid;*/
    };


}  // namespace HBSoft