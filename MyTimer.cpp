#include "MyTimer.h"
using namespace MyProject;

MyTimer::MyTimer(int _limitedMaxFPS)
	: mLimitedMaxFPS(mLimitedMaxFPS)
{
	MyTimer::InitComponent();
}

float MyTimer::GetDeltaTime() const
{
	return mSecondPerFrame;
}

bool MyTimer::HasPassedTime()
{
	if (mSecondTime >= 1.0f) // 1초가 지나면 초기화
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool MyTimer::HasPassedFrame() 
{
	if (mCurrentFPS >= mLimitedMaxFPS)
	{
		mCurrentFPS = 0;
		return true;
	}
	else
	{
		return false;
	}
}

void MyTimer::SetMaxFPS(int _fps)
{
	mLimitedMaxFPS = _fps;
}

int MyTimer::GetMaxFPS() const
{
	return mLimitedMaxFPS;
}

void MyTimer::InitComponent()
{
	mFPS = 0;
	mPreTimeTick = timeGetTime();
	mCurrentTimeTick = 0;
	mGameTimeTick = 0.0f;
	mCurrentFPS = 0;
	mCurrentMaxFPS = 0;
	mDeltaTime = 0.0f;
	mSecondTime = 0.0f;
	mSecondPerFrame = 0;
}

void MyTimer::UpdateComponent()
{
	mCurrentTimeTick = timeGetTime();
	mDeltaTime = mCurrentTimeTick - mPreTimeTick;
	mSecondPerFrame = (float)mDeltaTime / 1000.0f;
	mGameTimeTick += mSecondPerFrame;

	if (HasPassedTime())
	{
		mSecondTime = 0.f;
		mCurrentMaxFPS = mFPS;
		mFPS = 0;
	}
	else
	{
		mSecondTime += mSecondPerFrame;
		mFPS++;
	}

	mCurrentFPS += 1;
	mPreTimeTick = mCurrentTimeTick;
#ifdef _DEBUG
	TCHAR msgKey[MAX_PATH] = { 0, };
	_stprintf_s(msgKey,
		L"FPS=%ld, GameTimer=%10.4f SPF=%f\n",
		mCurrentMaxFPS, mGameTimeTick,
		mSecondPerFrame);
	m_csBuffer = msgKey;
#endif 
}

void MyTimer::RenderComponent()
{
}

void MyTimer::ReleaseComponent()
{
}
