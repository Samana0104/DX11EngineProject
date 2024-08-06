#pragma once
#include "pch.h"

namespace MyProject
{
#define MY_WINDOW_NAME L"My Project"
#define MY_WINDOW_CLASS_NAME L"IS_REAL_WINDOW?"

	using CALLBACK_ID = UINT;
	using WMSIZE_FUNC = std::function<void(UINT, UINT)>;

	class MyWindow : public Singleton<MyWindow>
	{
	private:
		inline static bool	mIsActivate = false;
		inline static POINT mWindowSize = { 0, 0 };

		CALLBACK_ID registerCallbackID = 0;
		std::map<CALLBACK_ID, WMSIZE_FUNC> mCallbackWMSize;

		HINSTANCE	mHinstance;
		HWND		mHwnd;

	private:	
		friend class Singleton<MyWindow>;
		MyWindow() = default;

		void CreateRegisterClass(HINSTANCE _hInstance);

		void CallEventWMActivate(HWND _hwnd, UINT _uMsg, WPARAM _wParam, LPARAM	_lParam);
		void CallEventWMDestroy(HWND _hwnd, UINT _uMsg, WPARAM _wParam, LPARAM	_lParam);
		void CallEventWMSize(HWND _hwnd, UINT _uMsg, WPARAM _wParam, LPARAM	_lParam);

	public:
		bool	CreateWin(LONG _width, LONG _height);
		bool	WindowRun() const; 
		bool	IsActivate() const;

		void	SetHinstance(HINSTANCE _hinstance);

		POINT		GetWindowSize() const;
		POINTFLOAT	GetWindowSizeF() const;
		glm::vec2	GetWindowSizeVec2() const;
		HWND		GetWindowHandle() const;

		CALLBACK_ID	RegisterCallBackWMSize(WMSIZE_FUNC _func);
		bool DeleteCallBack(CALLBACK_ID _id);
	};
}
