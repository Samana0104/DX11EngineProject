#pragma once
#include "MySystemTimer.h"
#include "MyInput.h"
#include "MyWindow.h"
#include "MyResourceManger.h"

namespace MyProject
{
	class MyCore : public MyCoreAPI
	{
	protected:
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
	protected:
		MyCore() = default;

		virtual void Init() = 0;
		virtual void Update(const float _delta) = 0;
		virtual void Render() = 0;
		virtual void Release() = 0;

	public:
		void GameRun();

		static void INITIAL_SETUP(HINSTANCE _hinstance, LONG _width, LONG _height);
	};
}
