#pragma once
#include "Component.h"
#include "D3Device.h"

namespace MyProject
{
	class MyWriterFont : protected Component
	{
	private:
		ComPtr<ID2D1Factory>			mD2dFactory;
		ComPtr<ID2D1RenderTarget>		mD2dRT;
		ComPtr<IDWriteFactory>			mWriteFactory;
		ComPtr<IDWriteTextFormat>		mWriteFont;
		ComPtr<ID2D1SolidColorBrush>	mDefaultColor;

		std::wstring	mFontName;
		float			mFontSize;
		COLOR_F			mColor;

	private:
		bool	CreateDevice();
		bool	CreateD2D1Factory();
		bool	CreateDWriteFactory();
		bool	CreateTextFormat();
		bool	CreateRenderTarget();
		bool	CreateBrush();

	public:
		MyWriterFont(std::wstring _fontName, FLOAT _fontSize, COLOR_F _color);

		void DrawTexts(std::wstring msg, RECT_F	pos);

		virtual void InitComponent() override;
		virtual void UpdateComponent() override;
		virtual void RenderComponent() override;
		virtual void ReleaseComponent() override;
	};
}
