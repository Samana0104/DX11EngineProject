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

		std::wstring	mSoundPath;
		wchar_t			mSoundTimer[MAX_PATH];
		unsigned int	mSoundSizeInMS;

		float			mSoundVolume;

	private:
		bool CreateSound(const wstringV _filePath);

	public:
		MySound(const wstringV _filePath);
		~MySound();

		bool IsPlaying() const;
		bool Play(bool _loop = false);
		void Stop();
		void Paused();
		void VolumeUp(float _volume);
		void VolumneDown(float _volume);

		void Update();

		void InitSound();
	};
}