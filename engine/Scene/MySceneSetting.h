#pragma once
#include "MySceneManager.h"

namespace MyProject
{
	class MySceneSetting : public MyScene
	{
	private:

	public:
		using MyScene::MyScene;

		virtual void Init() override;
		virtual void Update(float _deltaTime) override;
		virtual void Render() override;
		virtual void Release() override;
		virtual void Reset() override;
		virtual void Start() override;
		virtual void End() override;
	};
}


