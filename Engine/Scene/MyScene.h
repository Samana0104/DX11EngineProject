#pragma once
#include "MyCoreAPI.h"

namespace MyProject
{
	class MyScene
	{
	public:
		virtual void Init() = 0;
		virtual void Update(float _deltaTime) = 0;
		virtual void Render() = 0;
		virtual void Release() = 0;
	};
}

