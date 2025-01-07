/*
author : 변한빛
description : GUI 버튼을 정의하기 위한 헤더 파일

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
        DEFAULT = 0,  // 커서가 위에 없을 때(T_FOCUS상태에서 다른 곳을 T_ACTIVE하면 전환된다.)
        HOVER    = 1,  // 커서가 위에 있을 때
        SELECTED = 2   // T_ACTIVE 상태에서 왼쪽버튼 놓았을 때
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
            param : rect -> 버튼의 영역 ( 스크린 좌표계 )

            description :
               버튼이 렌더링 되는 영역을 지정한다
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
