/*
author : 변한빛
description : 탭키 누르면 나오는 퀘스트 GUI 헤더파일

version: 1.0.5
date: 2025-01-07
*/
#pragma once

#include "pch.h"
#include "2D/Object2D.h"
#include "3D/PicnicRug.h"
#include "Texture/GeneralTexture.h"
#include "Font/Font.h"
#include "Observer.h"
#include "Sound/HSound.h"

namespace HBSoft
{
    enum QuestInfo
    {
        CARROT  = 0,
        PUMPKIN = 1
    };

    class QuestGUI : public Object2D, Observer
    {
    private:
        std::shared_ptr<Mesh>    m_squaredMesh;
        std::shared_ptr<Texture> m_questTexture;
        std::shared_ptr<Font>    m_quest1Font;
        std::shared_ptr<Font>    m_quest2Font;
        std::shared_ptr<Font>    m_questLine1Font;
        std::shared_ptr<Font>    m_questLine2Font;
        std::shared_ptr<HSound>  m_paperSound;

        HRect m_textRect;

        bool m_isQuest1Clear;
        bool m_isQuest2Clear;

        bool m_isTab;
        bool m_isEsc;
        bool m_isWorking;

        float m_openTimer;

        int m_carrotCount;
        int m_pumpkinCount;

        inline static const int MAX_QUESTS  = 2;
        inline static const int MAX_CARROT  = 1;
        inline static const int MAX_PUMPKIN = 1;

    private:
        virtual void OnNotice(EventList event, void* entity);

    public:
        QuestGUI();
        ~QuestGUI();

        virtual void Update(const float deltaTime) override;
        virtual void Render() override;
        virtual void Init() override;
        virtual void Release() override;
    };
}  // namespace HBSoft
