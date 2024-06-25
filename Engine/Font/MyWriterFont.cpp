#include "pch.h"
#include "MyWriterFont.h"
using namespace MyProject;

MyWriterFont::MyWriterFont(const FontDesc& _desc) :	
	mFontDesc(_desc)
{
#ifdef _DEBUG
	_ASSERT(CreateBrushComponent());
#else
	CreateBrushComponent();
#endif
	MyWindow::GetInstance().RegisterCallBackWMSize(this, &MyWriterFont::OnWMSize);
}

void MyWriterFont::OnWMSize(UINT _weight, UINT _height)
{
	mWriteFactory->Release();
	mWriteFont->Release();
	mBrush->Release();

	CreateBrushComponent();
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

void MyWriterFont::DrawBegin()
{
	D2D1_MATRIX_3X2_F convertMat;
	mat3 trsMat = mTransform->GetViewMat();

	mDevice.mD2dRT->GetTransform(&mTempMat);

	convertMat.m11 = trsMat[0][0];
	convertMat.m12 = trsMat[0][1];
	convertMat.m21 = trsMat[1][0];
	convertMat.m22 = trsMat[1][1];
	convertMat.dx = trsMat[2][0];
	convertMat.dy = trsMat[2][1];

	mDevice.mD2dRT->SetTransform(convertMat);
}

void MyWriterFont::DrawEnd()
{
	mDevice.mD2dRT->SetTransform(mTempMat);
}

void MyWriterFont::DrawTexts(const wstringV _msg, RECT_F _rect, COLOR_F _color) 
{
	DrawBegin();
	mDevice.mD2dRT->BeginDraw();
	mBrush->SetColor(_color);
	//mDevice.mD2dRT->DrawRectangle(rc, mDefaultColor.Get());
	//mDevice.mD2dRT->DrawText(_msg.data(), _msg.size(), mWriteFont.Get(),&rc, mDefaultColor.Get());
	//mDevice.mD2dRT->SetTransform(D2D1::Matrix3x2F::Rotation(-10.f));
	mDevice.mD2dRT->DrawText(_msg.data(), _msg.size(), mWriteFont.Get(),&_rect, mBrush.Get());
	mDevice.mD2dRT->EndDraw();
	DrawEnd();
}

const ComPtr<ID2D1SolidColorBrush>& MyWriterFont::GetBrush() const
{
	return mBrush;
}

void MyWriterFont::SetBold()
{
	if (isBold())
	{
		mWriteFont->Release();
		mFontDesc.mFontWeight = DWRITE_FONT_WEIGHT_NORMAL;
		CreateTextFormat();
	}
	else
	{
		mWriteFont->Release();
		mFontDesc.mFontWeight = DWRITE_FONT_WEIGHT_BOLD;
		CreateTextFormat();
	}
}

bool MyWriterFont::isBold() const
{
	if (mFontDesc.mFontWeight == DWRITE_FONT_WEIGHT_BOLD)
		return true;
	else
		return false;
}

MyTransformer2D* MyWriterFont::operator->()
{
	return &mTransform;
}
