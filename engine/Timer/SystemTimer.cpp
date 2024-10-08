#include "pch.h"
#include "SystemTimer.h"
using namespace HBSoft;

SystemTimer::SystemTimer(int _maxFPS)
{
	mMaxFPS = _maxFPS;
	mMaxFPSTime = 1.0 / _maxFPS;
	Reset();
}

bool SystemTimer::CanExecuteFrame()
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

bool SystemTimer::HasPassedTime() 
{
	Timer::Update();
	mOneSecond += Timer::GetDeltaTime();
	mSecondPerMaxFPS += Timer::GetDeltaTime();

	if (!CanExecuteFrame()) // ������ ��� ���� �߰�
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

void SystemTimer::SetMaxFPS(int _fps)
{
	mMaxFPSTime = 1.0/_fps;
	mMaxFPS = _fps;
}

int SystemTimer::GetMaxFPS() const
{
	return mMaxFPS;
}

float SystemTimer::GetDeltaTime() const
{
	// ����� ���� ����� ���� �ʹ� Ŭ ���� ������
	if (mDeltaTime >= mMaxFPSTime*2)
		return static_cast<float>(mMaxFPSTime);
	else
		return static_cast<float>(mDeltaTime);
}

void SystemTimer::Reset()
{
    Timer::Reset();

	mDeltaTime = 0.0;
	mCurrentFPS = 0;
	mFPS = 0;
	mSecondPerMaxFPS = 0.0;
	mOneSecond = 0.0;
}

void SystemTimer::Start()
{
	Timer::Start();
}
