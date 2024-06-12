#pragma once
#include <memory>
#include <initializer_list>
#include <vector>
#include <string>
#include <map>
#include <list>
#include <algorithm>
#include <chrono>
#include <string_view>
#include <unordered_map>
#include <Windows.h>
#include <wrl.h>
#include <d3d11.h>
#include <d3dcompiler.h>
#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>
#include <tchar.h>
#include <glm/glm.hpp>
#include "directxtk/WICTextureLoader.h"
#include "Singleton.h"
#include "MyWindow.h"
#include "D3Device.h"

#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "DirectXTK.lib")

//#include "MyResourceManger.h"


using namespace Microsoft::WRL;
using namespace glm;

namespace MyProject
{
	using COLOR_F	= D2D1_COLOR_F;
	using RECT_L	= D2D1_RECT_L;
	using RECT_F	= D2D1_RECT_F;
	using RECT_U	= D2D1_RECT_U;
	using POINT_L	= D2D1_POINT_2L;
	using POINT_F	= D2D1_POINT_2F;
	using POINT_U	= D2D1_POINT_2U;

	using stringV	= std::string_view;
	using wstringV	= std::wstring_view;

	class Component
	{
	protected:
		static inline MyWindow& mWindow = MyWindow::GetInstance();
		static inline D3Device& mDevice = D3Device::GetInstance();
	protected:
		virtual void UpdateComponent() = 0;
		virtual void RenderComponent() = 0;
		virtual void ReleaseComponent() = 0;
	};
}