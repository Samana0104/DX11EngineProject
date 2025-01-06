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


    for (int y = 0; y <= GRID_OFFSET * 2; ++y)
    {
        for (int x = 0; x <= GRID_OFFSET * 2; ++x)
        {
            m_grid[y][x] = std::make_shared<Node>(x, y);  // make_shared 사용
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

    /*m_grid[10 + GRID_OFFSET][-3 + GRID_OFFSET]->isObstacle = true;
    m_grid[10 + GRID_OFFSET][-2 + GRID_OFFSET]->isObstacle = true;
    m_grid[10 + GRID_OFFSET][-1 + GRID_OFFSET]->isObstacle = true;
    m_grid[10 + GRID_OFFSET][GRID_OFFSET + 1]->isObstacle  = true;
    m_grid[10 + GRID_OFFSET][GRID_OFFSET + 2]->isObstacle  = true;
    m_grid[10 + GRID_OFFSET][GRID_OFFSET + 3]->isObstacle  = true;
    m_grid[10 + GRID_OFFSET][GRID_OFFSET + 4]->isObstacle  = true;
    m_grid[10 + GRID_OFFSET][GRID_OFFSET + 5]->isObstacle  = true;
    m_grid[10 + GRID_OFFSET][GRID_OFFSET + 6]->isObstacle  = true;
    m_grid[10 + GRID_OFFSET][GRID_OFFSET + 7]->isObstacle  = true;

    m_grid[4 + GRID_OFFSET][GRID_OFFSET + 11]->isObstacle = true;
    m_grid[5 + GRID_OFFSET][GRID_OFFSET + 11]->isObstacle = true;
    m_grid[6 + GRID_OFFSET][GRID_OFFSET + 11]->isObstacle = true;
    m_grid[4 + GRID_OFFSET][GRID_OFFSET + 12]->isObstacle = true;
    m_grid[5 + GRID_OFFSET][GRID_OFFSET + 12]->isObstacle = true;
    m_grid[6 + GRID_OFFSET][GRID_OFFSET + 12]->isObstacle = true;

    m_grid[0 + GRID_OFFSET][GRID_OFFSET + 11]->isObstacle = true;
    m_grid[0 + GRID_OFFSET][GRID_OFFSET + 12]->isObstacle = true;
    m_grid[1 + GRID_OFFSET][GRID_OFFSET + 11]->isObstacle = true;
    m_grid[1 + GRID_OFFSET][GRID_OFFSET + 12]->isObstacle = true;

    m_grid[-7 + GRID_OFFSET][GRID_OFFSET + 11]->isObstacle = true;
    m_grid[-7 + GRID_OFFSET][GRID_OFFSET + 12]->isObstacle = true;
    m_grid[-6 + GRID_OFFSET][GRID_OFFSET + 11]->isObstacle = true;
    m_grid[-6 + GRID_OFFSET][GRID_OFFSET + 12]->isObstacle = true;
    m_grid[-5 + GRID_OFFSET][GRID_OFFSET + 11]->isObstacle = true;
    m_grid[-5 + GRID_OFFSET][GRID_OFFSET + 12]->isObstacle = true;
    m_grid[-4 + GRID_OFFSET][GRID_OFFSET + 11]->isObstacle = true;
    m_grid[-4 + GRID_OFFSET][GRID_OFFSET + 12]->isObstacle = true;
    m_grid[-3 + GRID_OFFSET][GRID_OFFSET + 11]->isObstacle = true;
    m_grid[-3 + GRID_OFFSET][GRID_OFFSET + 12]->isObstacle = true;
    m_grid[-2 + GRID_OFFSET][GRID_OFFSET + 11]->isObstacle = true;
    m_grid[-2 + GRID_OFFSET][GRID_OFFSET + 12]->isObstacle = true;*/
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


    // 2D 그리드 초기화
    for (int y = 0; y <= GRID_OFFSET * 2; ++y)
    {
        for (int x = 0; x <= GRID_OFFSET * 2; ++x)
        {
            m_grid[y][x]->gCost  = 99999.f;
            m_grid[y][x]->hCost  = 0.f;
            m_grid[y][x]->parent = nullptr;
        }
    }
    //    장애물 설정 (예: 좌표 (2,2), (2,3), (3,2)을 장애물로 설정)

    // 시작점과 목표점 설정
    int gardenerX = GRID_OFFSET + glm::floor(m_transform.m_pos.x * ((float)gridNum / gridLength));
    int gardenerZ = GRID_OFFSET - glm::floor(m_transform.m_pos.z * ((float)gridNum / gridLength));
    int gooseX    = GRID_OFFSET + glm::floor(m_goose1->GetPos().x * ((float)gridNum / gridLength));
    int gooseZ    = GRID_OFFSET - glm::floor(m_goose1->GetPos().z * ((float)gridNum / gridLength));

    std::cout << "gooseX : " << gooseX << ", gooseZ : " << gooseZ << std::endl;
    auto start = m_grid[gardenerZ][gardenerX];  // 가드너 움직이는 거에 따른 좌표
    auto goal  = m_grid[gooseZ][gooseX];        // 거위 움직이는 거에 따른 좌표

    // A* 알고리즘 실행

    // if (goal->isObstacle)
    //{
    //     if (!m_grid[gooseZ][gooseX + 1]->isObstacle)
    //         goal = m_grid[gooseZ][gooseX + 1];
    //     else if (!m_grid[gooseZ][gooseX - 1]->isObstacle)
    //         goal = m_grid[gooseZ][gooseX - 1];
    //     else if (!m_grid[gooseZ - 1][gooseX]->isObstacle)
    //         goal = m_grid[gooseZ - 1][gooseX];
    //     else if (!m_grid[gooseZ + 1][gooseX]->isObstacle)
    //         goal = m_grid[gooseZ + 1][gooseX];
    // }

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
            glm::normalize(vec3(-(gardener_x - pathIdx_x), 0.f, -(gardener_z - pathIdx_z))) * deltaTime);
        }
    }
    /*std::cout << "------------" << std::endl;*/
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
