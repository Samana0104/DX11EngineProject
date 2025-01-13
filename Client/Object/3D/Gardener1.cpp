/*
author : ������
description :

version: 1.1.5
date: 2025-01-06
*/


#include "pch.h"
#include "Gardener1.h"
using namespace HBSoft;

Gardener1::Gardener1()
    : m_grid(GRID_ROW, std::vector<std::shared_ptr<Node>>(GRID_COL))
{
    m_mesh = HASSET->m_meshes[L"Walking.hbs"];
    m_easyRender.SetMesh(m_mesh);
    m_easyRender.SetVSShader(L"BasicAniVS.hlsl");
    m_easyRender.SetPSShader(L"ColorPS.hlsl");

    anim.resize(m_mesh->m_born.bornIndex.size());

    m_transform.SetScale({0.2f, 0.2f, 0.2f});
    m_transform.SetLocation({3.f, 0.6f, 4.f});

    currentState = State1::Idle;

    for (int x = -GRID_OFFSET; x < GRID_OFFSET; ++x)
    {
        for (int y = -GRID_OFFSET; y < GRID_OFFSET; ++y)
        {
            m_grid[x + GRID_OFFSET][y + GRID_OFFSET] = std::make_shared<Node>(x, y);  // make_shared ���
        }
    }

    SetGridObstacle();

    /*m_transform.SetScale({0.2f, 0.2f, 0.2f});*/
    /* m_heightmap = std::make_shared<HeightMapObj>();*/
    m_gardenerAni.push_back(HASSET->m_animations[L"walking.skm"]);
    m_gardenerAni.push_back(HASSET->m_animations[L"working.skm"]);
    m_gardenerAni.push_back(HASSET->m_animations[L"watering.skm"]);
    m_gardenerAni.push_back(HASSET->m_animations[L"surprised.skm"]);
    m_gardenerAni.push_back(HASSET->m_animations[L"stopwalking.skm"]);
    m_gardenerAni.push_back(HASSET->m_animations[L"slowrun.skm"]);
    m_gardenerAni.push_back(HASSET->m_animations[L"breathingidle.skm"]);
    m_gardenerAni.push_back(HASSET->m_animations[L"kick.skm"]);
    m_gardenerAni.push_back(HASSET->m_animations[L"leftturn.skm"]);
    m_gardenerAni.push_back(HASSET->m_animations[L"pickingup.skm"]);
    m_gardenerAni.push_back(HASSET->m_animations[L"rightturn.skm"]);
    m_gardenerAni.push_back(HASSET->m_animations[L"gettingup.skm"]);
    m_gardenerAni.push_back(HASSET->m_animations[L"stretching.skm"]);

    m_animstate  = GardenerState1::walking1;
    m_startFrame = m_gardenerAni[m_animstate]->GetStartFrame();
    m_lastFrame  = m_gardenerAni[m_animstate]->GetLastFrame();
}

void Gardener1::Update(const float deltaTime)
{
    /// Walking �ӵ�
    speed = 18.f;
    // static int   selectAnimation = 0;

#ifdef _DEBUG
    ImGui::SliderFloat("Speed", &speed, 0, 30.f);
    /*ImGui::SliderFloat("Gardener speed", &m_speed2, 0.f, 50.f);*/
#endif

    GardenerState1 currentState = GardenerState1::walking1;

    dx       = m_goose1->GetPos().x - m_transform.m_pos[0];
    dz       = m_goose1->GetPos().z - m_transform.m_pos[2];
    distance = sqrt(dx * dx + dz * dz);

    bool isKick = false;

    /// ó�� IDLE
    onEvent(Event1::maintain, deltaTime);

    /// ������ ������� �Ÿ��� 1.f�̸��̸� ����ʰ� ���� �Ѿƿ� // �Ѵ»��·� �ٲ�
    if (distance < 1.8f)
    {
        speed = 0.f;
        onEvent(Event1::GooseClose, deltaTime);
        m_isPlaying = true;
        m_goose1->UnSocket();
    }

    /// ����ʿ� ���� �־����� �ٽ� IDLE
    if (distance > 1.1f)
    {
        onEvent(Event1::GooseFar, deltaTime);
    }
    /* if (m_isPlaying)
     {
         if (m_currentFrame + deltaTime * speed < m_lastFrame)
             currentState = GardenerState::kick;
         else
             m_isPlaying = false;
     }
     else
     {
         currentState = GardenerState::walking;
     }*/


    if (currentState != m_animstate)
    {
        m_startFrame   = m_gardenerAni[currentState]->GetStartFrame();
        m_lastFrame    = m_gardenerAni[currentState]->GetLastFrame();
        m_animstate    = currentState;
        m_currentFrame = 0.f;
    }

    m_currentFrame += deltaTime * speed;


    if (m_currentFrame > m_lastFrame)
        m_currentFrame = m_startFrame;

    anim = m_gardenerAni[m_animstate]->GetAnimationMatrix(m_currentFrame);

    float height = m_mapObj->GetHeight(m_transform.m_pos);
    m_transform.SetLocation({m_transform.m_pos[0], height, m_transform.m_pos[2]});
    UpdateDefaultCB();
    m_easyRender.UpdateVSCB((void*)&anim.at(0), sizeof(mat4) * anim.size(), 1);
}

void Gardener1::Render()
{
    m_easyRender.Draw();
    /*FollowPath(GetPath(path));*/
}

void Gardener1::Init() {}

void Gardener1::Release() {}

float HBSoft::Gardener1::GetLocationX()
{
    return m_transform.m_pos[0];
}

float HBSoft::Gardener1::GetLocationZ()
{
    return m_transform.m_pos[2];
}

vec3 HBSoft::Gardener1::GetPos()
{
    return m_transform.m_pos;
}

void HBSoft::Gardener1::SetPos(float a, float b)
{
    m_transform.m_pos[0] = a;
    m_transform.m_pos[2] = b;
}

void Gardener1::SetGooseObj(std::shared_ptr<Goose> gooseObj)
{
    m_goose1 = gooseObj;
}

void Gardener1::onEvent(Event1 event, float deltaTime)
{
    switch (currentState)
    {
    case State1::Idle:  //(gridLength / gridNum) + (gridLength / gridNum / 2)

        speed = 21.f;
        // ���� Idle �ൿ
        if (idlePathIdx + 1 < idlePath.size())  // size = 6
        {
            idlePathIdx_x =
            (idlePath[idlePathIdx + 1].first - GRID_OFFSET) * (gridLength / gridNum);  // path�� ������ġ
            idlePathIdx_z = (idlePath[idlePathIdx + 1].second - GRID_OFFSET) *
                            (gridLength / gridNum);  // path�� ������ġ

            idleGardener_x = m_transform.m_pos[0];  // ������� ������ġ
            idleGardener_z = m_transform.m_pos[2];  // ������� ������ġ


            if (glm::abs(idleGardener_x - idlePathIdx_x) < 0.4f &&
                glm::abs(idleGardener_z - idlePathIdx_z) < 0.4f)
            {
                idlePathIdx++;
            }
            else
            {
                if (idlePath[idlePathIdx].first - idlePath[idlePathIdx + 1].first > 0 &&
                    idlePath[idlePathIdx].second - idlePath[idlePathIdx + 1].second > 0)
                {
                    m_transform.SetRotation(vec3(0.f, 1.f, 0.f), glm::radians(-45.f));
                }
                else if (idlePath[idlePathIdx].first - idlePath[idlePathIdx + 1].first > 0 &&
                         idlePath[idlePathIdx].second - idlePath[idlePathIdx + 1].second < 0)
                {
                    m_transform.SetRotation(vec3(0.f, 1.f, 0.f), glm::radians(-135.f));
                }
                else if (idlePath[idlePathIdx].first - idlePath[idlePathIdx + 1].first < 0 &&
                         idlePath[idlePathIdx].second - idlePath[idlePathIdx + 1].second > 0)
                {
                    m_transform.SetRotation(vec3(0.f, 1.f, 0.f), glm::radians(45.f));
                }
                else if (idlePath[idlePathIdx].first - idlePath[idlePathIdx + 1].first < 0 &&
                         idlePath[idlePathIdx].second - idlePath[idlePathIdx + 1].second < 0)
                {
                    m_transform.SetRotation(vec3(0.f, 1.f, 0.f), glm::radians(135.f));
                }
                else if (idlePath[idlePathIdx].first - idlePath[idlePathIdx + 1].first == 0 &&
                         idlePath[idlePathIdx].second - idlePath[idlePathIdx + 1].second > 0)
                {
                    m_transform.SetRotation(vec3(0.f, 1.f, 0.f), glm::radians(0.f));
                }
                else if (idlePath[idlePathIdx].first - idlePath[idlePathIdx + 1].first == 0 &&
                         idlePath[idlePathIdx].second - idlePath[idlePathIdx + 1].second < 0)
                {
                    m_transform.SetRotation(vec3(0.f, 1.f, 0.f), glm::radians(180.f));
                }
                else if (idlePath[idlePathIdx].first - idlePath[idlePathIdx + 1].first > 0 &&
                         idlePath[idlePathIdx].second - idlePath[idlePathIdx + 1].second == 0)
                {
                    m_transform.SetRotation(vec3(0.f, 1.f, 0.f), glm::radians(-90.f));
                }
                else if (idlePath[idlePathIdx].first - idlePath[idlePathIdx + 1].first < 0 &&
                         idlePath[idlePathIdx].second - idlePath[idlePathIdx + 1].second == 0)
                {
                    m_transform.SetRotation(vec3(0.f, 1.f, 0.f), glm::radians(90.f));
                }
                m_transform.AddLocation(
                glm::normalize(
                vec3(-(idleGardener_x - idlePathIdx_x), 0.f, -(idleGardener_z - idlePathIdx_z))) *
                deltaTime * 1.5f);
            }
        }
        else
        {
            std::reverse(idlePath.begin(), idlePath.end());
            idlePathIdx = 0;
        }
        if (event == Event1::GooseClose)
        {
            currentState = State1::Chasing;
        }
        else if (event == Event1::maintain)
        {
        }
        break;

    case State1::Chasing:
        // �������� ��ǥ�� ����
        speed         = 25.f;
        int gardenerX = GRID_OFFSET + glm::floor(m_transform.m_pos.x * ((float)gridNum / gridLength));
        int gardenerZ = glm::floor(m_transform.m_pos.z * ((float)gridNum / gridLength)) + GRID_OFFSET;
        int gooseX    = GRID_OFFSET + glm::floor(m_goose1->GetPos().x * ((float)gridNum / gridLength));
        int gooseZ    = glm::floor(m_goose1->GetPos().z * ((float)gridNum / gridLength)) + GRID_OFFSET;


        auto start = m_grid[gardenerX][gardenerZ];  // ����� �����̴� �ſ� ���� ��ǥ
        auto goal  = m_grid[gooseX][gooseZ];        // ���� �����̴� �ſ� ���� ��ǥ

        // A* �˰��� ����

        if (goal->isObstacle)
        {
            if (!m_grid[gooseX][gooseZ + 1]->isObstacle)
                goal = m_grid[gooseX][gooseZ + 1];
            else if (!m_grid[gooseX][gooseZ - 1]->isObstacle)
                goal = m_grid[gooseX][gooseZ - 1];
            else if (!m_grid[gooseX - 1][gooseZ]->isObstacle)
                goal = m_grid[gooseX - 1][gooseZ];
            else if (!m_grid[gooseX + 1][gooseZ]->isObstacle)
                goal = m_grid[gooseX + 1][gooseZ];
        }

        auto path = std::move(m_astar.aStar(start, goal, m_grid));


        if (idx + 1 < path.size())
        {
            pathIdx_x = path[idx + 1]->GetLocationX() * (gridLength / gridNum) +
                        (gridLength / gridNum / 2);  // path�� ������ġ
            pathIdx_z = path[idx + 1]->GetLocationY() * (gridLength / gridNum) +
                        (gridLength / gridNum / 2);  // path�� ������ġ

            gardener_x = m_transform.m_pos[0];  // ������� ������ġ
            gardener_z = m_transform.m_pos[2];  // ������� ������ġ

            if (glm::abs(gardener_x - pathIdx_x) < 0.5f && glm::abs(gardener_z - pathIdx_z) < 0.5f)
            {
                idx++;
            }
            else
            {
                if (path[idx]->GetLocationX() - path[idx + 1]->GetLocationX() > 0 &&
                    path[idx]->GetLocationY() - path[idx + 1]->GetLocationY() > 0)
                {
                    m_transform.SetRotation(vec3(0.f, 1.f, 0.f), glm::radians(-45.f));
                }
                else if (path[idx]->GetLocationX() - path[idx + 1]->GetLocationX() > 0 &&
                         path[idx]->GetLocationY() - path[idx + 1]->GetLocationY() < 0)
                {
                    m_transform.SetRotation(vec3(0.f, 1.f, 0.f), glm::radians(-135.f));
                }
                else if (path[idx]->GetLocationX() - path[idx + 1]->GetLocationX() < 0 &&
                         path[idx]->GetLocationY() - path[idx + 1]->GetLocationY() > 0)
                {
                    m_transform.SetRotation(vec3(0.f, 1.f, 0.f), glm::radians(45.f));
                }
                else if (path[idx]->GetLocationX() - path[idx + 1]->GetLocationX() < 0 &&
                         path[idx]->GetLocationY() - path[idx + 1]->GetLocationY() < 0)
                {
                    m_transform.SetRotation(vec3(0.f, 1.f, 0.f), glm::radians(135.f));
                }
                else if (path[idx]->GetLocationX() - path[idx + 1]->GetLocationX() == 0 &&
                         path[idx]->GetLocationY() - path[idx + 1]->GetLocationY() > 0)
                {
                    m_transform.SetRotation(vec3(0.f, 1.f, 0.f), glm::radians(0.f));
                }
                else if (path[idx]->GetLocationX() - path[idx + 1]->GetLocationX() == 0 &&
                         path[idx]->GetLocationY() - path[idx + 1]->GetLocationY() < 0)
                {
                    m_transform.SetRotation(vec3(0.f, 1.f, 0.f), glm::radians(180.f));
                }
                else if (path[idx]->GetLocationX() - path[idx + 1]->GetLocationX() > 0 &&
                         path[idx]->GetLocationY() - path[idx + 1]->GetLocationY() == 0)
                {
                    m_transform.SetRotation(vec3(0.f, 1.f, 0.f), glm::radians(-90.f));
                }
                else if (path[idx]->GetLocationX() - path[idx + 1]->GetLocationX() < 0 &&
                         path[idx]->GetLocationY() - path[idx + 1]->GetLocationY() == 0)
                {
                    m_transform.SetRotation(vec3(0.f, 1.f, 0.f), glm::radians(90.f));
                }


                m_transform.AddLocation(
                glm::normalize(vec3(-(gardener_x - pathIdx_x), 0.f, -(gardener_z - pathIdx_z))) *
                deltaTime);
            }
        }
        if (event == Event1::GooseFar)
        {
            /*std::cout << "�����簡 ���� �ȴ� ���·� ���ư��ϴ�.\n";*/
            currentState = State1::Idle;
        }
        // else if (event == Event::GooseClose)
        //{
        //     vec3 pushForce  = glm::normalize(vec3(dx / distance, 0.f, dz / distance)) * 3.f;
        //     velocity        = pushForce;
        //     velocity       *= 0.9f;

        //    m_goose1->AddLoc(velocity * deltaTime);
        //    /*std::cout << velocity << std::endl;*/
        //    std::cout << "CHASING : �����簡 ������ �б� �����մϴ�.\n";
        //}
        break;
    }
}

void Gardener1::SetHeightMap(std::shared_ptr<HeightMapObj> mapObj)
{
    m_mapObj = mapObj;
}

void Gardener1::SetGridObstacle()
{
    // ���� ������ ��
    m_grid[-13 + GRID_OFFSET][-2 + GRID_OFFSET]->isObstacle = true;
    m_grid[-13 + GRID_OFFSET][-1 + GRID_OFFSET]->isObstacle = true;
    m_grid[-13 + GRID_OFFSET][GRID_OFFSET]->isObstacle      = true;
    m_grid[-13 + GRID_OFFSET][1 + GRID_OFFSET]->isObstacle  = true;
    m_grid[-13 + GRID_OFFSET][2 + GRID_OFFSET]->isObstacle  = true;
    m_grid[-13 + GRID_OFFSET][3 + GRID_OFFSET]->isObstacle  = true;
    m_grid[-13 + GRID_OFFSET][4 + GRID_OFFSET]->isObstacle  = true;
    m_grid[-13 + GRID_OFFSET][5 + GRID_OFFSET]->isObstacle  = true;
    m_grid[-13 + GRID_OFFSET][6 + GRID_OFFSET]->isObstacle  = true;
    /*  m_grid[-13 + GRID_OFFSET][7 + GRID_OFFSET]->isObstacle  = true;*/

    m_grid[-12 + GRID_OFFSET][-2 + GRID_OFFSET]->isObstacle = true;
    m_grid[-12 + GRID_OFFSET][-1 + GRID_OFFSET]->isObstacle = true;
    m_grid[-12 + GRID_OFFSET][GRID_OFFSET]->isObstacle      = true;
    m_grid[-12 + GRID_OFFSET][1 + GRID_OFFSET]->isObstacle  = true;
    m_grid[-12 + GRID_OFFSET][2 + GRID_OFFSET]->isObstacle  = true;
    m_grid[-12 + GRID_OFFSET][3 + GRID_OFFSET]->isObstacle  = true;
    m_grid[-12 + GRID_OFFSET][4 + GRID_OFFSET]->isObstacle  = true;
    m_grid[-12 + GRID_OFFSET][5 + GRID_OFFSET]->isObstacle  = true;
    m_grid[-12 + GRID_OFFSET][6 + GRID_OFFSET]->isObstacle  = true;
    // m_grid[-12 + GRID_OFFSET][7 + GRID_OFFSET]->isObstacle  = true;

    m_grid[-11 + GRID_OFFSET][-2 + GRID_OFFSET]->isObstacle = true;
    m_grid[-11 + GRID_OFFSET][-1 + GRID_OFFSET]->isObstacle = true;
    m_grid[-11 + GRID_OFFSET][GRID_OFFSET]->isObstacle      = true;
    m_grid[-11 + GRID_OFFSET][1 + GRID_OFFSET]->isObstacle  = true;
    m_grid[-11 + GRID_OFFSET][2 + GRID_OFFSET]->isObstacle  = true;
    m_grid[-11 + GRID_OFFSET][3 + GRID_OFFSET]->isObstacle  = true;
    m_grid[-11 + GRID_OFFSET][4 + GRID_OFFSET]->isObstacle  = true;
    m_grid[-11 + GRID_OFFSET][5 + GRID_OFFSET]->isObstacle  = true;
    m_grid[-11 + GRID_OFFSET][6 + GRID_OFFSET]->isObstacle  = true;
    // m_grid[-11 + GRID_OFFSET][7 + GRID_OFFSET]->isObstacle  = true;

    m_grid[-10 + GRID_OFFSET][-2 + GRID_OFFSET]->isObstacle = true;
    m_grid[-10 + GRID_OFFSET][-1 + GRID_OFFSET]->isObstacle = true;
    m_grid[-10 + GRID_OFFSET][GRID_OFFSET]->isObstacle      = true;
    m_grid[-10 + GRID_OFFSET][1 + GRID_OFFSET]->isObstacle  = true;
    m_grid[-10 + GRID_OFFSET][2 + GRID_OFFSET]->isObstacle  = true;
    m_grid[-10 + GRID_OFFSET][3 + GRID_OFFSET]->isObstacle  = true;
    m_grid[-10 + GRID_OFFSET][4 + GRID_OFFSET]->isObstacle  = true;
    /*  m_grid[-10 + GRID_OFFSET][5 + GRID_OFFSET]->isObstacle  = true;*/

    m_grid[-9 + GRID_OFFSET][-2 + GRID_OFFSET]->isObstacle = true;
    m_grid[-9 + GRID_OFFSET][-1 + GRID_OFFSET]->isObstacle = true;
    m_grid[-9 + GRID_OFFSET][GRID_OFFSET]->isObstacle      = true;
    m_grid[-9 + GRID_OFFSET][1 + GRID_OFFSET]->isObstacle  = true;
    m_grid[-9 + GRID_OFFSET][2 + GRID_OFFSET]->isObstacle  = true;
    m_grid[-9 + GRID_OFFSET][3 + GRID_OFFSET]->isObstacle  = true;
    m_grid[-9 + GRID_OFFSET][4 + GRID_OFFSET]->isObstacle  = true;
    m_grid[-9 + GRID_OFFSET][5 + GRID_OFFSET]->isObstacle  = true;

    m_grid[-8 + GRID_OFFSET][-2 + GRID_OFFSET]->isObstacle = true;
    m_grid[-8 + GRID_OFFSET][-1 + GRID_OFFSET]->isObstacle = true;
    m_grid[-8 + GRID_OFFSET][GRID_OFFSET]->isObstacle      = true;
    m_grid[-8 + GRID_OFFSET][1 + GRID_OFFSET]->isObstacle  = true;
    m_grid[-8 + GRID_OFFSET][2 + GRID_OFFSET]->isObstacle  = true;
    m_grid[-8 + GRID_OFFSET][3 + GRID_OFFSET]->isObstacle  = true;
    m_grid[-8 + GRID_OFFSET][4 + GRID_OFFSET]->isObstacle  = true;
    m_grid[-8 + GRID_OFFSET][5 + GRID_OFFSET]->isObstacle  = true;

    m_grid[-7 + GRID_OFFSET][-2 + GRID_OFFSET]->isObstacle = true;
    m_grid[-7 + GRID_OFFSET][-1 + GRID_OFFSET]->isObstacle = true;
    m_grid[-7 + GRID_OFFSET][GRID_OFFSET]->isObstacle      = true;
    m_grid[-7 + GRID_OFFSET][1 + GRID_OFFSET]->isObstacle  = true;
    m_grid[-7 + GRID_OFFSET][2 + GRID_OFFSET]->isObstacle  = true;
    m_grid[-7 + GRID_OFFSET][3 + GRID_OFFSET]->isObstacle  = true;
    m_grid[-7 + GRID_OFFSET][4 + GRID_OFFSET]->isObstacle  = true;

    m_grid[-6 + GRID_OFFSET][-2 + GRID_OFFSET]->isObstacle = true;
    m_grid[-6 + GRID_OFFSET][-1 + GRID_OFFSET]->isObstacle = true;
    m_grid[-6 + GRID_OFFSET][GRID_OFFSET]->isObstacle      = true;
    m_grid[-6 + GRID_OFFSET][1 + GRID_OFFSET]->isObstacle  = true;
    m_grid[-6 + GRID_OFFSET][2 + GRID_OFFSET]->isObstacle  = true;
    m_grid[-6 + GRID_OFFSET][3 + GRID_OFFSET]->isObstacle  = true;
    // m_grid[-6 + GRID_OFFSET][4 + GRID_OFFSET]->isObstacle  = true;

    m_grid[-5 + GRID_OFFSET][-2 + GRID_OFFSET]->isObstacle = true;
    m_grid[-5 + GRID_OFFSET][-1 + GRID_OFFSET]->isObstacle = true;
    m_grid[-5 + GRID_OFFSET][GRID_OFFSET]->isObstacle      = true;
    m_grid[-5 + GRID_OFFSET][1 + GRID_OFFSET]->isObstacle  = true;
    /*   m_grid[-5 + GRID_OFFSET][2 + GRID_OFFSET]->isObstacle  = true;*/

    m_grid[-4 + GRID_OFFSET][-2 + GRID_OFFSET]->isObstacle = true;
    m_grid[-4 + GRID_OFFSET][-1 + GRID_OFFSET]->isObstacle = true;
    m_grid[-4 + GRID_OFFSET][GRID_OFFSET]->isObstacle      = true;
    m_grid[-4 + GRID_OFFSET][1 + GRID_OFFSET]->isObstacle  = true;
    // m_grid[-4 + GRID_OFFSET][2 + GRID_OFFSET]->isObstacle  = true;

    m_grid[-3 + GRID_OFFSET][-7 + GRID_OFFSET]->isObstacle = true;
    m_grid[-3 + GRID_OFFSET][-6 + GRID_OFFSET]->isObstacle = true;
    m_grid[-3 + GRID_OFFSET][-5 + GRID_OFFSET]->isObstacle = true;
    m_grid[-3 + GRID_OFFSET][-4 + GRID_OFFSET]->isObstacle = true;
    m_grid[-3 + GRID_OFFSET][-3 + GRID_OFFSET]->isObstacle = true;
    m_grid[-3 + GRID_OFFSET][-2 + GRID_OFFSET]->isObstacle = true;
    m_grid[-3 + GRID_OFFSET][-1 + GRID_OFFSET]->isObstacle = true;
    m_grid[-3 + GRID_OFFSET][GRID_OFFSET]->isObstacle      = true;
    m_grid[-3 + GRID_OFFSET][1 + GRID_OFFSET]->isObstacle  = true;
    // m_grid[-3 + GRID_OFFSET][2 + GRID_OFFSET]->isObstacle  = true;

    m_grid[-2 + GRID_OFFSET][-7 + GRID_OFFSET]->isObstacle = true;
    m_grid[-2 + GRID_OFFSET][-6 + GRID_OFFSET]->isObstacle = true;
    m_grid[-2 + GRID_OFFSET][-5 + GRID_OFFSET]->isObstacle = true;

    m_grid[-2 + GRID_OFFSET][5 + GRID_OFFSET]->isObstacle = true;
    m_grid[-2 + GRID_OFFSET][6 + GRID_OFFSET]->isObstacle = true;

    m_grid[-2 + GRID_OFFSET][8 + GRID_OFFSET]->isObstacle = true;
    /*  m_grid[-2 + GRID_OFFSET][-4 + GRID_OFFSET]->isObstacle = true;*/

    m_grid[-1 + GRID_OFFSET][-7 + GRID_OFFSET]->isObstacle = true;
    m_grid[-1 + GRID_OFFSET][-6 + GRID_OFFSET]->isObstacle = true;
    m_grid[-1 + GRID_OFFSET][-5 + GRID_OFFSET]->isObstacle = true;

    m_grid[-1 + GRID_OFFSET][5 + GRID_OFFSET]->isObstacle = true;
    m_grid[-1 + GRID_OFFSET][6 + GRID_OFFSET]->isObstacle = true;
    m_grid[-1 + GRID_OFFSET][7 + GRID_OFFSET]->isObstacle = true;
    m_grid[-1 + GRID_OFFSET][8 + GRID_OFFSET]->isObstacle = true;
    // m_grid[-1 + GRID_OFFSET][-4 + GRID_OFFSET]->isObstacle = true;

    m_grid[GRID_OFFSET][-7 + GRID_OFFSET]->isObstacle = true;
    m_grid[GRID_OFFSET][-6 + GRID_OFFSET]->isObstacle = true;
    m_grid[GRID_OFFSET][-5 + GRID_OFFSET]->isObstacle = true;

    m_grid[GRID_OFFSET][5 + GRID_OFFSET]->isObstacle = true;
    m_grid[GRID_OFFSET][6 + GRID_OFFSET]->isObstacle = true;
    m_grid[GRID_OFFSET][7 + GRID_OFFSET]->isObstacle = true;
    m_grid[GRID_OFFSET][8 + GRID_OFFSET]->isObstacle = true;
    // m_grid[GRID_OFFSET][-4 + GRID_OFFSET]->isObstacle = true;

    m_grid[1 + GRID_OFFSET][-7 + GRID_OFFSET]->isObstacle = true;
    m_grid[1 + GRID_OFFSET][-6 + GRID_OFFSET]->isObstacle = true;
    m_grid[1 + GRID_OFFSET][-5 + GRID_OFFSET]->isObstacle = true;
    // m_grid[1 + GRID_OFFSET][-4 + GRID_OFFSET]->isObstacle = true;

    m_grid[2 + GRID_OFFSET][-7 + GRID_OFFSET]->isObstacle = true;
    m_grid[2 + GRID_OFFSET][-6 + GRID_OFFSET]->isObstacle = true;
    m_grid[2 + GRID_OFFSET][-5 + GRID_OFFSET]->isObstacle = true;
    /* m_grid[2 + GRID_OFFSET][-4 + GRID_OFFSET]->isObstacle = true;*/

    m_grid[3 + GRID_OFFSET][-7 + GRID_OFFSET]->isObstacle = true;
    m_grid[3 + GRID_OFFSET][-6 + GRID_OFFSET]->isObstacle = true;
    m_grid[3 + GRID_OFFSET][-5 + GRID_OFFSET]->isObstacle = true;


    m_grid[4 + GRID_OFFSET][-7 + GRID_OFFSET]->isObstacle = true;
    m_grid[4 + GRID_OFFSET][-6 + GRID_OFFSET]->isObstacle = true;
    m_grid[4 + GRID_OFFSET][-5 + GRID_OFFSET]->isObstacle = true;


    m_grid[5 + GRID_OFFSET][-7 + GRID_OFFSET]->isObstacle = true;
    m_grid[5 + GRID_OFFSET][-6 + GRID_OFFSET]->isObstacle = true;
    m_grid[5 + GRID_OFFSET][-5 + GRID_OFFSET]->isObstacle = true;


    m_grid[6 + GRID_OFFSET][-7 + GRID_OFFSET]->isObstacle = true;
    m_grid[6 + GRID_OFFSET][-6 + GRID_OFFSET]->isObstacle = true;
    m_grid[6 + GRID_OFFSET][-5 + GRID_OFFSET]->isObstacle = true;


    m_grid[7 + GRID_OFFSET][-7 + GRID_OFFSET]->isObstacle = true;
    m_grid[7 + GRID_OFFSET][-6 + GRID_OFFSET]->isObstacle = true;
    m_grid[7 + GRID_OFFSET][-5 + GRID_OFFSET]->isObstacle = true;


    m_grid[8 + GRID_OFFSET][-7 + GRID_OFFSET]->isObstacle = true;
    m_grid[8 + GRID_OFFSET][-6 + GRID_OFFSET]->isObstacle = true;
    m_grid[8 + GRID_OFFSET][-5 + GRID_OFFSET]->isObstacle = true;


    m_grid[9 + GRID_OFFSET][-7 + GRID_OFFSET]->isObstacle = true;
    m_grid[9 + GRID_OFFSET][-6 + GRID_OFFSET]->isObstacle = true;
    m_grid[9 + GRID_OFFSET][-5 + GRID_OFFSET]->isObstacle = true;


    m_grid[10 + GRID_OFFSET][-6 + GRID_OFFSET]->isObstacle = true;
    m_grid[10 + GRID_OFFSET][-5 + GRID_OFFSET]->isObstacle = true;
    m_grid[10 + GRID_OFFSET][-4 + GRID_OFFSET]->isObstacle = true;
    m_grid[10 + GRID_OFFSET][-3 + GRID_OFFSET]->isObstacle = true;
    m_grid[10 + GRID_OFFSET][-2 + GRID_OFFSET]->isObstacle = true;
    m_grid[10 + GRID_OFFSET][-1 + GRID_OFFSET]->isObstacle = true;
    m_grid[10 + GRID_OFFSET][GRID_OFFSET]->isObstacle      = true;
    m_grid[10 + GRID_OFFSET][1 + GRID_OFFSET]->isObstacle  = true;
    m_grid[10 + GRID_OFFSET][2 + GRID_OFFSET]->isObstacle  = true;
    m_grid[10 + GRID_OFFSET][3 + GRID_OFFSET]->isObstacle  = true;
    m_grid[10 + GRID_OFFSET][4 + GRID_OFFSET]->isObstacle  = true;
    m_grid[10 + GRID_OFFSET][5 + GRID_OFFSET]->isObstacle  = true;
    m_grid[10 + GRID_OFFSET][6 + GRID_OFFSET]->isObstacle  = true;
    m_grid[10 + GRID_OFFSET][7 + GRID_OFFSET]->isObstacle  = true;
    m_grid[10 + GRID_OFFSET][8 + GRID_OFFSET]->isObstacle  = true;
    m_grid[9 + GRID_OFFSET][7 + GRID_OFFSET]->isObstacle   = true;
    m_grid[9 + GRID_OFFSET][8 + GRID_OFFSET]->isObstacle   = true;
    // ������ ������ ��

    m_grid[9 + GRID_OFFSET][10 + GRID_OFFSET]->isObstacle  = true;
    m_grid[9 + GRID_OFFSET][11 + GRID_OFFSET]->isObstacle  = true;
    m_grid[10 + GRID_OFFSET][10 + GRID_OFFSET]->isObstacle = true;
    m_grid[10 + GRID_OFFSET][11 + GRID_OFFSET]->isObstacle = true;
    m_grid[10 + GRID_OFFSET][12 + GRID_OFFSET]->isObstacle = true;
    m_grid[10 + GRID_OFFSET][13 + GRID_OFFSET]->isObstacle = true;
    m_grid[10 + GRID_OFFSET][14 + GRID_OFFSET]->isObstacle = true;
    m_grid[10 + GRID_OFFSET][15 + GRID_OFFSET]->isObstacle = true;
    m_grid[10 + GRID_OFFSET][16 + GRID_OFFSET]->isObstacle = true;
    m_grid[10 + GRID_OFFSET][17 + GRID_OFFSET]->isObstacle = true;
    m_grid[10 + GRID_OFFSET][18 + GRID_OFFSET]->isObstacle = true;
    m_grid[10 + GRID_OFFSET][19 + GRID_OFFSET]->isObstacle = true;
    m_grid[10 + GRID_OFFSET][20 + GRID_OFFSET]->isObstacle = true;
    m_grid[10 + GRID_OFFSET][21 + GRID_OFFSET]->isObstacle = true;
    m_grid[10 + GRID_OFFSET][22 + GRID_OFFSET]->isObstacle = true;
    m_grid[10 + GRID_OFFSET][23 + GRID_OFFSET]->isObstacle = true;
    m_grid[10 + GRID_OFFSET][24 + GRID_OFFSET]->isObstacle = true;

    // ���� �� ������ ��(�Ʒ�����)
    m_grid[-9 + GRID_OFFSET][10 + GRID_OFFSET]->isObstacle = true;
    m_grid[-9 + GRID_OFFSET][11 + GRID_OFFSET]->isObstacle = true;
    m_grid[-9 + GRID_OFFSET][12 + GRID_OFFSET]->isObstacle = true;
    m_grid[-9 + GRID_OFFSET][13 + GRID_OFFSET]->isObstacle = true;

    m_grid[-8 + GRID_OFFSET][10 + GRID_OFFSET]->isObstacle = true;
    m_grid[-8 + GRID_OFFSET][11 + GRID_OFFSET]->isObstacle = true;
    m_grid[-8 + GRID_OFFSET][12 + GRID_OFFSET]->isObstacle = true;
    m_grid[-8 + GRID_OFFSET][13 + GRID_OFFSET]->isObstacle = true;

    m_grid[-7 + GRID_OFFSET][10 + GRID_OFFSET]->isObstacle = true;
    m_grid[-7 + GRID_OFFSET][11 + GRID_OFFSET]->isObstacle = true;
    m_grid[-7 + GRID_OFFSET][12 + GRID_OFFSET]->isObstacle = true;
    m_grid[-7 + GRID_OFFSET][13 + GRID_OFFSET]->isObstacle = true;

    m_grid[-6 + GRID_OFFSET][10 + GRID_OFFSET]->isObstacle = true;
    m_grid[-6 + GRID_OFFSET][11 + GRID_OFFSET]->isObstacle = true;
    m_grid[-6 + GRID_OFFSET][12 + GRID_OFFSET]->isObstacle = true;
    m_grid[-6 + GRID_OFFSET][13 + GRID_OFFSET]->isObstacle = true;

    m_grid[-5 + GRID_OFFSET][10 + GRID_OFFSET]->isObstacle = true;
    m_grid[-5 + GRID_OFFSET][11 + GRID_OFFSET]->isObstacle = true;
    m_grid[-5 + GRID_OFFSET][12 + GRID_OFFSET]->isObstacle = true;
    m_grid[-5 + GRID_OFFSET][13 + GRID_OFFSET]->isObstacle = true;

    m_grid[-4 + GRID_OFFSET][10 + GRID_OFFSET]->isObstacle = true;
    m_grid[-4 + GRID_OFFSET][11 + GRID_OFFSET]->isObstacle = true;
    m_grid[-4 + GRID_OFFSET][12 + GRID_OFFSET]->isObstacle = true;
    m_grid[-4 + GRID_OFFSET][13 + GRID_OFFSET]->isObstacle = true;

    m_grid[-3 + GRID_OFFSET][10 + GRID_OFFSET]->isObstacle = true;
    m_grid[-3 + GRID_OFFSET][11 + GRID_OFFSET]->isObstacle = true;
    m_grid[-3 + GRID_OFFSET][12 + GRID_OFFSET]->isObstacle = true;
    m_grid[-3 + GRID_OFFSET][13 + GRID_OFFSET]->isObstacle = true;

    m_grid[-1 + GRID_OFFSET][10 + GRID_OFFSET]->isObstacle = true;
    m_grid[-1 + GRID_OFFSET][11 + GRID_OFFSET]->isObstacle = true;
    m_grid[-1 + GRID_OFFSET][12 + GRID_OFFSET]->isObstacle = true;
    m_grid[-1 + GRID_OFFSET][13 + GRID_OFFSET]->isObstacle = true;

    m_grid[0 + GRID_OFFSET][10 + GRID_OFFSET]->isObstacle = true;
    m_grid[0 + GRID_OFFSET][11 + GRID_OFFSET]->isObstacle = true;
    m_grid[0 + GRID_OFFSET][12 + GRID_OFFSET]->isObstacle = true;
    m_grid[0 + GRID_OFFSET][13 + GRID_OFFSET]->isObstacle = true;

    m_grid[1 + GRID_OFFSET][10 + GRID_OFFSET]->isObstacle = true;
    m_grid[1 + GRID_OFFSET][11 + GRID_OFFSET]->isObstacle = true;
    m_grid[1 + GRID_OFFSET][12 + GRID_OFFSET]->isObstacle = true;
    m_grid[1 + GRID_OFFSET][13 + GRID_OFFSET]->isObstacle = true;

    m_grid[2 + GRID_OFFSET][10 + GRID_OFFSET]->isObstacle = true;
    m_grid[2 + GRID_OFFSET][11 + GRID_OFFSET]->isObstacle = true;
    m_grid[2 + GRID_OFFSET][12 + GRID_OFFSET]->isObstacle = true;
    m_grid[2 + GRID_OFFSET][13 + GRID_OFFSET]->isObstacle = true;

    m_grid[4 + GRID_OFFSET][10 + GRID_OFFSET]->isObstacle = true;
    m_grid[4 + GRID_OFFSET][11 + GRID_OFFSET]->isObstacle = true;
    m_grid[4 + GRID_OFFSET][12 + GRID_OFFSET]->isObstacle = true;
    m_grid[4 + GRID_OFFSET][13 + GRID_OFFSET]->isObstacle = true;

    m_grid[5 + GRID_OFFSET][10 + GRID_OFFSET]->isObstacle = true;
    m_grid[5 + GRID_OFFSET][11 + GRID_OFFSET]->isObstacle = true;
    m_grid[5 + GRID_OFFSET][12 + GRID_OFFSET]->isObstacle = true;
    m_grid[5 + GRID_OFFSET][13 + GRID_OFFSET]->isObstacle = true;

    m_grid[6 + GRID_OFFSET][10 + GRID_OFFSET]->isObstacle = true;
    m_grid[6 + GRID_OFFSET][11 + GRID_OFFSET]->isObstacle = true;
    m_grid[6 + GRID_OFFSET][12 + GRID_OFFSET]->isObstacle = true;
    m_grid[6 + GRID_OFFSET][13 + GRID_OFFSET]->isObstacle = true;

    m_grid[-14 + GRID_OFFSET][18 + GRID_OFFSET]->isObstacle = true;
    m_grid[-13 + GRID_OFFSET][18 + GRID_OFFSET]->isObstacle = true;
    m_grid[-12 + GRID_OFFSET][18 + GRID_OFFSET]->isObstacle = true;
    m_grid[-11 + GRID_OFFSET][18 + GRID_OFFSET]->isObstacle = true;
    m_grid[-10 + GRID_OFFSET][18 + GRID_OFFSET]->isObstacle = true;
    m_grid[-9 + GRID_OFFSET][18 + GRID_OFFSET]->isObstacle  = true;
    m_grid[-8 + GRID_OFFSET][18 + GRID_OFFSET]->isObstacle  = true;
    m_grid[-7 + GRID_OFFSET][18 + GRID_OFFSET]->isObstacle  = true;
    m_grid[-6 + GRID_OFFSET][18 + GRID_OFFSET]->isObstacle  = true;
    m_grid[-5 + GRID_OFFSET][18 + GRID_OFFSET]->isObstacle  = true;
    m_grid[-4 + GRID_OFFSET][18 + GRID_OFFSET]->isObstacle  = true;

    m_grid[-3 + GRID_OFFSET][18 + GRID_OFFSET]->isObstacle = true;
    m_grid[-2 + GRID_OFFSET][18 + GRID_OFFSET]->isObstacle = true;
    m_grid[-1 + GRID_OFFSET][18 + GRID_OFFSET]->isObstacle = true;
    m_grid[GRID_OFFSET][18 + GRID_OFFSET]->isObstacle      = true;
    m_grid[1 + GRID_OFFSET][18 + GRID_OFFSET]->isObstacle  = true;
    m_grid[2 + GRID_OFFSET][18 + GRID_OFFSET]->isObstacle  = true;
    m_grid[3 + GRID_OFFSET][18 + GRID_OFFSET]->isObstacle  = true;
    m_grid[4 + GRID_OFFSET][18 + GRID_OFFSET]->isObstacle  = true;
    m_grid[5 + GRID_OFFSET][18 + GRID_OFFSET]->isObstacle  = true;
    m_grid[6 + GRID_OFFSET][18 + GRID_OFFSET]->isObstacle  = true;
    m_grid[7 + GRID_OFFSET][18 + GRID_OFFSET]->isObstacle  = true;
    m_grid[8 + GRID_OFFSET][18 + GRID_OFFSET]->isObstacle  = true;
    m_grid[9 + GRID_OFFSET][18 + GRID_OFFSET]->isObstacle  = true;

    m_grid[-13 + GRID_OFFSET][10 + GRID_OFFSET]->isObstacle = true;
    m_grid[-13 + GRID_OFFSET][11 + GRID_OFFSET]->isObstacle = true;
    m_grid[-13 + GRID_OFFSET][12 + GRID_OFFSET]->isObstacle = true;
    m_grid[-13 + GRID_OFFSET][13 + GRID_OFFSET]->isObstacle = true;
    m_grid[-13 + GRID_OFFSET][14 + GRID_OFFSET]->isObstacle = true;
    m_grid[-13 + GRID_OFFSET][15 + GRID_OFFSET]->isObstacle = true;
    m_grid[-13 + GRID_OFFSET][16 + GRID_OFFSET]->isObstacle = true;
    m_grid[-13 + GRID_OFFSET][17 + GRID_OFFSET]->isObstacle = true;
    m_grid[-13 + GRID_OFFSET][18 + GRID_OFFSET]->isObstacle = true;

    m_grid[-12 + GRID_OFFSET][11 + GRID_OFFSET]->isObstacle = true;
    m_grid[-12 + GRID_OFFSET][12 + GRID_OFFSET]->isObstacle = true;
    m_grid[-12 + GRID_OFFSET][13 + GRID_OFFSET]->isObstacle = true;
    m_grid[-12 + GRID_OFFSET][14 + GRID_OFFSET]->isObstacle = true;
    m_grid[-12 + GRID_OFFSET][15 + GRID_OFFSET]->isObstacle = true;
    m_grid[-12 + GRID_OFFSET][16 + GRID_OFFSET]->isObstacle = true;
    m_grid[-12 + GRID_OFFSET][17 + GRID_OFFSET]->isObstacle = true;
    m_grid[-12 + GRID_OFFSET][18 + GRID_OFFSET]->isObstacle = true;

    m_grid[-11 + GRID_OFFSET][11 + GRID_OFFSET]->isObstacle = true;
    m_grid[-11 + GRID_OFFSET][12 + GRID_OFFSET]->isObstacle = true;
    m_grid[-11 + GRID_OFFSET][13 + GRID_OFFSET]->isObstacle = true;
    m_grid[-11 + GRID_OFFSET][14 + GRID_OFFSET]->isObstacle = true;
    m_grid[-11 + GRID_OFFSET][15 + GRID_OFFSET]->isObstacle = true;
    m_grid[-11 + GRID_OFFSET][16 + GRID_OFFSET]->isObstacle = true;
    m_grid[-11 + GRID_OFFSET][17 + GRID_OFFSET]->isObstacle = true;
    m_grid[-11 + GRID_OFFSET][18 + GRID_OFFSET]->isObstacle = true;

    m_grid[-9 + GRID_OFFSET][19 + GRID_OFFSET]->isObstacle = true;
    m_grid[-9 + GRID_OFFSET][20 + GRID_OFFSET]->isObstacle = true;
    m_grid[-9 + GRID_OFFSET][21 + GRID_OFFSET]->isObstacle = true;
    m_grid[-9 + GRID_OFFSET][22 + GRID_OFFSET]->isObstacle = true;
    m_grid[-9 + GRID_OFFSET][23 + GRID_OFFSET]->isObstacle = true;
    m_grid[-9 + GRID_OFFSET][24 + GRID_OFFSET]->isObstacle = true;

    m_grid[-8 + GRID_OFFSET][19 + GRID_OFFSET]->isObstacle = true;
    m_grid[-8 + GRID_OFFSET][20 + GRID_OFFSET]->isObstacle = true;
    m_grid[-8 + GRID_OFFSET][21 + GRID_OFFSET]->isObstacle = true;
    m_grid[-8 + GRID_OFFSET][22 + GRID_OFFSET]->isObstacle = true;
    m_grid[-8 + GRID_OFFSET][23 + GRID_OFFSET]->isObstacle = true;
    m_grid[-8 + GRID_OFFSET][24 + GRID_OFFSET]->isObstacle = true;

    m_grid[-7 + GRID_OFFSET][19 + GRID_OFFSET]->isObstacle = true;
    m_grid[-7 + GRID_OFFSET][20 + GRID_OFFSET]->isObstacle = true;
    m_grid[-7 + GRID_OFFSET][21 + GRID_OFFSET]->isObstacle = true;
    m_grid[-7 + GRID_OFFSET][22 + GRID_OFFSET]->isObstacle = true;
    m_grid[-7 + GRID_OFFSET][23 + GRID_OFFSET]->isObstacle = true;
    m_grid[-7 + GRID_OFFSET][24 + GRID_OFFSET]->isObstacle = true;

    m_grid[-6 + GRID_OFFSET][19 + GRID_OFFSET]->isObstacle = true;
    m_grid[-6 + GRID_OFFSET][20 + GRID_OFFSET]->isObstacle = true;
    m_grid[-6 + GRID_OFFSET][21 + GRID_OFFSET]->isObstacle = true;
    m_grid[-6 + GRID_OFFSET][22 + GRID_OFFSET]->isObstacle = true;
    m_grid[-6 + GRID_OFFSET][23 + GRID_OFFSET]->isObstacle = true;
    m_grid[-6 + GRID_OFFSET][24 + GRID_OFFSET]->isObstacle = true;

    m_grid[-5 + GRID_OFFSET][19 + GRID_OFFSET]->isObstacle = true;
    m_grid[-5 + GRID_OFFSET][20 + GRID_OFFSET]->isObstacle = true;
    m_grid[-5 + GRID_OFFSET][21 + GRID_OFFSET]->isObstacle = true;
    m_grid[-5 + GRID_OFFSET][22 + GRID_OFFSET]->isObstacle = true;
    m_grid[-5 + GRID_OFFSET][23 + GRID_OFFSET]->isObstacle = true;
    m_grid[-5 + GRID_OFFSET][24 + GRID_OFFSET]->isObstacle = true;

    m_grid[-4 + GRID_OFFSET][19 + GRID_OFFSET]->isObstacle = true;
    m_grid[-4 + GRID_OFFSET][20 + GRID_OFFSET]->isObstacle = true;
    m_grid[-4 + GRID_OFFSET][21 + GRID_OFFSET]->isObstacle = true;
    m_grid[-4 + GRID_OFFSET][22 + GRID_OFFSET]->isObstacle = true;
    m_grid[-4 + GRID_OFFSET][23 + GRID_OFFSET]->isObstacle = true;
    m_grid[-4 + GRID_OFFSET][24 + GRID_OFFSET]->isObstacle = true;

    m_grid[-3 + GRID_OFFSET][19 + GRID_OFFSET]->isObstacle = true;
    m_grid[-3 + GRID_OFFSET][20 + GRID_OFFSET]->isObstacle = true;
    m_grid[-3 + GRID_OFFSET][21 + GRID_OFFSET]->isObstacle = true;
    m_grid[-3 + GRID_OFFSET][22 + GRID_OFFSET]->isObstacle = true;
    m_grid[-3 + GRID_OFFSET][23 + GRID_OFFSET]->isObstacle = true;
    m_grid[-3 + GRID_OFFSET][24 + GRID_OFFSET]->isObstacle = true;

    m_grid[-2 + GRID_OFFSET][19 + GRID_OFFSET]->isObstacle = true;
    m_grid[-2 + GRID_OFFSET][20 + GRID_OFFSET]->isObstacle = true;
    m_grid[-2 + GRID_OFFSET][21 + GRID_OFFSET]->isObstacle = true;
    m_grid[-2 + GRID_OFFSET][22 + GRID_OFFSET]->isObstacle = true;
    m_grid[-2 + GRID_OFFSET][23 + GRID_OFFSET]->isObstacle = true;
    m_grid[-2 + GRID_OFFSET][24 + GRID_OFFSET]->isObstacle = true;

    m_grid[-1 + GRID_OFFSET][19 + GRID_OFFSET]->isObstacle = true;
    m_grid[-1 + GRID_OFFSET][20 + GRID_OFFSET]->isObstacle = true;
    m_grid[-1 + GRID_OFFSET][21 + GRID_OFFSET]->isObstacle = true;
    m_grid[-1 + GRID_OFFSET][22 + GRID_OFFSET]->isObstacle = true;
    m_grid[-1 + GRID_OFFSET][23 + GRID_OFFSET]->isObstacle = true;
    m_grid[-1 + GRID_OFFSET][24 + GRID_OFFSET]->isObstacle = true;

    m_grid[GRID_OFFSET][19 + GRID_OFFSET]->isObstacle = true;
    m_grid[GRID_OFFSET][20 + GRID_OFFSET]->isObstacle = true;
    m_grid[GRID_OFFSET][21 + GRID_OFFSET]->isObstacle = true;
    m_grid[GRID_OFFSET][22 + GRID_OFFSET]->isObstacle = true;
    m_grid[GRID_OFFSET][23 + GRID_OFFSET]->isObstacle = true;
    m_grid[GRID_OFFSET][24 + GRID_OFFSET]->isObstacle = true;

    m_grid[1 + GRID_OFFSET][19 + GRID_OFFSET]->isObstacle = true;
    m_grid[1 + GRID_OFFSET][20 + GRID_OFFSET]->isObstacle = true;
    m_grid[1 + GRID_OFFSET][21 + GRID_OFFSET]->isObstacle = true;
    m_grid[1 + GRID_OFFSET][22 + GRID_OFFSET]->isObstacle = true;
    m_grid[1 + GRID_OFFSET][23 + GRID_OFFSET]->isObstacle = true;
    m_grid[1 + GRID_OFFSET][24 + GRID_OFFSET]->isObstacle = true;

    m_grid[2 + GRID_OFFSET][19 + GRID_OFFSET]->isObstacle = true;
    m_grid[2 + GRID_OFFSET][20 + GRID_OFFSET]->isObstacle = true;
    m_grid[2 + GRID_OFFSET][21 + GRID_OFFSET]->isObstacle = true;
    m_grid[2 + GRID_OFFSET][22 + GRID_OFFSET]->isObstacle = true;
    m_grid[2 + GRID_OFFSET][23 + GRID_OFFSET]->isObstacle = true;
    m_grid[2 + GRID_OFFSET][24 + GRID_OFFSET]->isObstacle = true;

    m_grid[3 + GRID_OFFSET][19 + GRID_OFFSET]->isObstacle = true;
    m_grid[3 + GRID_OFFSET][20 + GRID_OFFSET]->isObstacle = true;
    m_grid[3 + GRID_OFFSET][21 + GRID_OFFSET]->isObstacle = true;
    m_grid[3 + GRID_OFFSET][22 + GRID_OFFSET]->isObstacle = true;
    m_grid[3 + GRID_OFFSET][23 + GRID_OFFSET]->isObstacle = true;
    m_grid[3 + GRID_OFFSET][24 + GRID_OFFSET]->isObstacle = true;

    m_grid[4 + GRID_OFFSET][19 + GRID_OFFSET]->isObstacle = true;
    m_grid[4 + GRID_OFFSET][20 + GRID_OFFSET]->isObstacle = true;
    m_grid[4 + GRID_OFFSET][21 + GRID_OFFSET]->isObstacle = true;
    m_grid[4 + GRID_OFFSET][22 + GRID_OFFSET]->isObstacle = true;
    m_grid[4 + GRID_OFFSET][23 + GRID_OFFSET]->isObstacle = true;
    m_grid[4 + GRID_OFFSET][24 + GRID_OFFSET]->isObstacle = true;

    m_grid[5 + GRID_OFFSET][19 + GRID_OFFSET]->isObstacle = true;
    m_grid[5 + GRID_OFFSET][20 + GRID_OFFSET]->isObstacle = true;
    m_grid[5 + GRID_OFFSET][21 + GRID_OFFSET]->isObstacle = true;
    m_grid[5 + GRID_OFFSET][22 + GRID_OFFSET]->isObstacle = true;
    m_grid[5 + GRID_OFFSET][23 + GRID_OFFSET]->isObstacle = true;
    m_grid[5 + GRID_OFFSET][24 + GRID_OFFSET]->isObstacle = true;

    m_grid[6 + GRID_OFFSET][19 + GRID_OFFSET]->isObstacle = true;
    m_grid[6 + GRID_OFFSET][20 + GRID_OFFSET]->isObstacle = true;
    m_grid[6 + GRID_OFFSET][21 + GRID_OFFSET]->isObstacle = true;
    m_grid[6 + GRID_OFFSET][22 + GRID_OFFSET]->isObstacle = true;
    m_grid[6 + GRID_OFFSET][23 + GRID_OFFSET]->isObstacle = true;
    m_grid[6 + GRID_OFFSET][24 + GRID_OFFSET]->isObstacle = true;

    m_grid[7 + GRID_OFFSET][19 + GRID_OFFSET]->isObstacle = true;
    m_grid[7 + GRID_OFFSET][20 + GRID_OFFSET]->isObstacle = true;
    m_grid[7 + GRID_OFFSET][21 + GRID_OFFSET]->isObstacle = true;
    m_grid[7 + GRID_OFFSET][22 + GRID_OFFSET]->isObstacle = true;
    m_grid[7 + GRID_OFFSET][23 + GRID_OFFSET]->isObstacle = true;
    m_grid[7 + GRID_OFFSET][24 + GRID_OFFSET]->isObstacle = true;

    m_grid[8 + GRID_OFFSET][19 + GRID_OFFSET]->isObstacle = true;
    m_grid[8 + GRID_OFFSET][20 + GRID_OFFSET]->isObstacle = true;
    m_grid[8 + GRID_OFFSET][21 + GRID_OFFSET]->isObstacle = true;
    m_grid[8 + GRID_OFFSET][22 + GRID_OFFSET]->isObstacle = true;
    m_grid[8 + GRID_OFFSET][23 + GRID_OFFSET]->isObstacle = true;
    m_grid[8 + GRID_OFFSET][24 + GRID_OFFSET]->isObstacle = true;

    m_grid[9 + GRID_OFFSET][19 + GRID_OFFSET]->isObstacle = true;
    m_grid[9 + GRID_OFFSET][20 + GRID_OFFSET]->isObstacle = true;
    m_grid[9 + GRID_OFFSET][21 + GRID_OFFSET]->isObstacle = true;
    m_grid[9 + GRID_OFFSET][22 + GRID_OFFSET]->isObstacle = true;
    m_grid[9 + GRID_OFFSET][23 + GRID_OFFSET]->isObstacle = true;
    m_grid[9 + GRID_OFFSET][24 + GRID_OFFSET]->isObstacle = true;

    m_grid[16 + GRID_OFFSET][1 + GRID_OFFSET]->isObstacle = true;
    m_grid[16 + GRID_OFFSET][2 + GRID_OFFSET]->isObstacle = true;
    m_grid[16 + GRID_OFFSET][3 + GRID_OFFSET]->isObstacle = true;

    m_grid[17 + GRID_OFFSET][1 + GRID_OFFSET]->isObstacle = true;
    m_grid[17 + GRID_OFFSET][2 + GRID_OFFSET]->isObstacle = true;
    m_grid[17 + GRID_OFFSET][3 + GRID_OFFSET]->isObstacle = true;

    m_grid[18 + GRID_OFFSET][9 + GRID_OFFSET]->isObstacle  = true;
    m_grid[18 + GRID_OFFSET][10 + GRID_OFFSET]->isObstacle = true;
    m_grid[18 + GRID_OFFSET][11 + GRID_OFFSET]->isObstacle = true;
    m_grid[18 + GRID_OFFSET][12 + GRID_OFFSET]->isObstacle = true;
}
