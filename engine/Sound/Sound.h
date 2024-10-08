#pragma once
#include "CoreAPI.h"
#include "MyFmodSystem.h"

namespace HBSoft
{
    class Sound
    {
    private:
        MyFmodSystem   mFmodSys;
        FMOD::Sound*   mSound;
        FMOD::Channel* mSoundChannel;

        std::wstring mSoundPath;
        float        mSoundVolume;

        // wchar_t			mSoundTimer[MAX_PATH];
        // unsigned int	mSoundSizeInMS;

    private:
        bool CreateSound(const wstringV _filePath);

    public:
        Sound(const wstringV _filePath);
        ~Sound();

        bool IsPlaying() const;
        bool Play(bool _loop = false);
        void Stop();
        void Paused();
        void VolumeUp(float _volume);
        void VolumneDown(float _volume);

        void Update();

        void InitSound();
    };
}  // namespace HBSoft