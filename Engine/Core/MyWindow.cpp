#include "pch.h"
#include "MyWindow.h"
using namespace MyProject;

void MyWindow::CreateRegisterClass(HINSTANCE _hInstance) 
{
	WNDCLASS wc = {};
	wc.lpfnWndProc = [](HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM	lParam) -> LRESULT
	{
		switch (uMsg)
		{
		case WM_ACTIVATE:
			MyWindow::GetInstance().CallEventWMActivate(hwnd, uMsg, wParam, lParam);
			return 0;

		case WM_DESTROY:
			MyWindow::GetInstance().CallEventWMDestroy(hwnd, uMsg, wParam, lParam);
			return 0;

		case WM_SIZE:
			MyWindow::GetInstance().CallEventWMSize(hwnd, uMsg, wParam, lParam);
			return 0;

		}
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	};

	wc.hInstance = _hInstance;
	wc.lpszClassName = MY_WINDOW_CLASS_NAME;
	RegisterClass(&wc);
}

bool MyWindow::CreateWin(LONG _width, LONG _height) 
{
	mWindowSize = { _width, _height };
	RECT rt{ 0, 0, _width, _height };

	CreateRegisterClass(mHinstance);
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, FALSE);

	HWND hwnd = CreateWindowEx(
		0, // Optional window styles.
		MY_WINDOW_CLASS_NAME,
		MY_WINDOW_NAME,
		WS_OVERLAPPEDWINDOW,// Window style
		GetSystemMetrics(SM_CXSCREEN) / 2 - (rt.right-rt.left) / 2, // 영역 중앙에 윈도우 생성
		GetSystemMetrics(SM_CYSCREEN) / 2 - (rt.bottom - rt.top) / 2, // 하단 영역 45px
		rt.right-rt.left, 
		rt.bottom-rt.top,
		NULL, // Parent window
		NULL, // Menu
		mHinstance, // Instance handle
		NULL // Additional application data
	);

	if (hwnd == NULL)
		return false;

	mHwnd = hwnd;
	ShowWindow(hwnd, SW_SHOW);

	return true;
}


bool MyWindow::WindowRun() const
{
	MSG msg = { };
	while (WM_QUIT != msg.message)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			return true;
		}
	}
	return false;
}

void MyWindow::CallEventWMActivate(HWND _hwnd, UINT _uMsg, WPARAM _wParam, LPARAM _lParam)
{
	if (LOWORD(_wParam) == WA_INACTIVE)
		MyWindow::mIsActivate = false;
	else
		MyWindow::mIsActivate = true;
}

void MyWindow::CallEventWMDestroy(HWND _hwnd, UINT _uMsg, WPARAM _wParam, LPARAM _lParam)
{
	PostQuitMessage(0);
}

void MyWindow::CallEventWMSize(HWND _hwnd, UINT _uMsg, WPARAM _wParam, LPARAM _lParam)
{
	RECT rc;

	GetClientRect(_hwnd, &rc);

	MyWindow::mWindowSize.x = rc.right;
	MyWindow::mWindowSize.y = rc.bottom;

	for (auto& obj : mCallbackWMSize)
		obj.second(MyWindow::mWindowSize.x, MyWindow::mWindowSize.y);
}

bool MyWindow::IsActivate() const
{
	return mIsActivate;
}

void MyWindow::SetHinstance(HINSTANCE _hinstance) 
{
	mHinstance = _hinstance;
}

POINT MyWindow::GetWindowSize() const
{
	return mWindowSize;
}

POINTFLOAT MyWindow::GetWindowSizeF() const
{
	return { static_cast<FLOAT>(mWindowSize.x), static_cast<FLOAT>(mWindowSize.y) };
}

glm::vec2 MyWindow::GetWindowSizeVec2() const
{
	return { static_cast<FLOAT>(mWindowSize.x), static_cast<FLOAT>(mWindowSize.y) };
}

HWND MyWindow::GetWindowHandle() const
{
	return mHwnd;
}

CALLBACK_ID MyWindow::RegisterCallBackWMSize(WMSIZE_FUNC _func)
{
	registerCallbackID++;
	mCallbackWMSize.insert(std::make_pair(registerCallbackID, _func));
	return registerCallbackID;
}

bool MyWindow::DeleteCallBack(CALLBACK_ID _id)
{
	if (mCallbackWMSize.contains(_id))
	{
		mCallbackWMSize.erase(_id);
		return true;
	}
	else
	{
		MessageBoxA(NULL, "Not existed event id[id Error]", "[WM Size event]", MB_OK);
		return false;
	}
}

