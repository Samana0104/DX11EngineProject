#pragma once
#include "MyActor.h"
#include "MyTileManager.h"

namespace MyProject
{
	class MyObjectManager
	{
	private:
		std::map<OBJECT_ID, std::unique_ptr<MyObject>> mUILists; // 추후에 사용 예정?
		std::map<OBJECT_ID, std::unique_ptr<MyActor>>  mObjLists;
		
		std::queue<OBJECT_ID> mDeleteQueue;

		MyTileManager* mTileManager = nullptr; // 타일 매니저 따로 안두면 너무 많은 조건 검사 함
		OBJECT_ID registerObjID = 0;

	public:
		MyObjectManager() = default;
		
		void AddObject(std::unique_ptr<MyActor> _obj);
		void SetTileManager(MyTileManager* _tileManager);

		void DeleteObject(OBJECT_ID _objID);
		void ClearObject();

		void Update(const float _deltaTime);
		void Render();
	};
}

