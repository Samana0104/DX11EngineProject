#include "pch.h"
#include "Sound.h"
using namespace HBSoft;

Sound::Sound(const wstringV _filePath)
    : mSoundPath(_filePath)
{
#ifdef _DEBUG
    _ASSERT(CreateSound(_filePath));
#else
    CreateSound(_filePath);
#endif

    InitSound();
}

Sound::~Sound()
{
    if (mSound != nullptr)
    {
        Stop();
        mSound->release();
    }

    mSound = nullptr;
}

bool Sound::CreateSound(const wstringV _filePath)
{
    FMOD_RESULT hr =
    mFmodSys->createSound(CoreAPI::to_wm(_filePath).c_str(), FMOD_DEFAULT, 0, &mSound);

    if (hr == FMOD_OK)
        return true;
    else
        return false;
}

void Sound::InitSound()
{
    Stop();

    mSoundChannel = nullptr;
    // ZeroMemory(mSoundTimer, sizeof(wchar_t) * MAX_PATH);
    // mSoundSizeInMS = 0;
    mSoundVolume = 0.5f;
}

bool Sound::Play(bool _loop)
{
    FMOD_RESULT hr = mFmodSys->playSound(mSound, nullptr, false, &mSoundChannel);

    if (hr != FMOD_OK)
        return false;

    mSoundChannel->setVolume(mSoundVolume);
    // mSound->getLength(&mSoundSizeInMS, FMOD_TIMEUNIT_MS);
    //_stprintf_s(mSoundTimer,
    //	L"전체시간 [%02d:%02d:%02d]",
    //	mSoundSizeInMS / 1000 / 60,
    //	mSoundSizeInMS / 1000 % 60,
    //	mSoundSizeInMS / 10 / 60);

    if (_loop)
        mSoundChannel->setMode(FMOD_LOOP_NORMAL);
    else
        mSoundChannel->setMode(FMOD_LOOP_OFF);

    return true;
}

void Sound::Stop()
{
    if (IsPlaying())
        mSoundChannel->stop();
}

bool Sound::IsPlaying() const
{
    if (mSoundChannel == nullptr)
        return false;

    bool isPlaying;
    mSoundChannel->isPlaying(&isPlaying);

    return isPlaying;
}

void Sound::Paused()
{
    bool paused;
    if (IsPlaying())
    {
        mSoundChannel->getPaused(&paused);
        mSoundChannel->setPaused(!paused);
    }
}

void Sound::VolumeUp(float _volume)
{
    if (mSoundChannel == nullptr)
        return;

    mSoundVolume = glm::clamp(mSoundVolume + _volume, 0.f, 1.f);
    mSoundChannel->setVolume(mSoundVolume);
}

void Sound::VolumneDown(float _volume)
{
    if (mSoundChannel == nullptr)
        return;

    mSoundVolume = glm::clamp(mSoundVolume - _volume, 0.f, 1.f);
    mSoundChannel->setVolume(mSoundVolume);
}

void Sound::Update()
{
    if (!IsPlaying())
        return;

    mFmodSys->update();

    // unsigned int ms;
    // mSoundChannel->getPosition(&ms, FMOD_TIMEUNIT_MS);
    //_stprintf_s(mSoundTimer,
    //	L"전체시간[%02d:%02d:%02d]\n",
    //	ms / 1000 / 60,
    //	ms / 1000 % 60,
    //	ms / 10 / 60);
    ////OutputDebugString(m_msSound);
}
