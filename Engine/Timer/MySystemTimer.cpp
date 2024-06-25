#include "pch.h"
#include "MySystemTimer.h"
using namespace MyProject;

MySystemTimer::MySystemTimer(int _maxFPS)
{
	mMaxFPS = _maxFPS;
	mMaxFPSTime = 1.0 / _maxFPS;
	Reset();
}

bool MySystemTimer::CanExecuteFrame()
{
	if (mSecondPerMaxFPS <= mMaxFPSTime)
		return false;

	mDeltaTime = mSecondPerMaxFPS;
	mSecondPerMaxFPS = 0.;

#ifdef _DEBUG
	TCHAR msgKey[MAX_PATH] = { 0, };
	_stprintf_s(msgKey,
		L" FPS=%ld \n FPS=%ld \n %.10f \n GameTimer=%10.10f \n SPF=%10.10f\n",
		mCurrentFPS, mFPS, mDeltaTime, mElapsedTime.count(),
		mOneSecond);
	m_csBuffer = msgKey;
#endif

	return true;
}

bool MySystemTimer::HasPassedTime() 
{
	MyTimer::Update();
	mOneSecond += MyTimer::GetDeltaTime();
	mSecondPerMaxFPS += MyTimer::GetDeltaTime();

	if (!CanExecuteFrame()) // 프레임 제어를 위해 추가
		return false;

	mFPS++;
	if (mOneSecond >= 1.)
	{
		mOneSecond = 0.;
		mCurrentFPS = mFPS;
		mFPS = 0;
	}

	return true;
}

void MySystemTimer::SetMaxFPS(int _fps)
{
	mMaxFPSTime = 1.0/_fps;
	mMaxFPS = _fps;
}

int MySystemTimer::GetMaxFPS() const
{
	return mMaxFPS;
}

float MySystemTimer::GetDeltaTime() const
{
	return static_cast<float>(mDeltaTime);
}

void MySystemTimer::Reset()
{
    MyTimer::Reset();

	mDeltaTime = 0.0;
	mCurrentFPS = 0;
	mFPS = 0;
	mSecondPerMaxFPS = 0.0;
	mOneSecond = 0.0;
}

void MySystemTimer::Start()
{
	MyTimer::Start();
}
