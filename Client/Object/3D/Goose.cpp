/*
author : 정찬빈
description :

version: 1.1.0
date: 2024-11-30
*/

#include "pch.h"
#include "Goose.h"

using namespace HBSoft;

Goose::Goose()
{
    m_mesh = HASSET->m_meshes[L"Goose.hbs"];

    m_easyRender.SetVSShader(L"AnimationVertex.hlsl");
    m_easyRender.SetPSShader(L"ColorPixelShader.hlsl");
    m_easyRender.SetMesh(m_mesh);
    m_easyRender.SetTexture(nullptr);

    anim.resize(m_mesh->m_born.bornIndex.size());

    m_transform.SetLocation({0.0f, 0.6f, -5.0f});
    m_transform.m_scale = {0.07f, 0.07f, 0.07f};
    m_transform.SetRotation(vec3(1.0f, 0.f, 0.f), 90.f);
}

void Goose::Update(float deltaTime)
{
    static float currentFrame = 0.f;
    static int   startFrame   = 0;
    static int   lastFrame    = 0;
    static float speed1       = 30.f;
    // static int   selectAnimation = 0;

    ImGui::SliderFloat("Speed1", &speed1, 0, 60.f);

    currentFrame += deltaTime * speed1;
    startFrame    = m_mesh->m_animations[0]->GetStartFrame();
    lastFrame     = m_mesh->m_animations[0]->GetLastFrame();

    if (currentFrame > lastFrame)
        currentFrame = startFrame;

    anim = m_mesh->m_animations[6]->GetAnimationMatrix(currentFrame);


    ImGui::SliderFloat("Goose speed", &m_speed1, 0.f, 300.f);

    static bool isDownPressed  = false;  // VK_DOWN 상태 추적
    static bool isUpPressed    = false;  // VK_UP 상태 추적
    static bool isRightPressed = false;
    static bool isLeftPressed  = false;
    vec3        moveDirection  = vec3(0.f, 0.f, 0.f);


    if (HINPUT->IsKeyPressed(37) && !isRightPressed)  // VK_LEFT
    {
        isLeftPressed  = true;
        isRightPressed = false;
        moveDirection  = vec3(-1.f, 0.f, 0.f);
        anim           = m_mesh->m_animations[0]->GetAnimationMatrix(currentFrame);
        m_transform.SetRotation(vec3(90.f, -45.f - 22.5f, 0.f));

        /* m_transform.AddRotation(vec3(0.f, 1.f, 0.f), glm::radians(90.f));*/


        if (HINPUT->IsKeyPressed(40))  // VK_DOWN
        {

            moveDirection += vec3(0.f, 0.f, -1.f);
            /* m_transform.SetRotation(vec3(0.f, 1.f, 0.f), glm::radians(-45.f));*/
        }
        if (HINPUT->IsKeyPressed(38))  // VK_UP
        {

            moveDirection += vec3(0.f, 0.f, 1.f);
            /*    m_transform.SetRotation(vec3(0.f, 1.f, 0.f), glm::radians(-135.f));*/
        }
        if (HINPUT->IsKeyPressed(16))  // SHIFT키
        {
            anim           = m_mesh->m_animations[2]->GetAnimationMatrix(currentFrame);
            moveDirection += vec3(-1.0f, 0.0f, 0.0f);


            /*m_transform.AddLocation(vec3(-1.0f, 0.0f, 0.0f) * deltaTime * m_speed1 * 2.0f);*/
        }

        if (HINPUT->IsKeyPressed(88))  // X키
        {
            anim = m_mesh->m_animations[26]->GetAnimationMatrix(currentFrame);

            if (HINPUT->IsKeyPressed(16))
                anim = m_mesh->m_animations[25]->GetAnimationMatrix(currentFrame);
        }

        if (HINPUT->IsKeyPressed(17))  // Ctrl키
        {
            anim = m_mesh->m_animations[3]->GetAnimationMatrix(currentFrame);


            if (HINPUT->IsKeyPressed(16))  // SHIFT키
            {
                if (HINPUT->IsKeyPressed(88))  // X키
                    anim = m_mesh->m_animations[29]->GetAnimationMatrix(currentFrame);
            }
            else
            {
                if (HINPUT->IsKeyPressed(88))  // X키
                    anim = m_mesh->m_animations[29]->GetAnimationMatrix(currentFrame);
            }
        }
    }

    if (HINPUT->IsKeyPressed(39) && !isLeftPressed)  // VK_RIGHT
    {
        isLeftPressed  = false;
        isRightPressed = true;
        moveDirection  = vec3(1.f, 0.f, 0.f);
        anim           = m_mesh->m_animations[0]->GetAnimationMatrix(currentFrame);
        m_transform.SetRotation(vec3(90.f, 45.f + 22.5f, 0.f));

        if (HINPUT->IsKeyPressed(40))  // VK_DOWN
        {
            /*   m_transform.SetRotation(vec3(0.f, 1.f, 0.f), glm::radians(45.f));*/
            moveDirection += vec3(0.f, 0.f, -1.f);
        }

        if (HINPUT->IsKeyPressed(38))  // VK_UP
        {
            /*    m_transform.SetRotation(vec3(0.f, 1.f, 0.f), glm::radians(-135.f));*/
            moveDirection += vec3(0.f, 0.f, 1.f);
        }

        if (HINPUT->IsKeyPressed(16))  // SHIFT키
        {
            anim = m_mesh->m_animations[2]->GetAnimationMatrix(currentFrame);

            moveDirection += vec3(1.0f, 0.0f, 0.0f);

            /*m_transform.AddLocation(vec3(1.0f, 0.0f, 0.0f) * deltaTime * m_speed1 * 2.0f);*/
        }

        if (HINPUT->IsKeyPressed(88))  // X키
        {
            anim = m_mesh->m_animations[26]->GetAnimationMatrix(currentFrame);

            if (HINPUT->IsKeyPressed(16))  // SHIFT키
                anim = m_mesh->m_animations[25]->GetAnimationMatrix(currentFrame);
        }

        if (HINPUT->IsKeyPressed(17))  // Ctrl키
        {
            anim = m_mesh->m_animations[3]->GetAnimationMatrix(currentFrame);

            if (HINPUT->IsKeyPressed(16))  // SHIFT키
            {
                if (HINPUT->IsKeyPressed(88))  // X키
                    anim = m_mesh->m_animations[29]->GetAnimationMatrix(currentFrame);
            }
            else
            {
                if (HINPUT->IsKeyPressed(88))  // X키
                    anim = m_mesh->m_animations[29]->GetAnimationMatrix(currentFrame);
            }
        }
    }


    // VK_DOWN 처리
    if (HINPUT->IsKeyPressed(40) && !isUpPressed)  // VK_DOWN (VK_UP이 눌리지 않은 경우)
    {
        isDownPressed = true;   // VK_DOWN 활성화
        isUpPressed   = false;  // VK_UP 비활성화
        moveDirection = vec3(0.f, 0.f, -1.f);

        anim = m_mesh->m_animations[0]->GetAnimationMatrix(currentFrame);
        m_transform.SetRotation(vec3(90.f, 135.f, 0.f));
        if (HINPUT->IsKeyPressed(37))  // VK_LEFT
        {

            m_transform.SetRotation(vec3(90.f, -135.f + 22.5f + 90.f, 0.f));
            if (HINPUT->IsKeyPressed(32))
                anim = m_mesh->m_animations[13]->GetAnimationMatrix(currentFrame);
            moveDirection += vec3(-1.0f, 0.f, 0.f);
        }

        if (HINPUT->IsKeyPressed(39))  // VK_RIGHT
        {
            m_transform.SetRotation(vec3(90.f, -135.f - 22.5f - 90.f, 0.f));
            moveDirection += vec3(1.0f, 0.f, 0.f);
        }


        if (HINPUT->IsKeyPressed(16))  // SHIFT키
        {
            anim = m_mesh->m_animations[2]->GetAnimationMatrix(currentFrame);

            moveDirection += vec3(0.0f, 0.0f, -1.0f);
            /*m_transform.AddLocation(vec3(0.0f, 0.0f, -1.0f) * deltaTime * m_speed1 * 2.0f);*/
        }

        if (HINPUT->IsKeyPressed(88))  // x키
        {

            anim = m_mesh->m_animations[26]->GetAnimationMatrix(currentFrame);

            if (HINPUT->IsKeyPressed(16))
                anim = m_mesh->m_animations[25]->GetAnimationMatrix(currentFrame);
        }

        if (HINPUT->IsKeyPressed(17))  // Ctrl키
        {
            anim = m_mesh->m_animations[3]->GetAnimationMatrix(currentFrame);

            if (HINPUT->IsKeyPressed(16))  // SHIFT키
            {
                if (HINPUT->IsKeyPressed(88))  // x키
                    anim = m_mesh->m_animations[29]->GetAnimationMatrix(currentFrame);
            }
            else
            {
                if (HINPUT->IsKeyPressed(88))  // X키
                    anim = m_mesh->m_animations[29]->GetAnimationMatrix(currentFrame);
            }
        }
    }
    // VK_UP 처리
    if (HINPUT->IsKeyPressed(38) && !isDownPressed)  // VK_UP (VK_DOWN이 눌리지 않은 경우)
    {
        isUpPressed   = true;   // VK_UP 활성화
        isDownPressed = false;  // VK_DOWN 비활성화
        moveDirection = vec3(0.f, 0.f, 1.f);

        anim = m_mesh->m_animations[0]->GetAnimationMatrix(currentFrame);
        m_transform.SetRotation(vec3(90.f, 0.f, 0.f));

        if (HINPUT->IsKeyPressed(37))  // VK_LEFT
        {
            /* m_transform.SetRotation(vec3(90.f, 45.f, 0));  ///  90 ,45*/
            m_transform.SetRotation(vec3(90.f, -135.f + 22.5f + 90.f + 180.f, 0.f));

            moveDirection += vec3(-1.0f, 0.f, 0.f);
        }

        if (HINPUT->IsKeyPressed(39))  // VK_RIGHT
        {
            m_transform.SetRotation(vec3(90.f, -135.f - 22.5f, 0.f));
            moveDirection += vec3(1.0f, 0.f, 0.f);
        }

        if (HINPUT->IsKeyHold(16))  // SHIFT키
        {
            anim = m_mesh->m_animations[2]->GetAnimationMatrix(currentFrame);

            moveDirection += vec3(0.0f, 0.0f, 1.0f);
            /* m_transform.AddLocation(vec3(0.0f, 0.0f, 1.0f) * deltaTime * m_speed1 * 2.0f);*/
        }

        if (HINPUT->IsKeyPressed(88))  // X키
        {
            anim = m_mesh->m_animations[26]->GetAnimationMatrix(currentFrame);
            if (HINPUT->IsKeyPressed(16))  // SHIFT키
                anim = m_mesh->m_animations[25]->GetAnimationMatrix(currentFrame);
        }

        if (HINPUT->IsKeyPressed(17))  // Ctrl키
        {
            anim = m_mesh->m_animations[3]->GetAnimationMatrix(currentFrame);


            if (HINPUT->IsKeyPressed(16))  // SHIFT키
            {
                if (HINPUT->IsKeyPressed(88))  // X키
                    anim = m_mesh->m_animations[29]->GetAnimationMatrix(currentFrame);
            }
            else
            {
                if (HINPUT->IsKeyPressed(88))  // X키
                    anim = m_mesh->m_animations[29]->GetAnimationMatrix(currentFrame);
            }
        }
    }

    ////////부동자세/////////////
    if (HINPUT->IsKeyPressed(88) && !isUpPressed && !isDownPressed && !isRightPressed &&
        !isLeftPressed)  // X키
    {
        anim = m_mesh->m_animations[7]->GetAnimationMatrix(currentFrame);
    }

    if (HINPUT->IsKeyPressed(32) && !isUpPressed && !isDownPressed && !isRightPressed &&
        !isLeftPressed)  // Space키
    {
        anim = m_mesh->m_animations[13]->GetAnimationMatrix(currentFrame);
    }

    if (HINPUT->IsKeyPressed(17) && !isUpPressed && !isDownPressed && !isRightPressed &&
        !isLeftPressed)  // Ctrl키
    {
        anim = m_mesh->m_animations[5]->GetAnimationMatrix(currentFrame);

        if (HINPUT->IsKeyPressed(88))  // X키
            anim = m_mesh->m_animations[30]->GetAnimationMatrix(currentFrame);
    }


    if (!HINPUT->IsKeyPressed(39))  // VK_RIGHT
    {
        isRightPressed = false;
    }

    if (!HINPUT->IsKeyPressed(37))  // VK_LEFT
    {
        isLeftPressed = false;
    }

    // VK_DOWN 해제 시 상태 초기화
    if (!HINPUT->IsKeyPressed(40))
    {
        isDownPressed = false;
    }

    // VK_UP 해제 시 상태 초기화
    if (!HINPUT->IsKeyPressed(38))
    {
        isUpPressed = false;
    }
    float height = m_mapObj->GetHeight(m_transform.m_pos);

    m_transform.AddLocation(moveDirection * deltaTime * m_speed1);

    if (HINPUT->IsKeyPressed(16))  // SHIFT키
    {
        m_transform.AddLocation(moveDirection * deltaTime * m_speed1 * 1.5f);
    }

    m_transform.SetLocation({m_transform.m_pos.x, height, m_transform.m_pos.z});

    UpdateDefaultCB();
    m_easyRender.UpdateVSCB((void*)&anim.at(0), sizeof(mat4) * anim.size(), 1);
}

void Goose::Render()
{
    m_easyRender.Draw();
}

void Goose::Release() {}

void Goose::Init() {}

float Goose::GetLocationX()
{
    return -1.f;
}

float HBSoft::Goose::GetLocationZ()
{
    return -1.f;
}

vec3 Goose::GetGooseTransform()
{
    return m_transform.m_pos;
}

void Goose::SetHeightMap(std::shared_ptr<HeightMapObj> mapObj)
{
    m_mapObj = mapObj;
}
