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
		double	mDeltaTime;
		double	mMaxFPSTime;
		double	mSecondPerMaxFPS;

		int		mMaxFPS;
		int		mFPS;
		int		mCurrentFPS;

	private:
		void UpdateSPFAndElapsedTime();
		bool CanExecuteFrame();

	public:
		std::wstring   m_csBuffer;

	public:
		MyTimer(int _maxFPS = 120);

		void	ResetTimer();

		void	SetMasFPS(int _fps);
		int		GetMaxFPS()	const;
		float	GetDeltaTime() const;
		float	GetElapsedTime() const;

		bool	HasPassedTime();


		virtual void UpdateComponent() override;
		virtual void RenderComponent() override;
	};
}