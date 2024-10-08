#include "pch.h"
#include "ObjectManager.h"
using namespace HBSoft;

void ObjectManager::AddObject(std::unique_ptr<Actor> obj)
{
    m_registerObjID++;
    // obj->SetObjectID(m_registerObjID);
    m_objLists.insert(std::make_pair(m_registerObjID, std::move(obj)));
}

void ObjectManager::ClearObject()
{
    m_registerObjID = 0;
    m_tileManager   = nullptr;
    m_uiLists.clear();
    m_objLists.clear();

    while (!m_deleteQueue.empty())
        m_deleteQueue.pop();
}

void ObjectManager::DeleteObject(OBJECT_ID _objID)
{
    m_deleteQueue.push(_objID);
}

void ObjectManager::Update(const float _deltaTime)
{
    // 큐에 등록 안하고 삭제 처리해버리면 이벤트 처리 큰일
    while (!m_deleteQueue.empty())
    {
        if (m_objLists.contains(m_deleteQueue.front()))
            m_objLists.erase(m_deleteQueue.front());

        m_deleteQueue.pop();
    }

    for (auto& obj : m_objLists)
    {
        obj.second->Update(_deltaTime);

        if (m_tileManager != nullptr)
            m_tileManager->ProcessCollision(*(obj.second));
    }

    for (auto& obj : m_objLists)
    {
        for (auto& targetObj : m_objLists)
        {
            if (obj.first == targetObj.first)
                continue;

            obj.second->GetCollisionComponent().IsCollisionWithEvent(
            targetObj.second->GetCollisionComponent());
        }
    }
}

void ObjectManager::Render()
{
    if (m_tileManager != nullptr)
        m_tileManager->Render();

    for (auto& obj : m_objLists)
        obj.second->Render();
}

void ObjectManager::SetTileManager(TileManager* _tileManager)
{
    m_tileManager = _tileManager;
}
