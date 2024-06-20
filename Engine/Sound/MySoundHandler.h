#pragma once
#include "ResourceHandler.h"
#include "MySound.h"

namespace MyProject
{
	class MySoundHandler : public ResourceHandler<MySound, SOUND_KEY>
	{
	private:
		const int MAX_CHANNELS = 32;
		std::unique_ptr<FMOD::System> mFmodSys;

	public:
		MySoundHandler();

		bool CreateFmodSystem();
		
		virtual ~MySoundHandler();
	};
}