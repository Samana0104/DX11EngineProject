#pragma once
#include "MyCoreAPI.h"


namespace MyProject
{
	using namespace std::chrono;
	class MyTimer : public MyCoreAPI
	{
	private:
		time_point<steady_clock>	mStartTimeTick;
		time_point<steady_clock>	mCurrentTimeTick;
		duration<double>			mFrameDuration;
		duration<double>			mElapsedTime;
		duration<double>			mSecondPerFrame;

		double	mOneSecond;
		double	mDeltaTime;
		double	mMaxFPSTime;
		double	mSecondPerMaxFPS;

		int		mMaxFPS;
		int		mFPS;
		int		mCurrentFPS;

	public:
		std::wstring   m_csBuffer;

	private:
		void UpdateSPFAndElapsedTime();
		bool CanExecuteFrame();

	public:
		MyTimer(int _maxFPS = 120);

		void	Reset();

		void	SetMaxFPS(int _fps);

		int		GetMaxFPS()	const;
		float	GetDeltaTime() const;
		float	GetElapsedTime() const;

		bool	HasPassedTime();

		virtual void UpdateComponent() override;
		virtual void RenderComponent() override;
	};
}