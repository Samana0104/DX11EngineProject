/*
author : 정찬빈
description :

version: 1.1.0
date: 2024-11-30
*/


#include "pch.h"
#include "Gardener.h"

using namespace HBSoft;

Gardener::Gardener()
    : m_grid(GRID_ROW, std::vector<std::shared_ptr<Node>>(GRID_COL))
{
    m_mesh = HASSET->m_meshes[L"Walking.hbs"];
    m_easyRender.SetMesh(m_mesh);
    m_easyRender.SetVSShader(L"BasicAniVS.hlsl");
    m_easyRender.SetPSShader(L"ColorPS.hlsl");

    anim.resize(m_mesh->m_born.bornIndex.size());

    m_transform.SetScale({0.2f, 0.2f, 0.2f});
    m_transform.SetLocation({3.f, 0.6f, 4.f});

    currentState = State::Idle;

    for (int x = -GRID_OFFSET; x <= GRID_OFFSET; ++x)
    {
        for (int y = -GRID_OFFSET; y <= GRID_OFFSET; ++y)
        {
            m_grid[x + GRID_OFFSET][y + GRID_OFFSET] = std::make_shared<Node>(x, y);  // make_shared 사용
        }
    }
    // 왼쪽문
    m_grid[5 + GRID_OFFSET][-2 + GRID_OFFSET]->isObstacle = true;
    m_grid[5 + GRID_OFFSET][-1 + GRID_OFFSET]->isObstacle = true;
    m_grid[5 + GRID_OFFSET][GRID_OFFSET]->isObstacle      = true;
    m_grid[5 + GRID_OFFSET][1 + GRID_OFFSET]->isObstacle  = true;
    m_grid[5 + GRID_OFFSET][2 + GRID_OFFSET]->isObstacle  = true;
    m_grid[5 + GRID_OFFSET][3 + GRID_OFFSET]->isObstacle  = true;
    m_grid[5 + GRID_OFFSET][4 + GRID_OFFSET]->isObstacle  = true;


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
}

void Gardener::Update(const float deltaTime)
{
    static float currentFrame = 0.f;
    static int   startFrame   = 0;
    static int   lastFrame    = 0;
    static float speed        = 14.f;
    // static int   selectAnimation = 0;

#ifdef _DEBUG
    ImGui::SliderFloat("Speed", &speed, 0, 30.f);
    ImGui::SliderFloat("Gardener speed", &m_speed2, 0.f, 50.f);
#endif

    currentFrame += deltaTime * speed;
    startFrame    = m_gardenerAni[0]->GetStartFrame();
    lastFrame     = m_gardenerAni[0]->GetLastFrame();

    if (currentFrame > lastFrame)
        currentFrame = startFrame;

    anim = m_gardenerAni[0]->GetAnimationMatrix(currentFrame);


    dx       = m_goose1->GetPos().x - m_transform.m_pos[0];
    dz       = m_goose1->GetPos().z - m_transform.m_pos[2];
    distance = sqrt(dx * dx + dz * dz);

    /// IDLE

    /*onEvent(Event::maintain, deltaTime);*/


    /// 물건 훔쳐가면
    onEvent(Event::GooseStoleItem, deltaTime);

    if (distance < 1.2f)
    {
        /*m_goose1->AddLoc(glm::normalize(vec3(dx / distance, 0.f, dz / distance)) * deltaTime *
         * 100.f);*/
        onEvent(Event::GooseClose, deltaTime);
    }

    UpdateDefaultCB();
    m_easyRender.UpdateVSCB((void*)&anim.at(0), sizeof(mat4) * anim.size(), 1);
}

void Gardener::Render()
{
    m_easyRender.Draw();
    /*FollowPath(GetPath(path));*/
}

void Gardener::Init() {}

void Gardener::Release() {}

float HBSoft::Gardener::GetLocationX()
{
    return m_transform.m_pos[0];
}

float HBSoft::Gardener::GetLocationZ()
{
    return m_transform.m_pos[2];
}

vec3 HBSoft::Gardener::GetPos()
{
    return m_transform.m_pos;
}

void HBSoft::Gardener::SetPos(float a, float b)
{
    m_transform.m_pos[0] = a;
    m_transform.m_pos[2] = b;
}

void Gardener::SetGooseObj(std::shared_ptr<Goose> gooseObj)
{
    m_goose1 = gooseObj;
}

void Gardener::onEvent(Event event, float deltaTime)
{
    switch (currentState)
    {
    case State::Idle:  //(gridLength / gridNum) + (gridLength / gridNum / 2)

        // 여기 Idle 행동
        forward = true;  // 경로 진행 방향
        if (forward)
        {
            if (idlePathIdx < idlePath.size() - 1)
            {
                idlePathX =
                (idlePath[idlePathIdx + 1].first - idlePath[idlePathIdx].first) * (gridLength / gridNum);

                idlePathZ = (idlePath[idlePathIdx + 1].second - idlePath[idlePathIdx].second) *
                            (gridLength / gridNum);

                m_transform.AddLocation(glm::normalize(vec3(idlePathX, 0.f, idlePathZ)) * deltaTime *
                                        10.f);

                idlePathIdx++;
            }
            else
            {
                forward = false;  // 역방향으로 전환
            }
        }
        else
        {
            if (idlePathIdx > 0)
            {
                idlePathX =
                (idlePath[idlePathIdx - 1].first - idlePath[idlePathIdx].first) * (gridLength / gridNum);

                idlePathZ = (idlePath[idlePathIdx - 1].second - idlePath[idlePathIdx].second) *
                            (gridLength / gridNum);

                m_transform.AddLocation(glm::normalize(vec3(idlePathX, 0.f, idlePathZ)) * deltaTime *
                                        10.f);

                idlePathIdx--;
            }
            else
            {
                forward = true;  // 순방향으로 전환
            }
        }
        /*  if (idlePathIdx == idlePath.size() - 1)
          {
              std::reverse(idlePath.begin(), idlePath.end());
              idlePathIdx = 0;
          }*/

        std::cout << "현재상태 : IDLE" << std::endl;
        if (event == Event::GooseClose)
        {
            vec3 pushForce  = glm::normalize(vec3(dx / distance, 0.f, dz / distance)) * 4.f;
            velocity        = pushForce;
            velocity       *= 0.9f;
            /*std::cout << "IDLE : 정원사가 거위를 밀기 시작합니다.\n";*/
            m_goose1->m_transform.AddLocation(velocity * deltaTime);
            /*std::cout << velocity << std::endl;*/
        }
        else if (event == Event::GooseStoleItem)
        {

            //  std::cout << "정원사가 거위를 쫓기 시작합니다.\n";
            currentState = State::Chasing;
        }
        else if (event == Event::maintain)
        {
        }
        break;

    case State::Chasing:
        // 시작점과 목표점 설정
        int gardenerX = GRID_OFFSET + glm::floor(m_transform.m_pos.x * ((float)gridNum / gridLength));
        int gardenerZ = glm::floor(m_transform.m_pos.z * ((float)gridNum / gridLength)) + GRID_OFFSET;
        int gooseX    = GRID_OFFSET + glm::floor(m_goose1->GetPos().x * ((float)gridNum / gridLength));
        int gooseZ    = glm::floor(m_goose1->GetPos().z * ((float)gridNum / gridLength)) + GRID_OFFSET;


        auto start = m_grid[gardenerX][gardenerZ];  // 가드너 움직이는 거에 따른 좌표
        auto goal  = m_grid[gooseX][gooseZ];        // 거위 움직이는 거에 따른 좌표

        // A* 알고리즘 실행

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
                        (gridLength / gridNum / 2);  // path의 월드위치
            pathIdx_z = path[idx + 1]->GetLocationY() * (gridLength / gridNum) +
                        (gridLength / gridNum / 2);  // path의 월드위치

            gardener_x = m_transform.m_pos[0];  // 가드너의 현재위치
            gardener_z = m_transform.m_pos[2];  // 가드너의 현재위치

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
        if (event == Event::GooseFar)
        {
            std::cout << "정원사가 평상시 걷는 상태로 돌아갑니다.\n";
            currentState = State::Idle;
        }
        else if (event == Event::GooseClose)
        {
            vec3 pushForce  = glm::normalize(vec3(dx / distance, 0.f, dz / distance)) * 4.f;
            velocity        = pushForce;
            velocity       *= 0.9f;

            m_goose1->m_transform.AddLocation(velocity * deltaTime);
            std::cout << velocity << std::endl;
            /*std::cout << "CHASING : 정원사가 거위를 밀기 시작합니다.\n";*/
        }
        break;
    }
}