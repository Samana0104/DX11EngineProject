#pragma once

#include "Core.h"
#include "3D/Object3D.h"
#include "3D/HeightMapObj.h"
#include "3D/Goose.h"
#include "Astar.h"

namespace HBSoft
{
    enum GardenerState
    {
        walking,
        working,
        watering,
        surprised,
        stopwalking,
        slowrun,
        breathingidle,
        kick,
        leftturn,
        pickingup,
        rightturn,
        gettingup,
        stretching,
    };

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

        float speed = 0;

    private:
        std::shared_ptr<Mesh> m_mesh;

        std::vector<mat4> anim;
        /*  float             m_speed2 = 100.f;*/

        std::vector<std::vector<std::shared_ptr<Node>>> m_grid;
        std::vector<std::shared_ptr<AnimationClip>>     m_gardenerAni;

        GardenerState                 m_animstate;
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
        int         idx  = 0;
        int         idx1 = 0;

        float pathIdx_x  = 0;
        float pathIdx_z  = 0;
        float gardener_x = 0;
        float gardener_z = 0;

        float pathIdx_x1  = 0;
        float pathIdx_z1  = 0;
        float gardener_x1 = 0;
        float gardener_z1 = 0;

        float gridLength  = 92.16f;
        int   gridNum     = 160;
        int   GRID_OFFSET = 80;

        float dx       = 0;
        float dz       = 0;
        float distance = 0;
        bool  forward  = true;

        bool goosestole = false;

        std::vector<std::pair<int, int>> idlePath = {
            {79, 81},
            {80, 81},
            {81, 81},
            {82, 81},
            {83, 81},
            {84, 81},
            {85, 81},
            {86, 81},
            {87, 81},
            {88, 81},
            {89, 81},
            {90, 81}
        };

        float idlePathX   = 0;
        float idlePathZ   = 0;
        int   idlePathIdx = 0;

        float idlePathIdx_x  = 0;
        float idlePathIdx_z  = 0;
        float idleGardener_x = 0;
        float idleGardener_z = 0;

        int gardenerIdleX = 0;
        int gardenerIdleZ = 0;
        int pathIdleX     = 0;
        int pathIdleZ     = 0;


        vec3                   velocity = {0.f, 0.f, 0.f};
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

        void SetGridObstacle();

        void SetHeightMap(std::shared_ptr<HeightMapObj> mapObj);
    };


}  // namespace HBSoft