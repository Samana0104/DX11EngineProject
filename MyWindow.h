#pragma once
#include <Windows.h>
#include <glm\glm.hpp>

namespace MyProject
{
	class MyWindow
	{
	private:
		static bool inline	mIsActivate = false;
		static POINT inline	mWindowSize = { 0, 0 };

		HINSTANCE	mHinstance;
		HWND		mHwnd;
		RECT		mWindowRect;
		RECT		mClientWindowRect;

	private:
		MyWindow() = default;
		MyWindow(const MyWindow&) = delete;
		MyWindow(MyWindow&&) = delete;
		MyWindow& operator=(const MyWindow&) = delete;
		MyWindow& operator=(MyWindow&&) = delete;

		void CreateRegisterClass(HINSTANCE _hInstance);

	public:
		const static int inline WINDOW_START_POS_X = 0;
		const static int inline WINDOW_START_POS_Y = 0;

	public:
		/* singleton */
		static MyWindow& GetInstance();

		bool	CreateWin(LONG _xSize, LONG _ySize);
		bool	WindowRun() const; 
		bool	IsActivate() const;

		void	SetHinstance(HINSTANCE _hinstance);

		POINT		GetWindowSize() const;
		POINTFLOAT	GetWindowSizeF() const;
		glm::vec2	GetWindowSizeVec2() const;

		HWND	GetWindowHandle() const;
	};

#define MY_WINDOW_NAME L"My Project"
#define MY_WINDOW_CLASS_NAME L"IS_REAL_WINDOW?"
#define CREATE_WINDOW(WIN_INSTANCE, WIDTH, HEIGHT) MyWindow::GetInstance().SetHinstance(WIN_INSTANCE);_ASSERT(MyWindow::GetInstance().CreateWin(WIDTH, HEIGHT));
}
