#include "pch.h"
#include "MySound.h"
using namespace MyProject;

MySound::MySound(wstringV _filePath)
{
	_ASSERT(CreateSound(_filePath));
	InitSound();
}

MySound::~MySound()
{
	if (mSound != nullptr)
	{
		Stop();
		mSound->release();
	}

	mSound = nullptr;
}

bool MySound::CreateSound(wstringV _filePath)
{
	FMOD_RESULT hr = mFmodSys->createSound(
		MyCoreAPI::to_wm(_filePath).c_str(),
		FMOD_DEFAULT,
		0,
		&mSound );

	if (hr == FMOD_OK)
		return true;
	else
		return false;
}

void MySound::InitSound()
{
	Stop();

	ZeroMemory(mSoundTimeStr, sizeof(wchar_t) * MAX_PATH);
	mSoundChannel = nullptr;
	mSoundSizeInMS = 0;
	mSoundVolume = 0.5f;
}

bool MySound::Play(bool _loop)
{
	FMOD_RESULT hr = mFmodSys->playSound(mSound, nullptr, false, &mSoundChannel);

	if (hr != FMOD_OK)
		return false;

	mSoundChannel->setVolume(mSoundVolume);
	mSound->getLength(&mSoundSizeInMS, FMOD_TIMEUNIT_MS);
	_stprintf_s(mSoundTimeStr,
		L"전체시간 [%02d:%02d:%02d]",
		mSoundSizeInMS / 1000 / 60,
		mSoundSizeInMS / 1000 % 60,
		mSoundSizeInMS / 10 / 60);

	if (_loop)
		mSoundChannel->setMode(FMOD_LOOP_NORMAL);
	else
		mSoundChannel->setMode(FMOD_LOOP_OFF);

	return true;
}

void MySound::Stop()
{
	if (IsPlaying())
		mSoundChannel->stop();
}

bool MySound::IsPlaying()
{
	if (mSoundChannel == nullptr)
		return false;

	bool isPlaying;
	mSoundChannel->isPlaying(&isPlaying);

	return isPlaying;
}

void MySound::Paused()
{
	bool paused;
	if (IsPlaying())
	{
		mSoundChannel->getPaused(&paused);
		mSoundChannel->setPaused(!paused);
	}
}

void MySound::VolumeUp(float _volumne)
{
	if (mSoundChannel == nullptr) 
		return;

	float setUpVolume = glm::clamp(_volumne + mSoundVolume, 0.f, 1.f);
	mSoundChannel->setVolume(setUpVolume);
}

void MySound::VolumneDown(float _volume)
{
	if (mSoundChannel == nullptr) 
		return;

	float setUpVolume = glm::clamp(_volume + mSoundVolume, 0.f, 1.f);
	mSoundChannel->setVolume(setUpVolume);
}

void MySound::Update()
{
	if (mSoundChannel == nullptr) 
		return;

	unsigned int ms;
	mSoundChannel->getPosition(&ms, FMOD_TIMEUNIT_MS);
	_stprintf_s(mSoundTimeStr,
		L"전체시간[%02d:%02d:%02d]\n",
		ms / 1000 / 60,
		ms / 1000 % 60,
		ms / 10 / 60);
	//OutputDebugString(m_msSound);
}

