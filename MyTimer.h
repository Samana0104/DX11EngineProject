#pragma once
#include "Component.h"

using namespace std::chrono;

namespace MyProject
{
	class MyTimer : public Component
	{
	private:
		time_point<steady_clock>	mStartTimeTick;
		time_point<steady_clock>	mCurrentTimeTick;
		duration<double>			mElapsedTime;
		duration<double>			mSecondPerFrame;

		double	mOneSecond;
		double	mSecondTime;
		double	mDeltaTime;
		double	mMaxFPSTime;

		int		mMaxFPS;
		int		mFPS;
		int		mCurrentFPS;

	public:
		std::wstring   m_csBuffer;

	public:
		MyTimer(int _maxFPS = 120);
		~MyTimer();

		void	InitTimer();

		float	GetDeltaTime() const;
		float	GetElapsedTime() const;
		int		GetMaxFPS()	const;

		bool	HasPassedTime();

		void	SetMasFPS(int _fps);

		virtual void UpdateComponent() override;
		virtual void RenderComponent() override;
		virtual void ReleaseComponent() override;
	};
}