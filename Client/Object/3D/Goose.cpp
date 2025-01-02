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
    m_mesh  = HASSET->m_meshes[L"Goose.hbs"];
    m_sound = HASSET->m_sounds[L"goose_honk.wav"];

    m_easyRender.SetVSShader(L"BasicAniVS.hlsl");
    m_easyRender.SetPSShader(L"ColorPS.hlsl");
    m_easyRender.SetMesh(m_mesh);
    m_easyRender.SetTexture(nullptr);

    anim.resize(m_mesh->m_born.bornIndex.size());

    m_transform.SetLocation({8.0f, 0.6f, 4.0f});
    m_transform.SetScale({0.07f, 0.07f, 0.07f});
    m_transform.SetRotation(vec3(1.0f, 0.f, 0.f), 0.65f * glm::pi<float>());

    m_gooseAnis.push_back(HASSET->m_animations[L"fancywalk.skm"]);
    m_gooseAnis.push_back(HASSET->m_animations[L"gooseGallop.skm"]);
    m_gooseAnis.push_back(HASSET->m_animations[L"gooseGallopDown.skm"]);
    m_gooseAnis.push_back(HASSET->m_animations[L"gooseSneakIdle.skm"]);
    m_gooseAnis.push_back(HASSET->m_animations[L"goose_idle_proud.skm"]);
    m_gooseAnis.push_back(HASSET->m_animations[L"angryflapping.skm"]);
    m_gooseAnis.push_back(HASSET->m_animations[L"gooseMouthOpen.skm"]);
    m_gooseAnis.push_back(HASSET->m_animations[L"gooseHalfFlap.skm"]);
    m_gooseAnis.push_back(HASSET->m_animations[L"gooseHalfFlapWalking.skm"]);
    m_gooseAnis.push_back(HASSET->m_animations[L"gooseGallopDownHalfFlap.skm"]);
    m_gooseAnis.push_back(HASSET->m_animations[L"gooseSneakIdleHalfFlap.skm"]);

    m_component.AddAABBRange(m_mesh->m_autoCollision.aabb);
}

void Goose::Update(float deltaTime)
{
    // static int   selectAnimation = 0;

#ifdef _DEBUG
    ImGui::SliderFloat("Speed1", &speed1, 0, 60.f);
    ImGui::SliderFloat("Goose speed", &m_speed1, 0.f, 300.f);
#endif

    currentFrame += deltaTime * speed1;
    startFrame    = m_gooseAnis[0]->GetStartFrame();
    lastFrame     = m_gooseAnis[0]->GetLastFrame();


    if (currentFrame > lastFrame)
        currentFrame = startFrame;

    m_animstate = GooseState::goose_idle_proud;

    /*anim = m_gooseAnis[4]->GetAnimationMatrix(currentFrame);*/

    static bool isDownPressed  = false;  // VK_DOWN 상태 추적
    static bool isUpPressed    = false;  // VK_UP 상태 추적
    static bool isRightPressed = false;
    static bool isLeftPressed  = false;

    moveDirection = vec3(0.f);
    moveVec       = vec3(0.f);

    if (HINPUT->IsKeyPressed(37) && !isRightPressed)  // VK_LEFT
    {
        isLeftPressed  = true;
        isRightPressed = false;
        moveDirection  = vec3(0.f, 0.f, -1.f);
        m_animstate    = GooseState::fancywalk;
        /* anim           = m_gooseAnis[0]->GetAnimationMatrix(currentFrame);*/
        m_transform.SetRotation(vec3(0.65f * glm::pi<float>(), glm::pi<float>(), 0.f));

        if (HINPUT->IsKeyPressed(40))  // VK_DOWN
        {
            moveDirection += vec3(1.f, 0.f, 0.f);
        }
        if (HINPUT->IsKeyPressed(38))  // VK_UP
        {
            moveDirection += vec3(-1.f, 0.f, 0.f);
        }
        if (HINPUT->IsKeyPressed(16))  // SHIFT키
        {
            m_animstate = GooseState::gooseGallop;
        }

        if (HINPUT->IsKeyPressed(88))  // X키
        {
            m_animstate = GooseState::gooseHalfFlapWalking;

            if (HINPUT->IsKeyPressed(16))
                m_animstate = GooseState::gooseHalfFlap;
        }

        if (HINPUT->IsKeyPressed(17))  // Ctrl키
        {
            m_animstate = GooseState::gooseGallopDown;

            if (HINPUT->IsKeyPressed(16))  // SHIFT키
            {
                if (HINPUT->IsKeyPressed(88))  // X키
                    m_animstate = GooseState::gooseGallopDownHalfFlap;
            }
            else
            {
                if (HINPUT->IsKeyPressed(88))  // X키
                    m_animstate = GooseState::gooseGallopDownHalfFlap;
            }
        }
    }

    if (HINPUT->IsKeyPressed(39) && !isLeftPressed)  // VK_RIGHT
    {
        isLeftPressed  = false;
        isRightPressed = true;
        moveDirection  = vec3(0.f, 0.f, 1.f);
        m_animstate    = GooseState::fancywalk;
        /*anim           = m_gooseAnis[0]->GetAnimationMatrix(currentFrame);*/
        m_transform.SetRotation(vec3(0.65f * glm::pi<float>(), 0.f, 0.f));

        if (HINPUT->IsKeyPressed(40))  // VK_DOWN
        {
            moveDirection += vec3(1.f, 0.f, 0.f);
        }

        if (HINPUT->IsKeyPressed(38))  // VK_UP
        {
            moveDirection += vec3(-1.f, 0.f, 0.f);
        }

        if (HINPUT->IsKeyPressed(16))  // SHIFT키
        {
            m_animstate = GooseState::gooseGallop;
        }

        if (HINPUT->IsKeyPressed(88))  // X키
        {
            m_animstate = GooseState::gooseHalfFlapWalking;

            if (HINPUT->IsKeyPressed(16))  // SHIFT키
                m_animstate = GooseState::gooseHalfFlap;
        }

        if (HINPUT->IsKeyPressed(17))  // Ctrl키
        {
            m_animstate = GooseState::gooseGallopDown;

            if (HINPUT->IsKeyPressed(16))  // SHIFT키
            {
                if (HINPUT->IsKeyPressed(88))  // X키
                    m_animstate = GooseState::gooseGallopDownHalfFlap;
            }
            else
            {
                if (HINPUT->IsKeyPressed(88))  // X키
                    m_animstate = GooseState::gooseGallopDownHalfFlap;
            }
        }
    }


    // VK_DOWN 처리
    if (HINPUT->IsKeyPressed(40) && !isUpPressed)  // VK_DOWN (VK_UP이 눌리지 않은 경우)
    {
        isDownPressed = true;   // VK_DOWN 활성화
        isUpPressed   = false;  // VK_UP 비활성화
        moveDirection = vec3(1.f, 0.f, 0.f);

        m_animstate = GooseState::fancywalk;
        /*anim = m_gooseAnis[0]->GetAnimationMatrix(currentFrame);*/
        m_transform.SetRotation(vec3(0.65f * glm::pi<float>(), 1.5f * glm::pi<float>(), 0.f));
        if (HINPUT->IsKeyPressed(37))  // VK_LEFT
        {
            m_transform.SetRotation(vec3(0.65f * glm::pi<float>(), 1.25f * glm::pi<float>(), 0.f));
            moveDirection += vec3(0.0f, 0.f, -1.f);
        }

        if (HINPUT->IsKeyPressed(39))  // VK_RIGHT
        {
            m_transform.SetRotation(vec3(0.65f * glm::pi<float>(), 1.75f * glm::pi<float>(), 0.f));
            moveDirection += vec3(0.f, 0.f, 1.f);
        }

        if (HINPUT->IsKeyPressed(16))  // SHIFT키
        {
            m_animstate = GooseState::gooseGallop;
        }

        if (HINPUT->IsKeyPressed(88))  // x키
        {
            m_animstate = GooseState::gooseHalfFlapWalking;

            if (HINPUT->IsKeyPressed(16))
                m_animstate = GooseState::gooseHalfFlap;
        }

        if (HINPUT->IsKeyPressed(17))  // Ctrl키
        {
            m_animstate = GooseState::gooseGallopDown;

            if (HINPUT->IsKeyPressed(16))  // SHIFT키
            {
                if (HINPUT->IsKeyPressed(88))  // x키
                    m_animstate = GooseState::gooseGallopDownHalfFlap;
            }
            else
            {
                if (HINPUT->IsKeyPressed(88))  // X키
                    m_animstate = GooseState::gooseGallopDownHalfFlap;
            }
        }
    }
    // VK_UP 처리
    if (HINPUT->IsKeyPressed(38) && !isDownPressed)  // VK_UP (VK_DOWN이 눌리지 않은 경우)
    {
        isUpPressed   = true;   // VK_UP 활성화
        isDownPressed = false;  // VK_DOWN 비활성화
        moveDirection = vec3(-1.f, 0.f, 0.f);

        m_animstate = GooseState::fancywalk;
        m_transform.SetRotation(vec3(0.65f * glm::pi<float>(), 0.5f * glm::pi<float>(), 0.f));

        if (HINPUT->IsKeyPressed(37))  // VK_LEFT
        {
            m_transform.SetRotation(vec3(0.65f * glm::pi<float>(), 0.75f * glm::pi<float>(), 0.f));

            moveDirection += vec3(0.0f, 0.f, -1.f);
        }

        if (HINPUT->IsKeyPressed(39))  // VK_RIGHT
        {
            m_transform.SetRotation(vec3(0.65f * glm::pi<float>(), 0.25f * glm::pi<float>(), 0.f));
            moveDirection += vec3(0.0f, 0.f, 1.f);
        }

        if (HINPUT->IsKeyHold(16))  // SHIFT키
        {
            m_animstate = GooseState::gooseGallop;
        }

        if (HINPUT->IsKeyPressed(88))  // X키
        {
            m_animstate = GooseState::gooseHalfFlapWalking;

            if (HINPUT->IsKeyPressed(16))  // SHIFT키
                m_animstate = GooseState::gooseHalfFlap;
        }

        if (HINPUT->IsKeyPressed(17))  // Ctrl키
        {
            m_animstate = GooseState::gooseGallopDown;

            if (HINPUT->IsKeyPressed(16))  // SHIFT키
            {
                if (HINPUT->IsKeyPressed(88))  // X키
                    m_animstate = GooseState::gooseGallopDownHalfFlap;
            }
            else
            {
                if (HINPUT->IsKeyPressed(88))  // X키
                    m_animstate = GooseState::gooseGallopDownHalfFlap;
            }
        }
    }

    ////////부동자세/////////////
    if (HINPUT->IsKeyPressed(88) && !isUpPressed && !isDownPressed && !isRightPressed &&
        !isLeftPressed)  // X키
    {
        m_animstate = GooseState::angryflapping;
    }

    if (HINPUT->IsKeyPressed(32) && !isUpPressed && !isDownPressed && !isRightPressed &&
        !isLeftPressed)  // Space키
    {
        m_animstate = GooseState::gooseMouthOpen;
    }

    if (HINPUT->IsKeyDown(32))
    {
        m_sound->Play();
    }

    if (HINPUT->IsKeyPressed(17) && !isUpPressed && !isDownPressed && !isRightPressed &&
        !isLeftPressed)  // Ctrl키
    {
        m_animstate = GooseState::gooseSneakIdle;

        if (HINPUT->IsKeyPressed(88))  // X키
            m_animstate = GooseState::gooseSneakIdleHalfFlap;
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

    if (glm::length(moveDirection) >= 0.01f)
        moveDirection = glm::normalize(moveDirection);

    moveVec = moveDirection * deltaTime * m_speed1;

    if (HINPUT->IsKeyPressed(16))  // SHIFT키
        moveVec = moveDirection * deltaTime * m_speed1 * 2.f;

    anim = m_gooseAnis[m_animstate]->GetAnimationMatrix(currentFrame);
    m_transform.AddLocation(moveVec);

#ifndef _DEBUG
    m_camera->Move({m_transform.m_pos[0] + 0.9f, m_transform.m_pos[1] + 3.f, m_transform.m_pos[2]});
#endif
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

float Goose::GetLocationZ()
{
    return -1.f;
}

vec3 Goose::GetmPos()
{
    return m_transform.m_pos;
}

void Goose::SetHeightMap(std::shared_ptr<HeightMapObj> mapObj)
{
    m_mapObj = mapObj;
}

void Goose::ProcessCollision(std::shared_ptr<Object3D> obj)
{
    if (m_component.IsCollision(obj->m_component))
    {
        // vec3 normal     = m_component.m_collidedArea.ComputeNormal(moveVec, m_transform.m_pos);
        // vec3 reflectVec = glm::reflect(moveVec, normal);
        m_transform.AddLocation(-moveVec);
    }
}
