#pragma once
#include "Component.h"

using namespace std::chrono;

namespace MyProject
{
	class MyTimer : public Component
	{
	private:
		time_point<steady_clock>	mPreTimeTick;
		time_point<steady_clock>	mCurrentTimeTick;
		duration<float, std::milli>	mTickToMilli;

		float	mSecondPerFrame;
		float	mOneSecond;
		float	mSecondTime;
		float	mGameTimeTick;
		float	mDeltaTime;

		float	mMaxFPSTime;
		int		mMaxFPS;
		int		mFPS;
		int		mCurrentFPS;

	public:
		std::wstring   m_csBuffer;

	public:
		MyTimer(int _maxFPS = 100);
		~MyTimer();

		void	InitTimer();

		float	GetDeltaTime() const;
		bool	HasPassedTime();

		void	SetMasFPS(int _fps);
		int		GetMaxFPS()	const;

		virtual void UpdateComponent() override;
		virtual void RenderComponent() override;
		virtual void ReleaseComponent() override;
	};
}