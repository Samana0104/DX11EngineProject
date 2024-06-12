#pragma once
#include "Component.h"

namespace MyProject
{
	class MyWriterFont : public Component
	{
	private:
		ComPtr<ID2D1Factory>			mD2dFactory;
		ComPtr<ID2D1RenderTarget>		mD2dRT;
		ComPtr<IDWriteFactory>			mWriteFactory;
		ComPtr<IDWriteTextFormat>		mWriteFont;
		ComPtr<ID2D1SolidColorBrush>	mDefaultColor;

		std::wstring	mFontName;
		std::wstring	mFontLocalName;
		float			mFontSize;

		DWRITE_FONT_WEIGHT	 mFontWeight;
		DWRITE_FONT_STYLE	 mFontStyle;
		DWRITE_FONT_STRETCH	 mFontStretch;

	private:
		bool	CreateDevice();
		bool	CreateD2D1Factory();
		bool	CreateDWriteFactory();
		bool	CreateTextFormat();
		bool	CreateRenderTarget();
		bool	CreateBrush();

	public:
		MyWriterFont(
			const std::wstring _fontName, 
			const FLOAT _fontSize, 
			const std::wstring _localName = L"ko-kr",
			const DWRITE_FONT_WEIGHT _fontWeight = DWRITE_FONT_WEIGHT_THIN, 
			const DWRITE_FONT_STYLE _fontStyle = DWRITE_FONT_STYLE_NORMAL,
			const DWRITE_FONT_STRETCH _fontStrech = DWRITE_FONT_STRETCH_NORMAL);
		virtual ~MyWriterFont();

		void DrawTexts(const wstringV _msg, POINT_F _pos, COLOR_F _color) const;

		virtual void UpdateComponent() override;
		virtual void RenderComponent() override;
		virtual void ReleaseComponent() override;
	};
}
