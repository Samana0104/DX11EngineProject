#include "pch.h"
#include "MyWriterFont.h"
using namespace MyProject;

MyWriterFont::MyWriterFont(
			const std::wstring _fontName, 
			const FLOAT _fontSize, 
			const std::wstring _localName, 
			const DWRITE_FONT_WEIGHT _fontWeight, 
			const DWRITE_FONT_STYLE _fontStyle,
			const DWRITE_FONT_STRETCH _fontStrech) 
	:	mFontName(_fontName),
		mFontSize(_fontSize),
		mFontLocalName(_localName),
		mFontWeight(_fontWeight),
		mFontStyle(_fontStyle),
		mFontStretch(_fontStrech)
{
	_ASSERT(CreateBrushComponent());
}

bool MyWriterFont::CreateBrushComponent()
{
	if (!CreateDWriteFactory())
		return false;
	
	if (!CreateBrush())
		return false;

	if (!CreateTextFormat())
		return false;

	return true;
}


bool MyWriterFont::CreateDWriteFactory()
{
	HRESULT hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED,__uuidof(IDWriteFactory),
		reinterpret_cast<IUnknown**>(mWriteFactory.GetAddressOf()));

	return !FAILED(hr);
}

bool MyWriterFont::CreateTextFormat()
{
	HRESULT hr = mWriteFactory->CreateTextFormat(
		mFontName.c_str(),
		nullptr,
		mFontWeight,
		mFontStyle,
		mFontStretch,
		mFontSize,
		mFontLocalName.c_str(),
		mWriteFont.GetAddressOf());

	return !FAILED(hr);
}

bool MyWriterFont::CreateBrush()
{
	COLOR_F color = { 1.f, 1.f, 1.f, 1.f };
	HRESULT hr = mDevice.mD2dRT->CreateSolidColorBrush(
		color,
		mDefaultColor.GetAddressOf());
	return !FAILED(hr);
}

void MyWriterFont::DrawTexts(const wstringV _msg, POINT_F _pos, COLOR_F _color) const
{
	RECT_F rc = { 
		_pos.x, 
		_pos.y, 
		MyWindow::GetInstance().GetWindowSizeF().x * 2,
		MyWindow::GetInstance().GetWindowSizeF().y * 2};

	mDevice.mD2dRT->BeginDraw();
	mDefaultColor->SetColor(_color);
	//mDevice.mD2dRT->DrawRectangle(rc, mDefaultColor.Get());
	//mDevice.mD2dRT->DrawText(_msg.data(), _msg.size(), mWriteFont.Get(),&rc, mDefaultColor.Get());
	//mDevice.mD2dRT->SetTransform(D2D1::Matrix3x2F::Rotation(-10.f));
	mDevice.mD2dRT->DrawText(_msg.data(), _msg.size(), mWriteFont.Get(),&rc, mDefaultColor.Get());
	mDevice.mD2dRT->EndDraw();
}

void MyWriterFont::UpdateComponent()
{
}

void MyWriterFont::RenderComponent()
{
}
