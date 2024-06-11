#include "MyTimer.h"
using namespace MyProject;


MyTimer::MyTimer(int _maxFPS)
{
	mMaxFPS = _maxFPS;
	mMaxFPSTime = 1.f / static_cast<float>(_maxFPS);
}

MyTimer::~MyTimer()
{
	MyTimer::ReleaseComponent();
}

void MyTimer::InitTimer()
{
	mPreTimeTick = steady_clock::now();
	mCurrentFPS = 0;
	mFPS = 0;
	mSecondTime = 0.f;
	mOneSecond = 0.f;
	mDeltaTime = 0.f;
	mSecondPerFrame = 0.f;
	mGameTimeTick = 0.f;
}

float MyTimer::GetDeltaTime() const
{
	return mDeltaTime;
}

// 컴퓨터가 대기 상태일 때 이전 틱과의 엄청난 차이를 보일 때가 있음 
bool MyTimer::HasPassedTime() 
{
	mCurrentTimeTick = steady_clock::now();
	mTickToMilli = mCurrentTimeTick - mPreTimeTick;
	mSecondPerFrame = mTickToMilli.count() / 1000.f;
	mGameTimeTick += mSecondPerFrame;
	mOneSecond += mSecondPerFrame;
	mSecondTime += mSecondPerFrame;
	mPreTimeTick = mCurrentTimeTick;

	if (mSecondTime >= mMaxFPSTime) 
	{
		mDeltaTime = mSecondTime;
		mSecondTime = 0.f;
		mFPS++;

		if (mOneSecond >= 1.f)
		{
			mOneSecond = 0.f;
			mCurrentFPS = mFPS;
			mFPS = 0;
		}
		return true;
	}
	return false;
}

void MyTimer::SetMasFPS(int _fps)
{
	mMaxFPSTime = 1.f/static_cast<float>(_fps);
	mMaxFPS = _fps;
}

int MyTimer::GetMaxFPS() const
{
	return mMaxFPS;
}

void MyTimer::UpdateComponent()
{
#ifdef _DEBUG
	TCHAR msgKey[MAX_PATH] = { 0, };
	_stprintf_s(msgKey,
		L"FPS=%ld, FPS=%d GameTimer=%10.4lf DeltaTime=%lf \n",
		mCurrentFPS, 
		mFPS,
		mGameTimeTick,
		mDeltaTime );
	m_csBuffer = msgKey;
#endif	
}

void MyTimer::RenderComponent()
{
}

void MyTimer::ReleaseComponent()
{
}
