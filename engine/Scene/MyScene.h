#pragma once
#include "MyCoreAPI.h"
#include "MyInput.h"
#include "MyResourceManger.h"
#include "MyObjectManager.h"

namespace MyProject
{
	class MySceneManager;

	class MyScene
	{
	protected:
		MySceneManager&	   mSceneManager;

		MyInput&		   mInput	   = MyInput::GetInstance();
		MyResourceManager& mManager	   = MyResourceManager::GetInstance();

		MyObjectManager	   mObjManager;

		//SCENE_KEY		mSceneID;
		// 필요하면 추가함 

	public:
		MyScene(MySceneManager& _sceneManager) : mSceneManager(_sceneManager) { }

		//const SCENE_KEY& GetSceneID() const { return mSceneID; }
		//void SetSceneID(SCENE_KEY _sceneID) { mSceneID = _sceneID;  }

		virtual void Init()    = 0;
		virtual void Render()  = 0;
		virtual void Release() = 0;
		virtual void Reset()   = 0;
		virtual void Start() = 0;
		virtual void End() = 0;
		virtual void Update(float _deltaTime) = 0;
	};
}

