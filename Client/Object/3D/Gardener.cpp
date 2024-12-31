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
{
    m_mesh = HASSET->m_meshes[L"Walking.hbs"];
    m_easyRender.SetMesh(m_mesh);
    m_easyRender.SetVSShader(L"BasicAniVS.hlsl");
    m_easyRender.SetPSShader(L"ColorPS.hlsl");

    anim.resize(m_mesh->m_born.bornIndex.size());

    m_transform.SetScale({0.2f, 0.2f, 0.2f});
    m_transform.SetLocation({0.75f, 0.5f, 0.75f});

    m_goose = std::make_shared<Goose>();


    // 2D 그리드 초기화

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


    ImGui::SliderFloat("Speed", &speed, 0, 30.f);

    currentFrame += deltaTime * speed;
    startFrame    = m_gardenerAni[0]->GetStartFrame();
    lastFrame     = m_gardenerAni[0]->GetLastFrame();

    if (currentFrame > lastFrame)
        currentFrame = startFrame;

    anim = m_gardenerAni[0]->GetAnimationMatrix(currentFrame);

    // ImGui::SliderFloat("Gardener speed", &m_speed2, 0.f, 50.f);

    // static bool isDownPressed  = false;  // VK_DOWN 상태 추적
    // static bool isUpPressed    = false;  // VK_UP 상태 추적
    // static bool isRightPressed = false;
    // static bool isLeftPressed  = false;
    // vec3        moveDirection  = vec3(0.f, 0.f, 0.f);


    // if (HINPUT->IsKeyPressed(74) && !isRightPressed)  // VK_LEFT
    //{
    //     isLeftPressed  = true;
    //     isRightPressed = false;
    //     moveDirection  = vec3(-1.f, 0.f, 0.f);
    //     m_transform.SetRotation(vec3(0.f, 1.f, 0.f), glm::radians(-90.f));


    //    if (HINPUT->IsKeyPressed(75))  // VK_DOWN
    //    {

    //        moveDirection += vec3(0.f, 0.f, -1.f);
    //        /* m_transform.SetRotation(vec3(0.f, 1.f, 0.f), glm::radians(-45.f));*/
    //    }
    //    if (HINPUT->IsKeyPressed(73))  // VK_UP
    //    {

    //        moveDirection += vec3(0.f, 0.f, 1.f);
    //        /*    m_transform.SetRotation(vec3(0.f, 1.f, 0.f), glm::radians(-135.f));*/
    //    }
    //    if (HINPUT->IsKeyPressed(16))  // SHIFT키
    //    {
    //        moveDirection += vec3(-1.0f, 0.0f, 0.0f);
    //        /*m_transform.AddLocation(vec3(-1.0f, 0.0f, 0.0f) * deltaTime * m_speed1 * 2.0f);*/
    //    }
    //}

    // if (HINPUT->IsKeyPressed(76) && !isLeftPressed)  // VK_RIGHT
    //{
    //     isLeftPressed  = false;
    //     isRightPressed = true;
    //     moveDirection  = vec3(1.f, 0.f, 0.f);
    //     m_transform.SetRotation(vec3(0.f, 1.f, 0.f), glm::radians(90.f));

    //    if (HINPUT->IsKeyPressed(75))  // VK_DOWN
    //    {
    //        /*   m_transform.SetRotation(vec3(0.f, 1.f, 0.f), glm::radians(45.f));*/
    //        moveDirection += vec3(0.f, 0.f, -1.f);
    //    }

    //    if (HINPUT->IsKeyPressed(73))  // VK_UP
    //    {
    //        /*    m_transform.SetRotation(vec3(0.f, 1.f, 0.f), glm::radians(-135.f));*/
    //        moveDirection += vec3(0.f, 0.f, 1.f);
    //    }

    //    if (HINPUT->IsKeyPressed(16))  // SHIFT키
    //    {
    //        moveDirection += vec3(1.0f, 0.0f, 0.0f);
    //        /*m_transform.AddLocation(vec3(1.0f, 0.0f, 0.0f) * deltaTime * m_speed1 * 2.0f);*/
    //    }
    //}


    // if (!HINPUT->IsKeyPressed(76))  // VK_RIGHT
    //{
    //     isRightPressed = false;
    // }

    // if (!HINPUT->IsKeyPressed(74))  // VK_LEFT
    //{
    //     isLeftPressed = false;
    // }

    //// VK_DOWN 처리
    // if (HINPUT->IsKeyPressed(75) && !isUpPressed)  // VK_DOWN (VK_UP이 눌리지 않은 경우)
    //{
    //     isDownPressed = true;   // VK_DOWN 활성화
    //     isUpPressed   = false;  // VK_UP 비활성화
    //     moveDirection = vec3(0.f, 0.f, -1.f);
    //     m_transform.SetRotation(vec3(0.f, 1.f, 0.f), glm::radians(0.f));

    //    if (HINPUT->IsKeyPressed(74))  // VK_LEFT
    //    {
    //        m_transform.SetRotation(vec3(0.f, 1.f, 0.f), glm::radians(-45.f));
    //        moveDirection += vec3(-1.0f, 0.f, 0.f);
    //    }

    //    if (HINPUT->IsKeyPressed(76))  // VK_RIGHT
    //    {
    //        m_transform.SetRotation(vec3(0.f, 1.f, 0.f), glm::radians(45.f));
    //        moveDirection += vec3(1.0f, 0.f, 0.f);
    //    }

    //    if (HINPUT->IsKeyPressed(16))  // SHIFT키
    //    {
    //        moveDirection += vec3(0.0f, 0.0f, -1.0f);
    //        /*m_transform.AddLocation(vec3(0.0f, 0.0f, -1.0f) * deltaTime * m_speed1 * 2.0f);*/
    //    }
    //}
    //// VK_UP 처리
    // if (HINPUT->IsKeyPressed(73) && !isDownPressed)  // VK_UP (VK_DOWN이 눌리지 않은 경우)
    //{
    //     isUpPressed   = true;   // VK_UP 활성화
    //     isDownPressed = false;  // VK_DOWN 비활성화
    //     moveDirection = vec3(0.f, 0.f, 1.f);
    //     m_transform.SetRotation(vec3(0.f, 1.f, 0.f), glm::radians(180.f));


    //    if (HINPUT->IsKeyPressed(74))  // VK_LEFT
    //    {
    //        m_transform.SetRotation(vec3(0.f, 1.f, 0.f), glm::radians(-135.f));
    //        moveDirection += vec3(-1.0f, 0.f, 0.f);
    //    }

    //    if (HINPUT->IsKeyPressed(76))  // VK_RIGHT
    //    {
    //        m_transform.SetRotation(vec3(0.f, 1.f, 0.f), glm::radians(135.f));
    //        moveDirection += vec3(1.0f, 0.f, 0.f);
    //    }

    //    if (HINPUT->IsKeyPressed(16))  // SHIFT키
    //    {
    //        moveDirection += vec3(0.0f, 0.0f, 1.0f);
    //        /* m_transform.AddLocation(vec3(0.0f, 0.0f, 1.0f) * deltaTime * m_speed1 * 2.0f);*/
    //    }

    //    /*if (glm::length(moveDirection) > 0.0f)
    //    {

    //        moveDirection = glm::normalize(moveDirection);
    //    }*/
    //}


    // if (HINPUT->IsKeyPressed(16))  // SHIFT키
    //{
    //     m_transform.AddLocation(moveDirection * deltaTime * m_speed2 * 1.5f);
    // }

    //// VK_DOWN 해제 시 상태 초기화
    // if (!HINPUT->IsKeyPressed(75))
    //{
    //     isDownPressed = false;
    // }

    //// VK_UP 해제 시 상태 초기화
    // if (!HINPUT->IsKeyPressed(73))
    //{
    //     isUpPressed = false;
    // }


    int                                             rows = 40;
    int                                             cols = 40;
    std::vector<std::vector<std::shared_ptr<Node>>> grid(rows, std::vector<std::shared_ptr<Node>>(cols));

    // 2D 그리드 초기화
    for (int y = -GRID_OFFSET; y < GRID_OFFSET; ++y)
    {
        for (int x = -GRID_OFFSET; x < GRID_OFFSET; ++x)
        {
            grid[x + GRID_OFFSET][y + GRID_OFFSET] = std::make_shared<Node>(x, y);  // make_shared 사용
        }
    }


    grid[4 + GRID_OFFSET][1 + GRID_OFFSET]->isObstacle = true;
    grid[4 + GRID_OFFSET][2 + GRID_OFFSET]->isObstacle = true;
    grid[4 + GRID_OFFSET][3 + GRID_OFFSET]->isObstacle = true;

    //// 2D 그리드 초기화
    // for (int y = -GRID_OFFSET; y < GRID_OFFSET; ++y)
    //{
    //     for (int x = -GRID_OFFSET; x < GRID_OFFSET; ++x)
    //     {
    //         grid[x + GRID_OFFSET][y + GRID_OFFSET] = std::make_shared<Node>(x, y);  // make_shared
    //         사용
    //     }
    // }

    bool gooseStealItem = false;


    if (gooseStealItem)
    {
    }
    else if ((abs(m_goose->GetmPos().x - m_transform.m_pos[0]) < 2.0f) &&
             (abs(m_goose->GetmPos().z - m_transform.m_pos[0]) < 2.0f))
    {
        vec3 goose_pos      = m_goose->GetmPos();
        vec3 pushDirection  = glm::normalize(goose_pos - m_transform.m_pos) * -1.0f;
        goose_pos          += pushDirection * deltaTime;
    }
    else
    {
        std::vector<std::pair<int, int>> position = movepath;

        m_transform.AddLocation(glm::normalize(vec3(position[posIdx].first * (gridLength / gridNum),
                                                    0.f,
                                                    position[posIdx].second * (gridLength / gridNum))) *
                                deltaTime);
        posIdx++;
        if (posIdx == 8)
            posIdx = 0;
    }
    std::cout << m_goose->GetmPos().x << ", " << m_goose->GetmPos().z << std::endl;

    // 장애물 설정 (예: 좌표 (2,2), (2,3), (3,2)을 장애물로 설정)
    grid[4 + GRID_OFFSET][0 + GRID_OFFSET]->isObstacle = true;
    grid[4 + GRID_OFFSET][1 + GRID_OFFSET]->isObstacle = true;
    grid[4 + GRID_OFFSET][2 + GRID_OFFSET]->isObstacle = true;
    grid[4 + GRID_OFFSET][3 + GRID_OFFSET]->isObstacle = true;

    //// 시작점과 목표점 설정

    auto start =
    grid[((int)(m_transform.m_pos[0] / (gridLength / gridNum))) + 20]
        [((int)(m_transform.m_pos[2] / (gridLength / gridNum))) + 20];  // 가드너 움직이는 거에 따른 좌표
    auto goal =
    grid[((int)(m_goose->GetmPos().x / (gridLength / gridNum))) + 20]
        [((int)(m_goose->GetmPos().z / (gridLength / gridNum))) + 20];  // 거위 움직이는 거에 따른 좌표
    // A* 알고리즘 실행


    auto path = m_astar.aStar(start, goal, grid);


    if (idx + 1 < path.size())
    {
        pathIdx_x = path[idx + 1]->GetLocationX() * (gridLength / gridNum) +
                    (gridLength / gridNum / 2);  // path의 월드위치
        pathIdx_z = path[idx + 1]->GetLocationY() * (gridLength / gridNum) +
                    (gridLength / gridNum / 2);  // path의 월드위치

        gardener_x = m_transform.m_pos[0];  // 가드너의 현재위치
        gardener_z = m_transform.m_pos[2];  // 가드너의 현재위치

        if (glm::abs(gardener_x - pathIdx_x) < 0.1f && glm::abs(gardener_z - pathIdx_z) < 0.1f)
        {
            idx++;
        }
        else
        {

            /* std::cout << path[idx + 1]->GetLocationX() << " " << path[idx + 1]->GetLocationY()
                       << std::endl;*/

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
            glm::normalize(vec3(-(gardener_x - pathIdx_x), 0.f, -(gardener_z - pathIdx_z))) * deltaTime *
            2.5f);
        }
    }

    ///*std::cout << "------------" << std::endl;*/
    UpdateDefaultCB();
    m_easyRender.UpdateVSCB((void*)&anim.at(0), sizeof(mat4) * anim.size(), 1);
    m_goose->Update(deltaTime);
    /*m_goose1.Update(deltaTime);*/
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

vec3 HBSoft::Gardener::GetmPos()
{
    return m_transform.m_pos;
}

void HBSoft::Gardener::SetmPos(float a, float b)
{
    m_transform.m_pos[0] = a;
    m_transform.m_pos[2] = b;
}