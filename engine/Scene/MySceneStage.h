#pragma once
#include "MySceneManager.h"
#include "MyObject.h"
#include "MyImageButton.h"

namespace MyProject
{
	class MySceneStage : public MyScene
	{
	private:
		int mCurrentButton;
		MyObject mBackground;
		MyObject mBackground2;
		MyImageButton mButtons[4];
	
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
