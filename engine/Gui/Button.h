/*
author : ���Ѻ�
description : GUI ��ư�� �����ϱ� ���� ��� ����

version: 1.0.0
date: 2024-11-30
*/

#pragma once
#include "2D/Object2D.h"
#include "Factory/MeshFactory.h"
#include "Observer.h"
#include "Sound/HSound.h"

namespace HBSoft
{
    enum ButtonState
    {
        DEFAULT = 0,  // Ŀ���� ���� ���� ��(T_FOCUS���¿��� �ٸ� ���� T_ACTIVE�ϸ� ��ȯ�ȴ�.)
        HOVER    = 1,  // Ŀ���� ���� ���� ��
        SELECTED = 2   // T_ACTIVE ���¿��� ���ʹ�ư ������ ��
    };

    class Button : public Object2D, Observer
    {
    private:
        ButtonState                 m_state;
        std::shared_ptr<Mesh>       m_boxMesh;
        std::shared_ptr<Texture>    m_texture;
        std::shared_ptr<LayoutFont> m_font;
        std::shared_ptr<HSound>     m_clickSound;

        HRect m_collisionArea;

        std::function<void()> m_onClickCallback;

    private:
        bool IsCursorInRect();

    public:
        Button();
        virtual ~Button();

        /*
            param : rect -> ��ư�� ���� ( ��ũ�� ��ǥ�� )

            description :
               ��ư�� ������ �Ǵ� ������ �����Ѵ�
        */
        void SetArea(const HRect& rect);

        void SetImage(const TEXTURE_KEY textureKey);
        void SetOnClickCallback(std::function<void()> callback);
        void SetText(const wstringV text, const COLOR_F& color);

        virtual void Update(const float deltaTime) override;
        virtual void Render() override;
        virtual void Release() override;
        virtual void Init() override;

        virtual void OnNotice(EventList event, void* entity);
    };
}  // namespace HBSoft
