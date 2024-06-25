#include "pch.h"
#include "MyTimer.h"
using namespace MyProject;

float MyTimer::GetElapsedTime() const
{
	return static_cast<float>(mElapsedTime.count());
}

float MyTimer::GetDeltaTime() const
{
	return static_cast<float>(mSecondPerFrame.count());
}

void MyTimer::Reset()
{
	mStartTimeTick = steady_clock::now();
    mElapsedTime = duration<double>(0);
    mFrameDuration = duration<double>(0);
    mSecondPerFrame = duration<double>(0);
}

void MyTimer::Start()
{
	Reset();
}

void MyTimer::Update()
{
	mCurrentTimeTick = steady_clock::now();
	mFrameDuration = mCurrentTimeTick - mStartTimeTick;
	mSecondPerFrame = mFrameDuration - mElapsedTime;
	mElapsedTime = mFrameDuration;
}

