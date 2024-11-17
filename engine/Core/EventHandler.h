/*
author : ���Ѻ�
description : ��� �̺�Ʈ �Լ����� ������ ���� �̺�Ʈ �ڵ鷯 �ҽ�����

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
            param : event -> �̺�Ʈ ����Ʈ�� �ش��ϴ� �̺�Ʈ | entity -> ȣ�� ��� Ŭ����
            description : event�� ��ϵ� ���������� OnNotice�� ȣ���Ѵ�.
        */
        void Notify(EventList event, void* entity = nullptr);
        void AddEvent(EventList event, Observer* observer);
        void DeleteEvent(EventList event, Observer* observer);
    };
}  // namespace HBSoft
