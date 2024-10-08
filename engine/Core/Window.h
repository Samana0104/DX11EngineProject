#pragma once
#include "pch.h"

namespace HBSoft
{
#define MY_WINDOW_NAME L"My Project"
#define MY_WINDOW_CLASS_NAME L"IS_REAL_WINDOW?"

	using CALLBACK_ID = UINT;
	using WMSIZE_FUNC = std::function<void(UINT, UINT)>;

	class Window : public Singleton<Window>
	{
	private:
		inline static bool	m_isActivate = false;
		inline static POINT m_windowSize = { 0, 0 };

		CALLBACK_ID m_registerCallbackID = 0;
		std::map<CALLBACK_ID, WMSIZE_FUNC> m_callbackWMSize;

		HINSTANCE	m_hinstance;
		HWND		m_hwnd;

	private:
		friend class Singleton<Window>;
		Window() = default;

		void CreateRegisterClass(HINSTANCE hInstance);

		void CallEventWMActivate(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		void CallEventWMDestroy(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		void CallEventWMSize(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	public:
		bool	CreateWin(LONG width, LONG height);
		bool	WindowRun() const;
		bool	IsActivate() const;

		void	SetHinstance(HINSTANCE hinstance);

		POINT		GetWindowSize() const;
		POINTFLOAT	GetWindowSizeF() const;
		glm::vec2	GetWindowSizeVec2() const;
		HWND		GetWindowHandle() const;

		CALLBACK_ID	RegisterCallBackWMSize(WMSIZE_FUNC func);
		bool DeleteCallBack(CALLBACK_ID id);
	};
}
