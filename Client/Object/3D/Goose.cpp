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

    m_gooseStand.min      = {-3.f, 0.f, -2.9f};
    m_gooseStand.max      = {3.f, 10.f, 2.9f};
    m_gooseCrounching.min = {-3.f, 0.f, -2.9f};
    m_gooseCrounching.max = {3.f, 5.f, 2.9f};
    m_component.AddAABBRange(m_gooseStand, "Goose");

    m_socketBornIdx = m_mesh->m_born.objectIndex["beaklower"];
    Init();
}

void Goose::Update(float deltaTime)
{
    // static int   selectAnimation = 0;

#ifdef _DEBUG
    ImGui::SliderFloat("Speed1", &speed1, 0, 60.f);
    ImGui::SliderFloat("Goose speed", &m_speed1, 0.f, 300.f);
#endif
    m_isInit  = false;
    m_isInit2 = false;

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

    vec3 moveDirection = vec3(0.f);
    moveVec            = vec3(0.f);

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
    {
        moveDirection   = glm::normalize(moveDirection);
        m_moveDirection = moveDirection;
    }

    moveVec = moveDirection * deltaTime * m_speed1;

    if (HINPUT->IsKeyPressed(16))  // SHIFT키
        moveVec = moveDirection * deltaTime * m_speed1 * 2.f;

    anim = m_gooseAnis[m_animstate]->GetAnimationMatrix(currentFrame);
    m_transform.AddLocation(moveVec);

    if (m_socketObj)
    {
        mat4 offsetMat =
        m_transform.m_worldMat * anim[m_socketBornIdx] * m_mesh->m_born.bindPoseInvMat[m_socketBornIdx];

        vec3 scale;
        vec3 pos;
        quat rot;
        vec3 dummy1;
        vec4 dummy2;

        glm::decompose(offsetMat, scale, rot, pos, dummy1, dummy2);

        pos.y -= 0.2f;
        m_socketObj->m_transform.SetLocation(pos + m_moveDirection * 0.2f);
        // m_socketObj->m_transform.SetRotation(rot);
    }


#ifndef _DEBUG
    m_camera->Move({m_transform.m_pos[0] + 1.f, m_transform.m_pos[1] + 2.5f, m_transform.m_pos[2]});
#endif
    m_easyRender.UpdateVSCB((void*)&anim.at(0), sizeof(mat4) * anim.size(), 1);
}

void Goose::Render()
{
    m_easyRender.Draw();
}

void Goose::Release() {}

void Goose::Init()
{
    m_transform.SetScale({0.07f, 0.07f, 0.07f});
    m_transform.SetRotation(vec3(1.0f, 0.f, 0.f), 0.65f * glm::pi<float>());
    m_isInit  = false;
    m_isInit2 = false;
}

float Goose::GetLocationX()
{
    return -1.f;
}

float Goose::GetLocationZ()
{
    return -1.f;
}

vec3 Goose::GetPos()
{
    return m_transform.m_pos;
}

void Goose::SetHeightMap(std::shared_ptr<HeightMapObj> mapObj)
{
    m_mapObj = mapObj;
}

void Goose::SetSocket(std::shared_ptr<Object3D> socketObj)
{
    m_socketObj = socketObj;
    m_socketObj->m_transform.SetLocation({0.f, 0.f, 0.f});
    // m_socketObj->m_transform.SetRotation({0.f, 0.f, 0.f});
}

bool Goose::HasSocket() const
{
    if (m_socketObj)
        return true;
    else
        return false;
}

void Goose::ProcessCollision(std::shared_ptr<Object3D> obj)
{
    bool isSocket  = false;
    bool isKeyDown = false;

    if (obj == m_socketObj)
        return;

    if (HINPUT->IsKeyDown(0x5A) && !m_isInit)
    {
        if (m_socketObj)
        {
            isSocket = true;
        }

        isKeyDown = true;
    }

    if (m_component.IsCollision(obj->m_component))
    {
        if (isKeyDown)
        {
            std::shared_ptr<Dynamic3DObj> dynamicObj = std::dynamic_pointer_cast<Dynamic3DObj>(obj);
            if (dynamicObj)
            {
                SetSocket(obj);
                m_isInit = true;
            }
        }

        float colMaxY = -9999.f;
        for (size_t i = 0; i < m_component.m_collidedAreas.size(); i++)
        {
            if (m_component.m_collidedAreas[i].max.y > colMaxY)
                colMaxY = m_component.m_collidedAreas[i].max.y;
        }

        if (glm::abs(m_transform.m_pos.y - colMaxY) < 0.3f)
        {
            m_transform.SetLocation({m_transform.m_pos.x, colMaxY, m_transform.m_pos.z});
        }
        else
        {
            vec3 reflectVec;


            if (glm::dot(m_component.m_collidedNormal, -moveVec) >= 0.f)
                reflectVec = glm::proj<vec3>(-moveVec, m_component.m_collidedNormal);
            else
                reflectVec = moveVec;

            m_transform.AddLocation(reflectVec);
        }

        m_isInit2 = true;
    }
    else
    {
        if (!m_isInit2)
        {
            m_transform.AddLocation({0.f, -0.2f, 0.f});
            m_isInit2 = true;
        }
    }

    float height = m_mapObj->GetHeight(m_transform.m_pos);
    if (m_transform.m_pos.y < height)
    {
        m_transform.SetLocation({m_transform.m_pos[0], height, m_transform.m_pos[2]});
    }

    if (isSocket)
    {
        m_socketObj->m_transform.SetLocation(
        vec3(m_transform.m_pos.x, m_transform.m_pos.y + 0.1f, m_transform.m_pos.z) +
        m_moveDirection * 0.5f);
        m_socketObj = nullptr;
        m_isInit    = true;
    }

    UpdateDefaultCB();
}
