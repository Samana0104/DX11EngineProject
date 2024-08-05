#pragma once
#include "MyStageInterface.h"
#include "MyPlayer.h"
#include "MyWoodBox.h"
#include "MyRuby.h"

namespace MyProject
{
	class MySceneStage3 : public MyStageInterface
	{
	public:
		using MyStageInterface::MyStageInterface;

		virtual void Init() override;
		virtual void Reset() override;
		virtual void Start() override;
		virtual void End() override;
		virtual void Update(float _deltaTime) override;
	};
}
