#pragma once
#include "MyStageInterface.h"
#include "MyWoodBox.h"
#include "MyPlayer.h"
#include "MyRuby.h"

namespace MyProject
{
	class MySceneStage1 : public MyStageInterface
	{
	private:

	public:
		using MyStageInterface::MyStageInterface;

		virtual void Init() override;
		virtual void Reset() override;
		virtual void Start() override;
		virtual void End() override;
		virtual void Update(float _deltaTime) override;
	};
}

