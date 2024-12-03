#include "pch.h"
#include "Test3DObj.h"
#include "Camera.h"

using namespace HBSoft;

Test3DObj::Test3DObj()
{
    m_mesh     = HASSET->m_meshes[L"Goose.fbx"];
    m_vsShader = HASSET->m_shaders[L"AnimationVertex.hlsl"];
    /*m_vsShader = HASSET->m_shaders[L"VertexShader.hlsl"];*/

    aabb_goose =
    m_aabbcollider->CalculateAABB(aabb_goose, vec3(100.0f, 0.0f, 100.0f), vec3(0.5f, 0.5f, 0.5f));

    // SetPSShaderKey(L"PixelShader.hlsl");  // 텍스쳐 있는 놈
    m_psShader = HASSET->m_shaders[L"ColorPixelShader.hlsl"];  // 텍스쳐 없는 놈
    anim.resize(m_mesh->m_born.bornIndex.size());
}

void Test3DObj::Update(const float deltaTime)
{
    static float currentFrame = 0.f;
    static int   startFrame   = 0;
    static int   lastFrame    = 0;
    static float speed        = 30.f;
    // static int   selectAnimation = 0;

    m_aabbcollider->UpdateAABB(aabb_goose, m_transform.m_pos, vec3(0.5f, 0.5f, 0.5f));

    ImGui::SliderFloat("Speed", &speed, 0, 30.f);

    currentFrame += deltaTime * speed;
    startFrame    = m_mesh->m_animations[0]->GetStartFrame();
    lastFrame     = m_mesh->m_animations[0]->GetLastFrame();

    if (currentFrame > lastFrame)
        currentFrame = startFrame;

    anim = m_mesh->m_animations[0]->GetAnimationMatrix(currentFrame);

    m_vsShader->SetConstantBuffer(HDEVICE, (void*)&anim.at(0), sizeof(mat4) * anim.size(), 1);

    ImGui::SliderFloat("Goose speed", &m_speed1, 0.f, 50.f);

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
        m_transform.SetRotation(vec3(0.f, 1.f, 0.f), glm::radians(-35.f));  ///-45


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
            moveDirection += vec3(-1.0f, 0.0f, 0.0f);
            /*m_transform.AddLocation(vec3(-1.0f, 0.0f, 0.0f) * deltaTime * m_speed1 * 2.0f);*/
        }
    }

    if (HINPUT->IsKeyPressed(39) && !isLeftPressed)  // VK_RIGHT
    {
        isLeftPressed  = false;
        isRightPressed = true;
        moveDirection  = vec3(1.f, 0.f, 0.f);
        m_transform.SetRotation(vec3(0.f, 1.f, 0.f), glm::radians(145.f));

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
            moveDirection += vec3(1.0f, 0.0f, 0.0f);
            /*m_transform.AddLocation(vec3(1.0f, 0.0f, 0.0f) * deltaTime * m_speed1 * 2.0f);*/
        }
    }


    if (!HINPUT->IsKeyPressed(39))  // VK_RIGHT
    {
        isRightPressed = false;
    }

    if (!HINPUT->IsKeyPressed(37))  // VK_LEFT
    {
        isLeftPressed = false;
    }

    // VK_DOWN 처리
    if (HINPUT->IsKeyPressed(40) && !isUpPressed)  // VK_DOWN (VK_UP이 눌리지 않은 경우)
    {
        isDownPressed = true;   // VK_DOWN 활성화
        isUpPressed   = false;  // VK_UP 비활성화
        moveDirection = vec3(0.f, 0.f, -1.f);
        m_transform.SetRotation(vec3(0.f, 1.f, 0.f), glm::radians(55.f));

        if (HINPUT->IsKeyPressed(37))  // VK_LEFT
        {
            m_transform.SetRotation(vec3(0.f, 1.f, 0.f), glm::radians(10.f));
            moveDirection += vec3(-1.0f, 0.f, 0.f);
        }

        if (HINPUT->IsKeyPressed(39))  // VK_RIGHT
        {
            m_transform.SetRotation(vec3(0.f, 1.f, 0.f), glm::radians(100.f));
            moveDirection += vec3(1.0f, 0.f, 0.f);
        }

        if (HINPUT->IsKeyPressed(16))  // SHIFT키
        {
            moveDirection += vec3(0.0f, 0.0f, -1.0f);
            /*m_transform.AddLocation(vec3(0.0f, 0.0f, -1.0f) * deltaTime * m_speed1 * 2.0f);*/
        }
    }
    // VK_UP 처리
    if (HINPUT->IsKeyPressed(38) && !isDownPressed)  // VK_UP (VK_DOWN이 눌리지 않은 경우)
    {
        isUpPressed   = true;   // VK_UP 활성화
        isDownPressed = false;  // VK_DOWN 비활성화
        moveDirection = vec3(0.f, 0.f, 1.f);
        m_transform.SetRotation(vec3(0.f, 1.f, 0.f), glm::radians(-125.f));  /// -135


        if (HINPUT->IsKeyPressed(37))  // VK_LEFT
        {
            m_transform.SetRotation(vec3(0.f, 1.f, 0.f), glm::radians(-80.f));
            moveDirection += vec3(-1.0f, 0.f, 0.f);
        }

        if (HINPUT->IsKeyPressed(39))  // VK_RIGHT
        {
            m_transform.SetRotation(vec3(0.f, 1.f, 0.f), glm::radians(190.f));
            moveDirection += vec3(1.0f, 0.f, 0.f);
        }

        if (HINPUT->IsKeyPressed(16))  // SHIFT키
        {
            moveDirection += vec3(0.0f, 0.0f, 1.0f);
            /* m_transform.AddLocation(vec3(0.0f, 0.0f, 1.0f) * deltaTime * m_speed1 * 2.0f);*/
        }

        /*if (glm::length(moveDirection) > 0.0f)
        {

            moveDirection = glm::normalize(moveDirection);
        }*/
    }

    m_transform.AddLocation(moveDirection * deltaTime * m_speed1);

    if (HINPUT->IsKeyPressed(16))  // SHIFT키
    {
        m_transform.AddLocation(moveDirection * deltaTime * m_speed1 * 1.5f);
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
    UpdateDefaultCB();
}

void Test3DObj::Render()
{
    UINT pStrides = sizeof(Vertex);  // 1개의 정점 크기
    UINT pOffsets = 0;               // 버퍼에 시작 인덱스

    m_vsShader->SetUpToContext(HDEVICE);
    m_psShader->SetUpToContext(HDEVICE);


    HDEVICE->m_context->IASetVertexBuffers(0,
                                           1,
                                           m_mesh->m_vertexBuffer.GetAddressOf(),
                                           &pStrides,
                                           &pOffsets);

    // DXGI_FORMAT_R32_UINT는 인덱스 버퍼의 타입이 UINT라 그럼
    HDEVICE->m_context->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);


    HDEVICE->m_context->PSSetSamplers(0, 1, HDEVICE->m_samplerState.GetAddressOf());
    HDEVICE->m_context->OMSetRenderTargets(1, HDEVICE->m_rtv.GetAddressOf(), HDEVICE->m_dsv.Get());

    for (size_t i = 0; i < m_mesh->m_subMeshes.size(); i++)
    {
        if (m_mesh->m_subMeshes[i]->hasTexture)
        {
            HDEVICE->m_context->PSSetShaderResources(
            0,
            1,
            HASSET->m_textures[m_mesh->m_subMeshes[i]->textureName]->GetSRV().GetAddressOf());
        }
        HDEVICE->m_context->IASetIndexBuffer(m_mesh->m_subMeshes[i]->indexBuffer.Get(),
                                             DXGI_FORMAT_R32_UINT,
                                             0);
        HDEVICE->m_context->DrawIndexed((UINT)m_mesh->m_subMeshes[i]->indices.size(), 0, 0);
    }
}

void Test3DObj::Init() {}

void Test3DObj::Release() {}

AABB HBSoft::Test3DObj::GetaabbCollider()
{
    return aabb_goose;
}
