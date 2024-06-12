#include "MyTimer.h"
using namespace MyProject;

MyTimer::MyTimer(int _maxFPS)
	: mElapsedTime(0)
{
	mMaxFPS = _maxFPS;
	mMaxFPSTime = 1. / static_cast<double>(_maxFPS);
	InitTimer();
}

MyTimer::~MyTimer()
{
	MyTimer::ReleaseComponent();
}

void MyTimer::InitTimer()
{
	mStartTimeTick = steady_clock::now();
	mCurrentFPS = 0;
	mFPS = 0;
	mSecondTime = 0.f;
	mOneSecond = 0.f;
	mDeltaTime = 0.f;
	//mElapsedTime = 0.f;
	//mSecondPerFrame = 0.f;
}

bool MyTimer::HasPassedTime() 
{
	mCurrentTimeTick = steady_clock::now();
	mSecondPerFrame = duration_cast<duration<double>>(mCurrentTimeTick - mStartTimeTick) - mElapsedTime;
	mElapsedTime = mCurrentTimeTick - mStartTimeTick;
	mSecondTime += mSecondPerFrame.count();
	mOneSecond += mSecondPerFrame.count();

	if (mSecondTime >= mMaxFPSTime) // SecondTime이 FPSTime을 경과했을 때 
	{
		mDeltaTime = mSecondTime;
		mSecondTime = 0.;
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
		L"FPS %ld, FPS=%ld, %.10f GameTimer=%10.10f SPF=%10.10f\n",
		mCurrentFPS, mFPS, mSecondPerFrame.count(), mElapsedTime.count(),
		mOneSecond);
	OutputDebugString(msgKey);
	m_csBuffer = msgKey;
#endif
}

void MyTimer::RenderComponent()
{
}

void MyTimer::ReleaseComponent()
{
}
