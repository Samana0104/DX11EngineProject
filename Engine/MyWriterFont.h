#pragma once
#include "Component.h"

namespace MyProject
{
	struct FontDesc
	{
		std::wstring mFontName;
		std::wstring mFontLocalName;
		FLOAT		 mFontSize;

		DWRITE_FONT_WEIGHT	mFontWeight;
		DWRITE_FONT_STYLE	mFontStyle;
		DWRITE_FONT_STRETCH mFontStretch;
	};

	class MyWriterFont : public Component
	{
	private:
		inline static D3Device& mDevice = D3Device::GetInstance();

		ComPtr<IDWriteFactory>			mWriteFactory;
		ComPtr<IDWriteTextFormat>		mWriteFont;
		ComPtr<ID2D1SolidColorBrush>	mDefaultColor;

		FontDesc mFontDesc;

	private:
		bool	CreateBrushComponent();
		bool	CreateDWriteFactory();
		bool	CreateTextFormat();
		bool	CreateBrush();

	public:
		MyWriterFont(const FontDesc& _desc);

		void DrawTexts(const wstringV _msg, POINT_F _pos, COLOR_F _color) const;

		virtual void UpdateComponent() override;
		virtual void RenderComponent() override;
	};
}
