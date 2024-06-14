#pragma once
#include "D3Device.h"


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
	};
}