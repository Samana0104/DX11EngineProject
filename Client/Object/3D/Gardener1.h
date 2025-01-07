#pragma once

#include "Core.h"
#include "3D/Object3D.h"
#include "3D/HeightMapObj.h"
#include "3D/Goose.h"
#include "Astar.h"
#include "Input.h"

namespace HBSoft
{
    enum GardenerState1
    {
        walking1,
        working1,
        watering1,
        surprised1,
        stopwalking1,
        slowrun1,
        breathingidle1,
        kick1,
        leftturn1,
        pickingup1,
        rightturn1,
        gettingup1,
        stretching1,
    };

    enum struct State1
    {
        Idle,     // 평상시 걷는 상태
        Chasing,  // 거위를 쫓는 상태
        Pushing   // 거위를 밀기 시작한 상태
    };

    enum struct Event1
    {
        GooseClose,      // 거위가 가까워짐
        GooseStoleItem,  // 거위가 물건을 훔침
        GooseFar,        // 거위가 멀어짐
        maintain
    };

    class Gardener1 : public Object3D
    {
    public:
        State1 currentState;  // 현재 상태

        // 이벤트 처리 함수
        void  onEvent(Event1 event, float deltaTime);
        float speed = 14.f;

    private:
        std::shared_ptr<Mesh> m_mesh;

        std::vector<mat4> anim;
        /*float             m_speed2 = 1.5f;*/

        std::vector<std::vector<std::shared_ptr<Node>>> m_grid;
        std::vector<std::shared_ptr<AnimationClip>>     m_gardenerAni;

        GardenerState1                m_animstate;
        std::shared_ptr<HeightMapObj> m_mapObj;

        inline static const UINT GRID_ROW = 161;
        inline static const UINT GRID_COL = 161;

        float m_currentFrame = 0.f;
        int   m_startFrame   = 0;
        int   m_lastFrame    = 0;
        bool  m_isPlaying    = false;

    public:
        Transform3D m_trans;
        Astar       m_astar;
        int         idx = 0;

        float pathIdx_x  = 0;
        float pathIdx_z  = 0;
        float gardener_x = 0;
        float gardener_z = 0;

        float gridLength  = 92.16f;
        int   gridNum     = 160;
        int   GRID_OFFSET = 80;

        float dx       = 0;
        float dz       = 0;
        float distance = 0;
        bool  forward  = true;

        bool goosestole = false;

        std::vector<std::pair<int, int>> idlePath = {
            {88, 89},
            {87, 89},
            {86, 89},
            {85, 89},
            {84, 89},
            {83, 89},
            {82, 89},
            {81, 89},
            {80, 89},
            {79, 89},
            {78, 89},
            {77, 89},
            {76, 89},
            {75, 89},
            {74, 89},
            {73, 89},
            {72, 89},
            {71, 89},
            {70, 89},
        };

        float idlePathX   = 0;
        float idlePathZ   = 0;
        int   idlePathIdx = 0;

        float idlePathIdx_x  = 0;
        float idlePathIdx_z  = 0;
        float idleGardener_x = 0;
        float idleGardener_z = 0;

        vec3                   velocity = {0.f, 0.f, 0.f};
        std::shared_ptr<Goose> m_goose1;

    public:
        Gardener1();

        virtual void Update(const float deltaTime) override;
        virtual void Render() override;
        virtual void Init();
        virtual void Release();

        float GetLocationX();
        float GetLocationZ();

        vec3 GetPos();
        void SetPos(float a, float b);

        void SetGooseObj(std::shared_ptr<Goose> gooseObj);

        void SetGridObstacle();

        void SetHeightMap(std::shared_ptr<HeightMapObj> mapObj);
    };


}  // namespace HBSoft