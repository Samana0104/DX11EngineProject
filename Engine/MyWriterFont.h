#pragma once
#include "Component.h"

namespace MyProject
{
	class MyWriterFont : public Component
	{
	private:
		inline static D3Device& mDevice = D3Device::GetInstance();

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
		bool	CreateBrushComponent();
		bool	CreateDWriteFactory();
		bool	CreateTextFormat();
		bool	CreateBrush();

	public:
		MyWriterFont(
			const std::wstring _fontName, 
			const FLOAT _fontSize, 
			const std::wstring _localName = L"ko-kr",
			const DWRITE_FONT_WEIGHT _fontWeight = DWRITE_FONT_WEIGHT_THIN, 
			const DWRITE_FONT_STYLE _fontStyle = DWRITE_FONT_STYLE_NORMAL,
			const DWRITE_FONT_STRETCH _fontStrech = DWRITE_FONT_STRETCH_NORMAL);

		void DrawTexts(const wstringV _msg, POINT_F _pos, COLOR_F _color) const;

		virtual void UpdateComponent() override;
		virtual void RenderComponent() override;
	};
}
