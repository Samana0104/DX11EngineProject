#include "pch.h"
#include "Sound.h"
using namespace HBSoft;

Sound::Sound(const wstringV _filePath)
    : m_soundPath(_filePath)
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
    if (m_sound != nullptr)
    {
        Stop();
        m_sound->release();
    }

    m_sound = nullptr;
}

bool Sound::CreateSound(const wstringV _filePath)
{
    FMOD_RESULT hr =
    m_fmodSys->createSound(HBSoft::ToMultiByte(_filePath).c_str(), FMOD_DEFAULT, 0, &m_sound);

    if (hr == FMOD_OK)
        return true;
    else
        return false;
}

void Sound::InitSound()
{
    Stop();

    m_soundChannel = nullptr;
    // ZeroMemory(m_soundTimer, sizeof(wchar_t) * MAX_PATH);
    // m_soundSizeInMS = 0;
    m_soundVolume = 0.5f;
}

bool Sound::Play(bool _loop)
{
    FMOD_RESULT hr = m_fmodSys->playSound(m_sound, nullptr, false, &m_soundChannel);

    if (hr != FMOD_OK)
        return false;

    m_soundChannel->setVolume(m_soundVolume);
    // m_sound->getLength(&m_soundSizeInMS, FMOD_TIMEUNIT_MS);
    //_stprintf_s(m_soundTimer,
    //	L"전체시간 [%02d:%02d:%02d]",
    //	m_soundSizeInMS / 1000 / 60,
    //	m_soundSizeInMS / 1000 % 60,
    //	m_soundSizeInMS / 10 / 60);

    if (_loop)
        m_soundChannel->setMode(FMOD_LOOP_NORMAL);
    else
        m_soundChannel->setMode(FMOD_LOOP_OFF);

    return true;
}

void Sound::Stop()
{
    if (IsPlaying())
        m_soundChannel->stop();
}

bool Sound::IsPlaying() const
{
    if (m_soundChannel == nullptr)
        return false;

    bool isPlaying;
    m_soundChannel->isPlaying(&isPlaying);

    return isPlaying;
}

void Sound::Paused()
{
    bool paused;
    if (IsPlaying())
    {
        m_soundChannel->getPaused(&paused);
        m_soundChannel->setPaused(!paused);
    }
}

void Sound::VolumeUp(float _volume)
{
    if (m_soundChannel == nullptr)
        return;

    m_soundVolume = glm::clamp(m_soundVolume + _volume, 0.f, 1.f);
    m_soundChannel->setVolume(m_soundVolume);
}

void Sound::VolumneDown(float _volume)
{
    if (m_soundChannel == nullptr)
        return;

    m_soundVolume = glm::clamp(m_soundVolume - _volume, 0.f, 1.f);
    m_soundChannel->setVolume(m_soundVolume);
}

void Sound::Update()
{
    if (!IsPlaying())
        return;

    m_fmodSys->update();

    // unsigned int ms;
    // m_soundChannel->getPosition(&ms, FMOD_TIMEUNIT_MS);
    //_stprintf_s(m_soundTimer,
    //	L"전체시간[%02d:%02d:%02d]\n",
    //	ms / 1000 / 60,
    //	ms / 1000 % 60,
    //	ms / 10 / 60);
    ////OutputDebugString(m_msSound);
}
