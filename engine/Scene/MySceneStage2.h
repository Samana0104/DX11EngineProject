#pragma once
#include "MyStageInterface.h"
#include "MyPlayer.h"
#include "MyRuby.h"
#include "MyWoodBox.h"
#include "MyKey.h"
#include "MyDoor.h"

namespace MyProject
{
	class MySceneStage2 : public MyStageInterface
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
