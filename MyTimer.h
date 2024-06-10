#pragma once
#include "Component.h"

namespace MyProject
{
	class MyTimer : protected Component
	{
	private:
		float	mGameTimeTick;
		float   mDeltaTime;
		float	mSecondTime;
		float   mSecondPerFrame;
		DWORD	mPreTimeTick;
		DWORD	mCurrentTimeTick;

		int mCurrentFPS;
		int	mFPS;
		int	mLimitedMaxFPS;
		int mCurrentMaxFPS;

	private:

	public:
		MyTimer(int _limitedMaxFPS = 60);
		std::wstring   m_csBuffer;


		float	GetDeltaTime() const;
		bool	HasPassedTime();
		bool	HasPassedFrame();
		void	SetMaxFPS(int _fps);
		int		GetMaxFPS()	const;

		virtual void InitComponent() override;
		virtual void UpdateComponent() override;
		virtual void RenderComponent() override;
		virtual void ReleaseComponent() override;
	};
}