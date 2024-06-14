#include "pch.h"
#include "MyTimer.h"
using namespace MyProject;

MyTimer::MyTimer(int _maxFPS)
	: mElapsedTime(0)
{
	mMaxFPS = _maxFPS;
	mMaxFPSTime = 1. / static_cast<double>(_maxFPS);
	ResetTimer();
}

void MyTimer::ResetTimer()
{
	mStartTimeTick = steady_clock::now();
	mCurrentFPS = 0;
	mFPS = 0;
	mSecondPerMaxFPS = 0.f;
	mOneSecond = 0.f;
	mDeltaTime = 0.f;
}

void MyTimer::UpdateSPFAndElapsedTime()
{
	mCurrentTimeTick = steady_clock::now();
	mSecondPerFrame = duration_cast<duration<double>>(mCurrentTimeTick - mStartTimeTick) - mElapsedTime;
	mElapsedTime = mCurrentTimeTick - mStartTimeTick;
}

bool MyTimer::CanExecuteFrame()
{
	mSecondPerMaxFPS += mSecondPerFrame.count();

	if (mSecondPerMaxFPS >= mMaxFPSTime) 
	{
		mDeltaTime = mSecondPerMaxFPS;
		mSecondPerMaxFPS = 0.;
		return true;
	}

	return false;
}

bool MyTimer::HasPassedTime() 
{
	UpdateSPFAndElapsedTime();
	mOneSecond += mSecondPerFrame.count();

	if (CanExecuteFrame()) // 프레임 제어를 위해 추가
	{
		mFPS++;
		if (mOneSecond >= 1.)
		{
			mOneSecond = 0.;
			mCurrentFPS = mFPS;
			mFPS = 0;
		}
		return true;
	}
	return false;
}

void MyTimer::SetMasFPS(int _fps)
{
	mMaxFPSTime = 1.f/static_cast<double>(_fps);
	mMaxFPS = _fps;
}

float MyTimer::GetDeltaTime() const
{
	return static_cast<float>(mDeltaTime);
}

int MyTimer::GetMaxFPS() const
{
	return mMaxFPS;
}

float MyTimer::GetElapsedTime() const
{
	return static_cast<float>(mElapsedTime.count());
}

void MyTimer::UpdateComponent()
{
#ifdef _DEBUG
	TCHAR msgKey[MAX_PATH] = { 0, };
	_stprintf_s(msgKey,
		L" FPS=%ld \n FPS=%ld \n %.10f \n GameTimer=%10.10f \n SPF=%10.10f\n",
		mCurrentFPS, mFPS, mSecondPerFrame.count(), mElapsedTime.count(),
		mOneSecond);
	OutputDebugString(msgKey);
	m_csBuffer = msgKey;
#endif
}

void MyTimer::RenderComponent()
{
}
