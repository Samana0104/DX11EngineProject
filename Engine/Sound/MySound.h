#pragma once
#include "MyCoreAPI.h"
#include "MyFmodSystem.h"

namespace MyProject
{
	class MySound
	{
	private:
		MyFmodSystem	mFmodSys;
		FMOD::Sound*	mSound;
		FMOD::Channel*	mSoundChannel;

		wchar_t			mSoundTimeStr[MAX_PATH];
		unsigned int	mSoundSizeInMS;

		float			mSoundVolume;

	private:
		bool CreateSound(wstringV _filePath);

	public:
		MySound(wstringV _filePath);
		~MySound();

		bool IsPlaying();
		bool Play(bool _loop);
		void Stop();
		void Paused();
		void VolumeUp(float _volume);
		void VolumneDown(float _volume);

		void Update();

		void InitSound();
	};
}