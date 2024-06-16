#pragma once
#include "MyTimer.h"
#include "MyInput.h"
#include "MyWindow.h"
#include "MyShader.h"
#include "MyBox2D.h"
#include "MyResourceManger.h"

namespace MyProject
{
	class MyCore : public Component
	{
	private:
		MyShader			mShader;

	protected:
		MyTimer	mTimer;
		MyInput	mInput;

		static inline MyWindow& mWindow = MyWindow::GetInstance();
		static inline D3Device& mDevice = D3Device::GetInstance();
		static inline MyResourceManager& mManager = MyResourceManager::GetInstance();

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

		static void INITIAL_SETUP(HINSTANCE _hinstance, LONG _width, LONG _height);
	};
}
