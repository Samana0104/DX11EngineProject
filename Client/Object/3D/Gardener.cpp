/*
author : ������
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
    m_transform.SetLocation({18.f, 0.5f, 18.f});

    // 2D �׸��� �ʱ�ȭ

    /*m_transform.SetScale({0.2f, 0.2f, 0.2f});*/
    /* m_heightmap = std::make_shared<HeightMapObj>();*/
    m_gardenerAni.push_back(HASSET->m_animations[L"mixamo.com.skm"]);
}

void Gardener::Update(const float deltaTime)
{
    static float currentFrame = 0.f;
    static int   startFrame   = 0;
    static int   lastFrame    = 0;
    static float speed        = 30.f;
    // static int   selectAnimation = 0;

#ifdef _DEBUG
    ImGui::SliderFloat("Speed", &speed, 0, 30.f);
#endif

    currentFrame += deltaTime * speed;
    startFrame    = m_gardenerAni[0]->GetStartFrame();
    lastFrame     = m_gardenerAni[0]->GetLastFrame();

    if (currentFrame > lastFrame)
        currentFrame = startFrame;

    anim = m_gardenerAni[0]->GetAnimationMatrix(currentFrame);

#ifdef _DEBUG
    ImGui::SliderFloat("Gardener speed", &m_speed2, 0.f, 50.f);
#endif

    static bool isDownPressed  = false;  // VK_DOWN ���� ����
    static bool isUpPressed    = false;  // VK_UP ���� ����
    static bool isRightPressed = false;
    static bool isLeftPressed  = false;
    vec3        moveDirection  = vec3(0.f, 0.f, 0.f);


    if (HINPUT->IsKeyPressed(74) && !isRightPressed)  // VK_LEFT
    {
        isLeftPressed  = true;
        isRightPressed = false;
        moveDirection  = vec3(-1.f, 0.f, 0.f);
        m_transform.SetRotation(vec3(0.f, 1.f, 0.f), glm::radians(-90.f));


        if (HINPUT->IsKeyPressed(75))  // VK_DOWN
        {

            moveDirection += vec3(0.f, 0.f, -1.f);
            /* m_transform.SetRotation(vec3(0.f, 1.f, 0.f), glm::radians(-45.f));*/
        }
        if (HINPUT->IsKeyPressed(73))  // VK_UP
        {

            moveDirection += vec3(0.f, 0.f, 1.f);
            /*    m_transform.SetRotation(vec3(0.f, 1.f, 0.f), glm::radians(-135.f));*/
        }
        if (HINPUT->IsKeyPressed(16))  // SHIFTŰ
        {
            moveDirection += vec3(-1.0f, 0.0f, 0.0f);
            /*m_transform.AddLocation(vec3(-1.0f, 0.0f, 0.0f) * deltaTime * m_speed1 * 2.0f);*/
        }
    }

    if (HINPUT->IsKeyPressed(76) && !isLeftPressed)  // VK_RIGHT
    {
        isLeftPressed  = false;
        isRightPressed = true;
        moveDirection  = vec3(1.f, 0.f, 0.f);
        m_transform.SetRotation(vec3(0.f, 1.f, 0.f), glm::radians(90.f));

        if (HINPUT->IsKeyPressed(75))  // VK_DOWN
        {
            /*   m_transform.SetRotation(vec3(0.f, 1.f, 0.f), glm::radians(45.f));*/
            moveDirection += vec3(0.f, 0.f, -1.f);
        }

        if (HINPUT->IsKeyPressed(73))  // VK_UP
        {
            /*    m_transform.SetRotation(vec3(0.f, 1.f, 0.f), glm::radians(-135.f));*/
            moveDirection += vec3(0.f, 0.f, 1.f);
        }

        if (HINPUT->IsKeyPressed(16))  // SHIFTŰ
        {
            moveDirection += vec3(1.0f, 0.0f, 0.0f);
            /*m_transform.AddLocation(vec3(1.0f, 0.0f, 0.0f) * deltaTime * m_speed1 * 2.0f);*/
        }
    }


    if (!HINPUT->IsKeyPressed(76))  // VK_RIGHT
    {
        isRightPressed = false;
    }

    if (!HINPUT->IsKeyPressed(74))  // VK_LEFT
    {
        isLeftPressed = false;
    }

    // VK_DOWN ó��
    if (HINPUT->IsKeyPressed(75) && !isUpPressed)  // VK_DOWN (VK_UP�� ������ ���� ���)
    {
        isDownPressed = true;   // VK_DOWN Ȱ��ȭ
        isUpPressed   = false;  // VK_UP ��Ȱ��ȭ
        moveDirection = vec3(0.f, 0.f, -1.f);
        m_transform.SetRotation(vec3(0.f, 1.f, 0.f), glm::radians(0.f));

        if (HINPUT->IsKeyPressed(74))  // VK_LEFT
        {
            m_transform.SetRotation(vec3(0.f, 1.f, 0.f), glm::radians(-45.f));
            moveDirection += vec3(-1.0f, 0.f, 0.f);
        }

        if (HINPUT->IsKeyPressed(76))  // VK_RIGHT
        {
            m_transform.SetRotation(vec3(0.f, 1.f, 0.f), glm::radians(45.f));
            moveDirection += vec3(1.0f, 0.f, 0.f);
        }

        if (HINPUT->IsKeyPressed(16))  // SHIFTŰ
        {
            moveDirection += vec3(0.0f, 0.0f, -1.0f);
            /*m_transform.AddLocation(vec3(0.0f, 0.0f, -1.0f) * deltaTime * m_speed1 * 2.0f);*/
        }
    }
    // VK_UP ó��
    if (HINPUT->IsKeyPressed(73) && !isDownPressed)  // VK_UP (VK_DOWN�� ������ ���� ���)
    {
        isUpPressed   = true;   // VK_UP Ȱ��ȭ
        isDownPressed = false;  // VK_DOWN ��Ȱ��ȭ
        moveDirection = vec3(0.f, 0.f, 1.f);
        m_transform.SetRotation(vec3(0.f, 1.f, 0.f), glm::radians(180.f));


        if (HINPUT->IsKeyPressed(74))  // VK_LEFT
        {
            m_transform.SetRotation(vec3(0.f, 1.f, 0.f), glm::radians(-135.f));
            moveDirection += vec3(-1.0f, 0.f, 0.f);
        }

        if (HINPUT->IsKeyPressed(76))  // VK_RIGHT
        {
            m_transform.SetRotation(vec3(0.f, 1.f, 0.f), glm::radians(135.f));
            moveDirection += vec3(1.0f, 0.f, 0.f);
        }

        if (HINPUT->IsKeyPressed(16))  // SHIFTŰ
        {
            moveDirection += vec3(0.0f, 0.0f, 1.0f);
            /* m_transform.AddLocation(vec3(0.0f, 0.0f, 1.0f) * deltaTime * m_speed1 * 2.0f);*/
        }

        /*if (glm::length(moveDirection) > 0.0f)
        {

            moveDirection = glm::normalize(moveDirection);
        }*/
    }


    if (HINPUT->IsKeyPressed(16))  // SHIFTŰ
    {
        m_transform.AddLocation(moveDirection * deltaTime * m_speed2 * 1.5f);
    }

    // VK_DOWN ���� �� ���� �ʱ�ȭ
    if (!HINPUT->IsKeyPressed(75))
    {
        isDownPressed = false;
    }

    // VK_UP ���� �� ���� �ʱ�ȭ
    if (!HINPUT->IsKeyPressed(73))
    {
        isUpPressed = false;
    }
    int                                             rows = 20;
    int                                             cols = 20;
    std::vector<std::vector<std::shared_ptr<Node>>> grid(rows, std::vector<std::shared_ptr<Node>>(cols));

    // 2D �׸��� �ʱ�ȭ
    for (int y = 0; y < rows; ++y)
    {
        for (int x = 0; x < cols; ++x)
        {
            grid[x][y] = std::make_shared<Node>(x, y);  // make_shared ���
        }
    }

    // ��ֹ� ���� (��: ��ǥ (2,2), (2,3), (3,2)�� ��ֹ��� ����)
    grid[2][0]->isObstacle = true;
    grid[2][1]->isObstacle = true;
    grid[2][2]->isObstacle = true;


    // �������� ��ǥ�� ����
    auto start = grid[(int)(m_transform.m_pos[0] / 3.072f)]
                     [(int)(m_transform.m_pos[2] / 3.072f)];  // ����� �����̴� �ſ� ���� ��ǥ
    auto goal = grid[(int)(m_goose1.GetmPos().x / 3.072f)]
                    [(int)(m_goose1.GetmPos().z / 3.072f)];  // ���� �����̴� �ſ� ���� ��ǥ

    // A* �˰��� ����


    /*(int)m_transform.m_pos[0] / 3.072f == path[idx + 1]->GetLocationX() &&
            (int)m_transform.m_pos[2] / 3.072f == path[idx + 1]->GetLocationY()*/
    auto path = m_astar.aStar(start, goal, grid);

    if (idx + 1 < path.size())
    {
        pathIdx_x = path[idx + 1]->GetLocationX() * 3.072f + 1.536f;  // path�� ������ġ
        pathIdx_z = path[idx + 1]->GetLocationY() * 3.072f + 1.536f;  // path�� ������ġ

        gardener_x = m_transform.m_pos[0];  // ������� ������ġ
        gardener_z = m_transform.m_pos[2];  // ������� ������ġ

        if (glm::abs(gardener_x - pathIdx_x) < 0.00001f && glm::abs(gardener_z - pathIdx_z) < 0.00001f)
        {
            idx++;
        }
        else
        {
            m_transform.AddLocation(
            glm::normalize(vec3(-(gardener_x - pathIdx_x), 0.f, -(gardener_z - pathIdx_z))) * deltaTime *
            2.f);
        }
    }
    m_goose1.Update(deltaTime);
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

vec3 HBSoft::Gardener::GetmPos()
{
    return m_transform.m_pos;
}

void HBSoft::Gardener::SetmPos(float a, float b)
{
    m_transform.m_pos[0] = a;
    m_transform.m_pos[2] = b;
}