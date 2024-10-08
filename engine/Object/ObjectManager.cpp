#include "pch.h"
#include "ObjectManager.h"
using namespace HBSoft;

void ObjectManager::AddObject(std::unique_ptr<Actor> _obj)
{
	registerObjID++;
	_obj->SetObjectID(registerObjID);
	mObjLists.insert(std::make_pair(registerObjID, std::move(_obj)));
}

void ObjectManager::ClearObject()
{
	registerObjID = 0;
	mTileManager = nullptr;
	mUILists.clear();
	mObjLists.clear();

	while (!mDeleteQueue.empty())
		mDeleteQueue.pop();
}

void ObjectManager::DeleteObject(OBJECT_ID _objID)
{
	mDeleteQueue.push(_objID);
}

void ObjectManager::Update(const float _deltaTime)
{
	// ť�� ��� ���ϰ� ���� ó���ع����� �̺�Ʈ ó�� ū��
	while (!mDeleteQueue.empty())
	{
		if (mObjLists.contains(mDeleteQueue.front()))
			mObjLists.erase(mDeleteQueue.front());

		mDeleteQueue.pop();
	}

	for (auto& obj : mObjLists)
	{
		obj.second->Update(_deltaTime);

		if (mTileManager != nullptr)
			mTileManager->ProcessCollision(*(obj.second));
	}

	for (auto& obj : mObjLists)
	{
		for (auto& targetObj : mObjLists)
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
	if (mTileManager != nullptr)
		mTileManager->Render();

	for (auto& obj : mObjLists)
		obj.second->Render();
}

void ObjectManager::SetTileManager(TileManager* _tileManager)
{
	mTileManager = _tileManager;
}
