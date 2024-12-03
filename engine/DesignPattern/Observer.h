/*
author : 변한빛
description : 옵저버 패턴을 위한 헤더 파일

version: 1.0.4
date: 2024-11-15
*/

#pragma once

namespace HBSoft
{
    enum class EventList : uint16_t
    {
        MOUSE_MOVE    = 0,  // 마우스 움직이면 발생하는 이벤트 entity로 nullptr
        WINDOW_RESIZE = 1,  // 윈도우 리사이즈 이벤트 entity로 nullptr
        DEVICE_CHANGE = 2,  // 디바이스 관련된 건 여기다 추가할 것 entity로 디바이스 넘어감
    };

    class Observer
    {
    protected:
        Observer()  = default;
        ~Observer() = default;

    public:
        virtual void OnNotice(EventList event, void* entity) = 0;
        // Update는 게임에서 많이 쓰이니 OnNotice로 변경
    };
}  // namespace HBSoft
