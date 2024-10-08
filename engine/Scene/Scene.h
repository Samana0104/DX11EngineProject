#pragma once
#include "CoreAPI.h"
#include "Input.h"
#include "MyResourceManger.h"
#include "ObjectManager.h"

namespace HBSoft
{
	class SceneManager;

	class Scene
	{
	protected:
		SceneManager&	   mSceneManager;

		Input&		   mInput	   = Input::GetInstance();
		MyResourceManager& mManager	   = MyResourceManager::GetInstance();

		ObjectManager	   mObjManager;

		//SCENE_KEY		mSceneID;
		// 필요하면 추가함 

	public:
		Scene(SceneManager& _sceneManager) : mSceneManager(_sceneManager) { }

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

