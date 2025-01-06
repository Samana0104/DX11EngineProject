/*
author : ���Ѻ�
description : ��Ű ������ ������ ����Ʈ GUI �������

version: 1.0.0
date: 2025-01-02
*/
#pragma once

#include "pch.h"
#include "2D/Object2D.h"
#include "Texture/GeneralTexture.h"
#include "Font/Font.h"
#include "Observer.h"

namespace HBSoft
{
    struct QuestInfo
    {};

    class QuestGUI : public Object2D, Observer

    {
    private:
        std::shared_ptr<Mesh>    m_squaredMesh;
        std::shared_ptr<Texture> m_questTexture;
        std::shared_ptr<Font>    m_questFont;

        bool m_isTab;
        bool m_isEsc;
        bool m_isWorking;

        float m_openTimer;

    private:
        virtual void OnNotice(EventList event, void* entity);

    public:
        QuestGUI();

        void AddQuest(std::wstring questMsg);

        virtual void Update(const float deltaTime) override;
        virtual void Render() override;
        virtual void Init() override;
        virtual void Release() override;
    };
}  // namespace HBSoft
