#pragma once
#include "MySceneManager.h"
#include "MyInput.h"
#include "TestObj.h"
#include "MyCamera.h"
#include "MyButton.h"

namespace MyProject
{
	class MySceneLobby : public MyScene
	{
	private:
		MyButton mButton;
		POINT_F myPos;
		TestObj mObject;
		TestObj mObject2;
		MyCamera mCamera;

	public:
		using MyScene::MyScene;

		virtual void Init() override;
		virtual void Update(float _deltaTime) override;
		virtual void Render() override;
		virtual void Release() override;
		virtual void Reset() override;
		virtual void Execute() override;
	};
}

