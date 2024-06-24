#pragma once
#include "MySystemTimer.h"
#include "MyInput.h"
#include "MyWindow.h"
#include "MyShader.h"
#include "MyBox2D.h"
#include "MyResourceManger.h"
#include "MyActor.h"
#include "MyCamera.h"

namespace MyProject
{
	class MyCore : public MyCoreAPI
	{
	private:

	protected:
		MySystemTimer mTimer;

		static inline MyInput&  mInput = MyInput::GetInstance();
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

#ifdef _DEBUG
		void DrawTextForDebugging(const wchar_t* format, ...);
#endif

		static void INITIAL_SETUP(HINSTANCE _hinstance, LONG _width, LONG _height);
	};
}
