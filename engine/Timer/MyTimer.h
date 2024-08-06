#pragma once
#include "MyCoreAPI.h"


namespace MyProject
{
	using namespace std::chrono;
	class MyTimer  
	{
	protected:
		time_point<steady_clock>	mStartTimeTick;
		time_point<steady_clock>	mCurrentTimeTick;
		duration<double>			mFrameDuration;
		duration<double>			mElapsedTime;
		duration<double>			mSecondPerFrame;

	public:
		float	GetElapsedTime() const;

		virtual float	GetDeltaTime() const;
		virtual void	Reset();
		virtual void	Start();
		void	Update();
	};
}