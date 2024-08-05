#pragma once
#include "MyActor.h"
#include "SpriteComponent.h"
#include "MySceneManager.h"

namespace MyProject
{
	class MyRuby : public MyActor
	{
	private:
		SpriteComponent mSprite;
		MySceneManager& mSceneManager;
		
		bool  mIsGameClear  = false;
		float mAngleForMove = 0.f;
		
	private:
		virtual void OnCollision(RECT_F& _self, RECT_F& _target, MyActor& _targetObj) override;

	public:
		MyRuby(MySceneManager& _sceneManager);

		void GameClear();

		virtual void Update(const float _deltaTime) override;
		virtual void Render() override;
	};
}

