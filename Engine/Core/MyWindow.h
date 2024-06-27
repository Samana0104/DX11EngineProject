#pragma once
#include "pch.h"

namespace MyProject
{
#define MY_WINDOW_NAME L"My Project"
#define MY_WINDOW_CLASS_NAME L"IS_REAL_WINDOW?"

	using CALLBACK_WMSIZE_TYPE = std::list<std::pair<void*, std::function<void(UINT, UINT)>>>;

	class MyWindow : public Singleton<MyWindow>
	{
	private:
		inline static bool	mIsActivate = false;
		inline static POINT mWindowSize = { 0, 0 };

		inline static CALLBACK_WMSIZE_TYPE mCallbackWMSize;

		HINSTANCE	mHinstance;
		HWND		mHwnd;

	private:	
		friend class Singleton<MyWindow>;
		MyWindow() = default;

		void CreateRegisterClass(HINSTANCE _hInstance);

		void static CallEventWMActivate(HWND _hwnd, UINT _uMsg, WPARAM _wParam, LPARAM	_lParam);
		void static CallEventWMDestroy(HWND _hwnd, UINT _uMsg, WPARAM _wParam, LPARAM	_lParam);
		void static CallEventWMSize(HWND _hwnd, UINT _uMsg, WPARAM _wParam, LPARAM	_lParam);

	public:
		bool	CreateWin(LONG _width, LONG _height);
		bool	WindowRun() const; 
		bool	IsActivate() const;

		void	SetHinstance(HINSTANCE _hinstance);

		POINT		GetWindowSize() const;
		POINTFLOAT	GetWindowSizeF() const;
		glm::vec2	GetWindowSizeVec2() const;
		HWND		GetWindowHandle() const;

		template <typename T>
		void	RegisterCallBackWMSize(T* obj, void(T::* func)(UINT, UINT));
		template <typename T>
		void	DeleteCallBack(T* obj);
	};

	template<typename T>
	inline void MyWindow::RegisterCallBackWMSize(T* obj, void(T::* func)(UINT, UINT))
	{
		mCallbackWMSize.push_back(std::make_pair(
			reinterpret_cast<void*>(obj), 
			[obj, func](UINT width, UINT height) 
			{
			(obj->*func)(width, height);
			}
		));
	}

	template<typename T>
	inline void MyWindow::DeleteCallBack(T* obj)
	{
		auto iter = std::find_if(mCallbackWMSize.begin, mCallbackWMSize.end(),
			[obj](std::pair<void*, std::function<void(UINT, UINT)>> & _value)
			{
				return _value.first == reinterpret_cast<void*>(obj);
			}
		);

		mCallbackWMSize.erase(iter);
	}
}
