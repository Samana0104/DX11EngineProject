/*
author : 변한빛, 이지혁
description : 탭키 누르면 나오는 퀘스트 GUI 소스파일
              v1.0.1: 사운드 추가 (이지혁)

version: 1.0.1
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

    m_transform.SetScale({0.6f, 0.8f});
    m_squaredMesh  = HASSET->m_meshes[L"BOX2D"];
    m_questTexture = HASSET->m_textures[L"퀘스트.png"];
    m_paperSound   = HASSET->m_sounds[L"paperSound.mp3"];
    m_easyRender.SetMesh(m_squaredMesh);
    m_easyRender.SetTexture(m_questTexture);
    m_easyRender.SetVSShader(L"2DBasicVS.hlsl");
    m_easyRender.SetPSShader(L"2DBasicPS.hlsl");
    m_easyRender.SetDSS(ERDepthStencilState::DISABLE);

    m_questFont = FontFactory::CreateFontFromDesc(HDEVICE, desc);

    desc.m_fontWeight = DWRITE_FONT_WEIGHT_BOLD;
    m_questLineFont   = FontFactory::CreateFontFromDesc(HDEVICE, desc);

    m_questFont->SetColor({0.f, 0.f, 0.f, 1.f});
    m_questLineFont->SetColor({0.f, 0.f, 0.f, 1.f});

    m_questFont->SetHorizontalAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
    m_questLineFont->SetHorizontalAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);

    m_questFont->SetVerticalAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
    m_questLineFont->SetVerticalAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);

    Init();
    EventHandler::GetInstance().AddEvent(EventList::WINDOW_RESIZE, this);
}

QuestGUI::~QuestGUI()
{
    EventHandler::GetInstance().DeleteEvent(EventList::WINDOW_RESIZE, this);
}

void QuestGUI::OnNotice(EventList event, void* entity)
{
    switch (event)
    {
    case EventList::WINDOW_RESIZE:
        HPoint windowSize = HWINDOW->GetWindowSize();
        HPoint targetPos  = {m_squaredMesh->m_vertices[0].p.x * m_transform.m_scale.x,
                             m_squaredMesh->m_vertices[0].p.y};
        HPoint screenPos  = Transform2D::ConvertNDCToScreen(windowSize, targetPos);
        m_textRect        = {screenPos.x, screenPos.y, screenPos.x + 100.f, screenPos.y + 100.f};
        break;
    }
}

void QuestGUI::Init()
{
    m_isTab         = false;
    m_isEsc         = false;
    m_isWorking     = false;
    m_isQuest1Clear = false;
    m_isQuest2Clear = false;

    m_openTimer        = 0.f;
    m_leftCarrotCount  = 5;
    m_leftPumpkinCount = 5;
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

        if (m_isWorking)
        {
            if (!m_paperSound->IsPlaying())
                m_paperSound->Play();
        }
        else
            m_paperSound->Stop();

        m_transform.SetLocation({m_transform.m_pos.x, glm::lerp(-2.f, -0.3f, m_openTimer)});
    }

    for (int i = 0; i < MAX_QUESTS; i++)
    {
        switch (i)
        {
        case QuestInfo::CARROT:
            m_questFont->DrawMsg(L"현재 남은 당근 : " + std::to_wstring(m_leftCarrotCount));

            if (m_isQuest1Clear)
                m_questLineFont->DrawMsg(L"ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ");
            break;

        case QuestInfo::PUMPKIN:
            m_questFont->DrawMsg(L"현재 남은 호박 : " + std::to_wstring(m_leftPumpkinCount));

            if (m_isQuest2Clear)
                m_questLineFont->DrawMsg(L"ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ");
            break;
        }
    }
    UpdateDefaultCB();
}

void QuestGUI::Render()
{
    if (m_openTimer > 0.f)
        m_easyRender.Draw();
}

void QuestGUI::Release() {}
