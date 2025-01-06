/*
author : º¯ÇÑºû
description : ÅÇÅ° ´©¸£¸é ³ª¿À´Â Äù½ºÆ® GUI ¼Ò½ºÆÄÀÏ

version: 1.0.0
date: 2025-01-02
*/

#include "pch.h"
#include "QuestGUI.h"
using namespace HBSoft;

QuestGUI::QuestGUI()
{
    FontDesc desc;
    {
        desc.m_fontName       = L"NotoSansCJKkr-Regular";
        desc.m_fontLocaleName = L"ko-kr";
        desc.m_fontSize       = 35.f;
        desc.m_fontStretch    = DWRITE_FONT_STRETCH_NORMAL;
        desc.m_fontStyle      = DWRITE_FONT_STYLE_NORMAL;
        desc.m_fontWeight     = DWRITE_FONT_WEIGHT_NORMAL;
    }
    m_isTab     = false;
    m_isEsc     = false;
    m_isWorking = false;

    m_openTimer = 0.f;

    m_transform.SetScale({0.6f, 0.8f});
    m_squaredMesh  = HASSET->m_meshes[L"BOX2D"];
    m_questTexture = HASSET->m_textures[L"Äù½ºÆ®.png"];
    m_easyRender.SetMesh(m_squaredMesh);
    m_easyRender.SetTexture(m_questTexture);
    m_easyRender.SetVSShader(L"2DBasicVS.hlsl");
    m_easyRender.SetPSShader(L"2DBasicPS.hlsl");
    m_easyRender.SetDSS(ERDepthStencilState::DISABLE);

    m_questFont = FontFactory::CreateFontFromDesc(HDEVICE, desc);
}

void QuestGUI::AddQuest(std::wstring questMsg) {}

void QuestGUI::OnNotice(EventList event, void* entity) {}

void QuestGUI::Init()
{
    m_isTab     = false;
    m_isEsc     = false;
    m_isWorking = false;

    m_openTimer = 0.f;
}

void QuestGUI::Update(const float deltaTime)
{
    if (HINPUT->IsKeyDown(VK_ESCAPE))
    {
        if (m_isEsc)
            m_isEsc = false;
        else
            m_isEsc = true;

        m_isTab     = false;
        m_isWorking = false;
        m_openTimer = 0.f;
    }

    if (HINPUT->IsKeyDown(VK_TAB))
    {
        if (!m_isEsc && m_isTab)
        {
            m_isTab     = false;
            m_isWorking = true;
        }
        else if (!m_isEsc && !m_isTab)
        {
            m_isTab     = true;
            m_isWorking = true;
        }
    }

    if (!m_isEsc && m_isWorking)
    {
        if (m_isTab)
            m_openTimer += deltaTime * 2.f;
        else
            m_openTimer -= deltaTime * 2.f;

        if (m_openTimer < 0.f)
        {
            m_isWorking = false;
            m_openTimer = 0.f;
        }
        else if (m_openTimer > 1.f)
        {
            m_isWorking = false;
            m_openTimer = 1.f;
        }

        m_transform.SetLocation({m_transform.m_pos.x, glm::lerp(-2.f, -0.3f, m_openTimer)});
    }
    UpdateDefaultCB();
}

void QuestGUI::Render()
{
    if (m_openTimer > 0.f)
        m_easyRender.Draw();
}

void QuestGUI::Release() {}
