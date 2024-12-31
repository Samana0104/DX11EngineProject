#pragma once

#include "Core.h"
#include "3D/Object3D.h"
#include "3D/HeightMapObj.h"
#include "3D/Goose.h"
#include "Astar.h"
#include "GardenerFSM.h"

namespace HBSoft
{
    class Gardener : public Object3D
    {
    private:
        std::shared_ptr<Mesh> m_mesh;

        std::vector<mat4> anim;

        float                                       m_speed2 = 0.5f;
        std::vector<std::shared_ptr<AnimationClip>> m_gardenerAni;

    public:
        Gardener();

        virtual void Update(const float deltaTime) override;
        virtual void Render() override;
        virtual void Init();
        virtual void Release();

        std::shared_ptr<Goose> m_goose;
        /*Goose m_goose1;*/

        Transform3D m_trans;
        Astar       m_astar;
        int         idx = 0;

        float pathIdx_x  = 0;
        float pathIdx_z  = 0;
        float gardener_x = 0;
        float gardener_z = 0;

        /*float gridLength = 61.44f;*/
        float gridLength = 61.44f;
        int   gridNum    = 40;


        float GetLocationX();
        float GetLocationZ();

        int  GRID_OFFSET = 20;
        vec3 GetmPos();
        void SetmPos(float a, float b);


        void patrol();
        void pushGoose();
        void chaseGoose();

        std::vector<std::pair<int, int>> movepath = {
            {0, 1},
            {0, 2}, // 첫 번째 구간
            {1, 2},
            {1, 1},
            {1, 0}, // 두 번째 구간
            {2, 0},
            {2, 1},
            {2, 2}, // 세 번째 구간
        };

        int posIdx = 0;
    };


}  // namespace HBSoft