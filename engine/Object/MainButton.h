/*
author : ���Ѻ�
description : GUI ��ư�� �����ϱ� ���� ��� ����

version: 1.0.0
date: 2024-11-30
*/

#pragma once
#include "2D/Object2D.h"
#include "Factory/MeshFactory.h"

namespace HBSoft
{
    enum ButtonState
    {
        DEFAULT = 0,  // Ŀ���� ���� ���� ��(T_FOCUS���¿��� �ٸ� ���� T_ACTIVE�ϸ� ��ȯ�ȴ�.)
        HOVER    = 1,  // Ŀ���� ���� ���� ��
        SELECTED = 2   // T_ACTIVE ���¿��� ���ʹ�ư ������ ��
    };

    class MainButton : public Object2D
    {
    private:
        ButtonState              m_state;
        std::shared_ptr<Mesh>    m_boxMesh;
        std::shared_ptr<Texture> m_texture;
        std::wstring             m_text;

        HRect m_collisionArea;

        std::function<void()> m_onClickCallback;

        float m_animationTime;

    private:
        bool IsCursorInRect();
        void PlayAnimation();

    public:
        MainButton();
        virtual ~MainButton();

        void SetArea(const HRect& rect);
        void SetImage(const TEXTURE_KEY textureKey);
        void SetOnClickCallback(std::function<void()> callback);
        void SetText(const wstringV text);

        virtual void Update(const float deltaTime) override;
        virtual void Render() override;
        virtual void Release() override;
        virtual void Init() override;
    };
}  // namespace HBSoft
