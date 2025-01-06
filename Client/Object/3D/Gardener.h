#pragma once

#include "Core.h"
#include "3D/Object3D.h"
#include "3D/HeightMapObj.h"
#include "3D/Goose.h"
#include "Astar.h"

namespace HBSoft
{
    enum struct State
    {
        Idle,     // 평상시 걷는 상태
        Chasing,  // 거위를 쫓는 상태
        Pushing   // 거위를 밀기 시작한 상태
    };

    enum struct Event
    {
        GooseClose,      // 거위가 가까워짐
        GooseStoleItem,  // 거위가 물건을 훔침
        GooseFar,        // 거위가 멀어짐
        maintain
    };

    class Gardener : public Object3D
    {
    public:
        State currentState;  // 현재 상태

        // 이벤트 처리 함수
        void onEvent(Event event, float deltaTime);


    private:
        std::shared_ptr<Mesh> m_mesh;

        std::vector<mat4> anim;
        float             m_speed2 = 1.5f;

        std::vector<std::vector<std::shared_ptr<Node>>> m_grid;
        std::vector<std::shared_ptr<AnimationClip>>     m_gardenerAni;
        /*std::shared_ptr<Goose>                   m_goose1;*/

        /*inline static const UINT GRID_ROW = 160;
        inline static const UINT GRID_COL = 160;*/
        inline static const UINT GRID_ROW = 81;
        inline static const UINT GRID_COL = 81;

    public:
        Transform3D m_trans;
        Astar       m_astar;
        int         idx = 0;

        float pathIdx_x  = 0;
        float pathIdx_z  = 0;
        float gardener_x = 0;
        float gardener_z = 0;

        float gridLength = 92.16f;
        /*int   gridNum     = 160;
        int   GRID_OFFSET = 80;*/
        int gridNum     = 80;
        int GRID_OFFSET = 40;

        float dx       = 0;
        float dz       = 0;
        float distance = 0;
        bool  forward  = true;

        std::vector<std::pair<int, int>> idlePath = {
            {10, 4},
            { 9, 4},
            { 9, 5},
            {10, 5},
            {10, 6},
            { 9, 6}
        };
        float idlePathX   = 0;
        float idlePathZ   = 0;
        int   idlePathIdx = 0;
        vec3  velocity    = {0.f, 0.f, 0.f};
        /*GardenerFSM gardenerFSM;*/
        std::shared_ptr<Goose> m_goose1;

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