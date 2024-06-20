#pragma once
#include "Component.h"

namespace MyProject
{
	class MySound
	{
	private:
		const int MAX_CHANNELS = 32;
		std::shared_ptr<FMOD::System> mFmodSys;
	public:
	};
}