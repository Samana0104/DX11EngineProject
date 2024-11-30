#include "pch.h"
#include "Goose.h"

using namespace HBSoft;

Goose::Goose()
{
    // SetTextureKey(L"goose1.png");
    // SetMeshKey(L"BOX3D");
    // SetVSShaderKey(L"VertexShader.hlsl");
    // SetPSShaderKey(L"PixelShader.hlsl");
}

void Goose::Update(float deltaTime)
{
    ImGui::SliderFloat("Goose speed", &m_speed1, 0.f, 300.f);

    static bool isDownPressed  = false;  // VK_DOWN ���� ����
    static bool isUpPressed    = false;  // VK_UP ���� ����
    static bool isRightPressed = false;
    static bool isLeftPressed  = false;
    vec3        moveDirection  = vec3(0.f, 0.f, 0.f);


    if (HINPUT->IsKeyPressed(37) && !isRightPressed)  // VK_LEFT
    {
        isLeftPressed  = true;
        isRightPressed = false;
        moveDirection  = vec3(-1.f, 0.f, 0.f);

        if (HINPUT->IsKeyPressed(40))  // VK_DOWN
        {
            moveDirection += vec3(0.f, 0.f, -1.f);
        }
        if (HINPUT->IsKeyPressed(38))  // VK_UP
        {
            moveDirection += vec3(0.f, 0.f, 1.f);
        }
        if (HINPUT->IsKeyPressed(16))
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

        if (HINPUT->IsKeyPressed(40))  // VK_DOWN
        {
            moveDirection += vec3(0.f, 0.f, -1.f);
        }

        if (HINPUT->IsKeyPressed(38))  // VK_UP
        {
            moveDirection += vec3(0.f, 0.f, 1.f);
        }

        if (HINPUT->IsKeyPressed(16))
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

    // VK_DOWN ó��
    if (HINPUT->IsKeyPressed(40) && !isUpPressed)  // VK_DOWN (VK_UP�� ������ ���� ���)
    {
        isDownPressed = true;   // VK_DOWN Ȱ��ȭ
        isUpPressed   = false;  // VK_UP ��Ȱ��ȭ

        moveDirection = vec3(0.f, 0.f, -1.f);

        if (HINPUT->IsKeyPressed(37))  // VK_LEFT
        {
            moveDirection += vec3(-1.0f, 0.f, 0.f);
        }

        if (HINPUT->IsKeyPressed(39))  // VK_RIGHT
        {
            moveDirection += vec3(1.0f, 0.f, 0.f);
        }

        if (HINPUT->IsKeyPressed(16))
        {
            moveDirection += vec3(0.0f, 0.0f, -1.0f);
            /*m_transform.AddLocation(vec3(0.0f, 0.0f, -1.0f) * deltaTime * m_speed1 * 2.0f);*/
        }
    }
    // VK_UP ó��
    if (HINPUT->IsKeyPressed(38) && !isDownPressed)  // VK_UP (VK_DOWN�� ������ ���� ���)
    {
        isUpPressed   = true;   // VK_UP Ȱ��ȭ
        isDownPressed = false;  // VK_DOWN ��Ȱ��ȭ


        moveDirection = vec3(0.f, 0.f, 1.f);

        if (HINPUT->IsKeyPressed(37))  // VK_LEFT
        {
            moveDirection += vec3(-1.0f, 0.f, 0.f);
        }

        if (HINPUT->IsKeyPressed(39))  // VK_RIGHT
        {
            moveDirection += vec3(1.0f, 0.f, 0.f);
        }

        if (HINPUT->IsKeyPressed(16))
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

    if (HINPUT->IsKeyPressed(16))
    {
        m_transform.AddLocation(moveDirection * deltaTime * m_speed1 * 1.5f);
    }

    // VK_DOWN ���� �� ���� �ʱ�ȭ
    if (!HINPUT->IsKeyPressed(40))
    {
        isDownPressed = false;
    }

    // VK_UP ���� �� ���� �ʱ�ȭ
    if (!HINPUT->IsKeyPressed(38))
    {
        isUpPressed = false;
    }

    UpdateDefaultCB();
}

void Goose::Render()
{
    // UINT pStrides = sizeof(Vertex);  // 1���� ���� ũ��
    // UINT pOffsets = 0;               // ���ۿ� ���� �ε���

    // m_vsShader->SetUpToContext(HDEVICE);
    // m_psShader->SetUpToContext(HDEVICE);

    // HDEVICE->m_context->IASetVertexBuffers(0,
    //                                        1,
    //                                        m_mesh->m_vertexBuffer.GetAddressOf(),
    //                                        &pStrides,
    //                                        &pOffsets);

    //// DXGI_FORMAT_R32_UINT�� �ε��� ������ Ÿ���� UINT�� �׷�
    // HDEVICE->m_context->IASetIndexBuffer(m_mesh->m_indexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
    // HDEVICE->m_context->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    // HDEVICE->m_context->PSSetShaderResources(0, 1, m_texture->GetSRV().GetAddressOf());


    // HDEVICE->m_context->PSSetSamplers(0, 1, HDEVICE->m_samplerState.GetAddressOf());
    // HDEVICE->m_context->OMSetRenderTargets(1, HDEVICE->m_rtv.GetAddressOf(), HDEVICE->m_dsv.Get());
    // HDEVICE->m_context->DrawIndexed((UINT)m_mesh->m_indices.size(), 0, 0);
}

void Goose::Release() {}

void Goose::Init() {}
