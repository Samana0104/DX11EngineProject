#pragma once

#include "Core.h"
#include "3D/Object3D.h"
#include "3D/HeightMapObj.h"
#include "3D/Goose.h"
#include "Astar.h"

namespace HBSoft
{
    enum GardenerState2
    {
        walking2,
        working2,
        watering2,
        surprised2,
        stopwalking2,
        slowrun2,
        breathingidle2,
        kick2,
        leftturn2,
        pickingup2,
        rightturn2,
        gettingup2,
        stretching2,
    };

    enum struct State2
    {
        Idle,     // ���� �ȴ� ����
        Chasing,  // ������ �Ѵ� ����
        Pushing   // ������ �б� ������ ����
    };

    enum struct Event2
    {
        GooseClose,      // ������ �������
        GooseStoleItem,  // ������ ������ ��ħ
        GooseFar,        // ������ �־���
        maintain
    };

    class Gardener2 : public Object3D
    {
    public:
        State2 currentState;  // ���� ����

        // �̺�Ʈ ó�� �Լ�
        void onEvent(Event2 event, float deltaTime);

        float speed = 0.f;

    private:
        std::shared_ptr<Mesh> m_mesh;

        std::vector<mat4> anim;
        /* float             m_speed2 = 1.5f;*/

        std::vector<std::vector<std::shared_ptr<Node>>> m_grid;
        std::vector<std::shared_ptr<AnimationClip>>     m_gardenerAni;

        GardenerState2                m_animstate;
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
            {81, 85},
            {82, 85},
            {83, 85},
            {84, 85},
            {85, 85},
            {86, 85},
            {87, 85},
            {88, 85},
            {89, 85}
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
        Gardener2();

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