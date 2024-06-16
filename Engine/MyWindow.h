#pragma once
#include "pch.h"

namespace MyProject
{
	class MyWindow : public Singleton<MyWindow>
	{
	private:
		inline static bool	mIsActivate = false;
		inline static POINT mWindowSize = { 0, 0 };

		HINSTANCE	mHinstance;
		HWND		mHwnd;
		RECT		mWindowRect;
		RECT		mClientWindowRect;

	private:
		void CreateRegisterClass(HINSTANCE _hInstance);

	public:
		bool	CreateWin(LONG _width, LONG _height);
		bool	WindowRun() const; 
		bool	IsActivate() const;

		void	SetHinstance(HINSTANCE _hinstance);

		POINT		GetWindowSize() const;
		POINTFLOAT	GetWindowSizeF() const;
		glm::vec2	GetWindowSizeVec2() const;
		HWND		GetWindowHandle() const;

		void static CallEventWMActivate(HWND _hwnd, UINT _uMsg, WPARAM _wParam, LPARAM	_lParam);
		void static CallEventWMDestroy(HWND _hwnd, UINT _uMsg, WPARAM _wParam, LPARAM	_lParam);
		void static CallEventWMSize(HWND _hwnd, UINT _uMsg, WPARAM _wParam, LPARAM	_lParam);
	};

#define MY_WINDOW_NAME L"My Project"
#define MY_WINDOW_CLASS_NAME L"IS_REAL_WINDOW?"
}
