/*
author : 변한빛
description : 모든 이벤트 함수들을 모으기 위한 이벤트 핸들러 소스파일

version: 1.0.1
date: 2024-11-15
*/
#pragma once

#include <functional>
#include <map>
#include <list>
#include "Singleton.h"
#include "Observer.h"

namespace HBSoft
{
    class EventHandler : public Singleton<EventHandler>
    {
    private:
        std::map<EventList, std::list<Observer*>> m_observers;

    private:
        friend class Singleton<EventHandler>;
        EventHandler();

    public:
        ~EventHandler();

        /*
            param : event -> 이벤트 리스트에 해당하는 이벤트 | entity -> 호출 대상 클래스
            description : event에 등록된 옵저버들의 OnNotice를 호출한다.
        */
        void Notify(EventList event, void* entity = nullptr);
        void AddEvent(EventList event, Observer* observer);
        void DeleteEvent(EventList event, Observer* observer);
    };
}  // namespace HBSoft
