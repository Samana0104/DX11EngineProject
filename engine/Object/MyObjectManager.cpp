#include "pch.h"
#include "MyObjectManager.h"
using namespace MyProject;

void MyObjectManager::AddObject(std::unique_ptr<MyActor> _obj)
{
	registerObjID++;
	_obj->SetObjectID(registerObjID);
	mObjLists.insert(std::make_pair(registerObjID, std::move(_obj)));
}

void MyObjectManager::ClearObject()
{
	registerObjID = 0;
	mTileManager = nullptr;
	mUILists.clear();
	mObjLists.clear();

	while (!mDeleteQueue.empty())
		mDeleteQueue.pop();
}

void MyObjectManager::DeleteObject(OBJECT_ID _objID)
{
	mDeleteQueue.push(_objID);
}

void MyObjectManager::Update(const float _deltaTime)
{
	// 큐에 등록 안하고 삭제 처리해버리면 이벤트 처리 큰일
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

void MyObjectManager::Render()
{
	if (mTileManager != nullptr)
		mTileManager->Render();

	for (auto& obj : mObjLists)
		obj.second->Render();
}

void MyObjectManager::SetTileManager(MyTileManager* _tileManager)
{
	mTileManager = _tileManager;
}
