#include "pch.h"
#include "MyWriterFont.h"
using namespace MyProject;

MyWriterFont::MyWriterFont(const FontDesc& _desc) :	
	mFontDesc(_desc)
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

	return SUCCEEDED(hr);
}

bool MyWriterFont::CreateTextFormat()
{
	HRESULT hr = mWriteFactory->CreateTextFormat(
		mFontDesc.mFontName.c_str(),
		nullptr,
		mFontDesc.mFontWeight,
		mFontDesc.mFontStyle,
		mFontDesc.mFontStretch,
		mFontDesc.mFontSize,
		mFontDesc.mFontLocalName.c_str(),
		mWriteFont.GetAddressOf());

	return SUCCEEDED(hr);
}

bool MyWriterFont::CreateBrush()
{
	COLOR_F color = { 1.f, 1.f, 1.f, 1.f };
	HRESULT hr = mDevice.mD2dRT->CreateSolidColorBrush(
		color,
		mBrush.GetAddressOf());
	return SUCCEEDED(hr);
}

void MyWriterFont::DrawTexts(const wstringV _msg, RECT_F _rect, COLOR_F _color) const
{
	mDevice.mD2dRT->BeginDraw();
	mBrush->SetColor(_color);
	//mDevice.mD2dRT->DrawRectangle(rc, mDefaultColor.Get());
	//mDevice.mD2dRT->DrawText(_msg.data(), _msg.size(), mWriteFont.Get(),&rc, mDefaultColor.Get());
	//mDevice.mD2dRT->SetTransform(D2D1::Matrix3x2F::Rotation(-10.f));
	mDevice.mD2dRT->DrawText(_msg.data(), _msg.size(), mWriteFont.Get(),&_rect, mBrush.Get());
	mDevice.mD2dRT->EndDraw();
}

const ComPtr<ID2D1SolidColorBrush>& MyWriterFont::GetBrush() const
{
	return mBrush;
}

void MyWriterFont::UpdateComponent()
{
}

void MyWriterFont::RenderComponent()
{
}
