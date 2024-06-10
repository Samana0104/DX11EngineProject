#include "MyWindow.h"
using namespace MyProject;

MyWindow& MyWindow::GetInstance()
{
	static MyWindow _myWindow;
	return _myWindow;
}

void MyWindow::CreateRegisterClass(HINSTANCE _hInstance) 
{
	WNDCLASS wc = {};
	wc.lpfnWndProc = [](HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM	lParam) -> LRESULT
	{
		switch (uMsg)
		{
		case WM_ACTIVATE:
			if (LOWORD(wParam) == WA_INACTIVE)
				MyWindow::mIsActivate = false;
			else
				MyWindow::mIsActivate = true;
			return 0;

		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;

		case WM_SIZE:
			//MyWindow::mWindowSize.x = LOWORD(lParam);
			//MyWindow::mWindowSize.y = HIWORD(lParam);
			return 0;
		}
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	};
	wc.hInstance = _hInstance;
	wc.lpszClassName = MY_WINDOW_CLASS_NAME;
	RegisterClass(&wc);
}

bool MyWindow::CreateWin(LONG _xSize, LONG _ySize) 
{
	mWindowSize = { _xSize, _ySize };
	RECT rt{ 0, 0, _xSize, _ySize };
	DWORD windowStyle = WS_OVERLAPPEDWINDOW;
	CreateRegisterClass(mHinstance);

	AdjustWindowRect(&rt, windowStyle, FALSE);

	HWND hwnd = CreateWindowEx(
		0, // Optional window styles.
		MY_WINDOW_CLASS_NAME,
		MY_WINDOW_NAME,
		windowStyle,// Window style
		// Size and position
		WINDOW_START_POS_X, WINDOW_START_POS_Y,
		rt.right-rt.left, rt.bottom-rt.top,
		NULL, // Parent window
		NULL, // Menu
		mHinstance, // Instance handle
		NULL // Additional application data
	);

	if (hwnd == NULL)
		return false;

	GetWindowRect(hwnd, &mWindowRect);
	GetClientRect(hwnd, &mClientWindowRect);

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

