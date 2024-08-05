#pragma once
#include "MySceneManager.h"
#include "MyTileManager.h"
#include "MyTextButton.h"

namespace MyProject
{
	class MyStageInterface : public MyScene
	{
	protected:
		MyTileManager	   mTileMap;
		MyTextButton       mButtons[3];
		MyObject		   mPauseBackground;

		vec2 playerLocation = { 0.f, 0.f };
		int  mCurrentButton = 0;
		bool isPause	    = false;

	public:
		MyStageInterface(MySceneManager& _sceneManager) : MyScene(_sceneManager) { }

		virtual void Render() override;
		virtual void Release() override;
		virtual void Init() = 0;
		virtual void Reset() = 0;
		virtual void Start() = 0;
		virtual void End() = 0;
		virtual void Update(float _deltaTime) = 0;
	};
}

