#pragma once
#include "Actor.h"
#include "TileManager.h"

namespace HBSoft
{
    class ObjectManager
    {
    private:
        std::map<OBJECT_ID, std::unique_ptr<Object2D>> m_uiLists;  // ���Ŀ� ��� ����?
        std::map<OBJECT_ID, std::unique_ptr<Actor>>    m_objLists;

        std::queue<OBJECT_ID> m_deleteQueue;

        // Ÿ�� �Ŵ��� ���� �ȵθ� �ʹ� ���� ���� �˻� ��
        TileManager* m_tileManager   = nullptr;
        OBJECT_ID    m_registerObjID = 0;

    public:
        ObjectManager() = default;

        void AddObject(std::unique_ptr<Actor> _obj);
        void SetTileManager(TileManager* _tileManager);

        void DeleteObject(OBJECT_ID _objID);
        void ClearObject();

        void Update(const float _deltaTime);
        void Render();
    };
}  // namespace HBSoft
