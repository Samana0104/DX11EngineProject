#pragma once
#include "MyTimer.h"
#include "MyInput.h"
#include "MyWindow.h"
#include "MyShader.h"
#include "Box2D.h"
#include "MyResourceManger.h"

namespace MyProject
{
	class MyCore : public Component
	{
	private:
		MyResourceManager	mSrcManager;
		MyShader			mShader;

	protected:
		MyTimer	mTimer;
		MyInput	mInput;
		MyFontHandler	mFont;

	public:
		static inline MyWindow& mWindow = MyWindow::GetInstance();
		static inline D3Device& mDevice = D3Device::GetInstance();

	private:
		MyCore(const MyCore&) = delete;
		void operator=(const MyCore&) = delete;

		void	GamePreFrame();
		void	GameFrame();
		void	GamePostFrame();
		void	GamePreRender();
		void	GameRender();
		void	GamePostRender();
		void	GameInit();
		void	GameRelease();
	protected:
		MyCore() = default;

		virtual void InitComponent() = 0;
		virtual void UpdateComponent() override = 0;
		virtual void RenderComponent() override = 0;
		virtual void ReleaseComponent() = 0;

	public:
		void GameRun();
		void DrawTextForDebugging(const wchar_t* format, ...);
	};
}
