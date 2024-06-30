#pragma once
#include "MySystemTimer.h"
#include "MyInput.h"
#include "MyWindow.h"
#include "MyResourceManger.h"
#include "MySceneManager.h"

namespace MyProject
{
	class MyCore : public MyCoreAPI
	{
	protected:
		MySceneManager mSceneManager;
		MySystemTimer mTimer;

		MyInput&			mInput = MyInput::GetInstance();
		MyWindow&			mWindow = MyWindow::GetInstance();
		D3Device&			mDevice = D3Device::GetInstance();
		MyResourceManager&	mManager = MyResourceManager::GetInstance();

	private:
		MyCore(const MyCore&) = delete;
		void operator=(const MyCore&) = delete;

		void	GameFrame();
		void	GamePreRender();
		void	GameRender();
		void	GamePostRender();
		void	GameInit();
		void	GameRelease();

	public:
		MyCore() = default;
		void GameRun();

		static void ENGINE_BEGIN(HINSTANCE _hinstance, LONG _width, LONG _height);
		static void ENGINE_END();
	};
}
