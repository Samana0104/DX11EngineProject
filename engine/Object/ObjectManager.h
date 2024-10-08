#pragma once
#include "Actor.h"
#include "TileManager.h"

namespace HBSoft
{
    class ObjectManager
    {
    private:
        std::map<OBJECT_ID, std::unique_ptr<Object>> mUILists;  // ���Ŀ� ��� ����?
        std::map<OBJECT_ID, std::unique_ptr<Actor>>  mObjLists;

        std::queue<OBJECT_ID> mDeleteQueue;

        TileManager* mTileManager = nullptr;  // Ÿ�� �Ŵ��� ���� �ȵθ� �ʹ� ���� ���� �˻� ��
        OBJECT_ID registerObjID = 0;

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
