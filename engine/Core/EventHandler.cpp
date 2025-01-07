#include "pch.h"
#include "EventHandler.h"
using namespace HBSoft;

EventHandler::EventHandler()
{
    m_observers.insert(std::make_pair(EventList::WINDOW_RESIZE, std::list<Observer*>()));
    m_observers.insert(std::make_pair(EventList::DEVICE_CHANGE, std::list<Observer*>()));
    m_observers.insert(std::make_pair(EventList::QUEST_CLEAR, std::list<Observer*>()));
    m_observers.insert(std::make_pair(EventList::CARROT_DOWN, std::list<Observer*>()));
    m_observers.insert(std::make_pair(EventList::PUMPKIN_DOWN, std::list<Observer*>()));
}

EventHandler::~EventHandler()
{
    m_observers.clear();
}

void EventHandler::Notify(EventList event, void* entity)
{
    assert(m_observers.contains(event));
    auto& observerList = m_observers[event];

    for (Observer* observer : observerList)
        observer->OnNotice(event, entity);
}

void EventHandler::AddEvent(EventList event, Observer* observer)
{
    assert(m_observers.contains(event));
    m_observers[event].push_back(observer);
}

void EventHandler::DeleteEvent(EventList event, Observer* observer)
{
    assert(m_observers.contains(event));
    m_observers[event].remove(observer);
}
