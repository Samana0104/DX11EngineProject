#pragma once
#include "MyCoreAPI.h"
#include "MyTransformer2D.h"

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

	class MyWriterFont
	{
	private:
		D3Device& mDevice = D3Device::GetInstance();

		ComPtr<IDWriteFactory>			mWriteFactory;
		ComPtr<IDWriteTextFormat>		mTextFormat;
		ComPtr<ID2D1SolidColorBrush>	mBrush;

		FontDesc		  mFontDesc;
		MyTransformer2D	  mTransform;
		D2D1_MATRIX_3X2_F mTempMat;
		CALLBACK_ID		  mWMSizeID;


	private:
		void	DrawBegin();
		void	DrawEnd();
		bool	CreateFontComponent();
		bool	CreateDWriteFactory();
		bool	CreateTextFormat();
		bool	CreateBrush();

		void	OnWMSize(UINT _weight, UINT _height);

	public:
		MyWriterFont(const FontDesc& _desc);
		~MyWriterFont();

		void DrawTexts(const wstringV _msg, RECT_F _rect, COLOR_F _color);
		const ComPtr<ID2D1SolidColorBrush>& GetBrush() const;

		void SetBold();
		bool isBold() const;

		float GetFontSize() const;
		vec2  GetTextSize(const wstringV _text) const;

		MyTransformer2D* operator->();
	};
}
