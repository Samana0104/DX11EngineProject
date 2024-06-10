#include "MyWriterFont.h"
using namespace MyProject;

MyWriterFont::MyWriterFont(std::wstring _fontName, FLOAT _fontSize, COLOR_F	_color)
	:	mFontName(_fontName),
		mFontSize(_fontSize),
		mColor(_color)
{
	_ASSERT(CreateDevice());
}

bool MyWriterFont::CreateDevice()
{
	if (!CreateD2D1Factory())
		return false;

	if (!CreateDWriteFactory())
		return false;
	
	if (!CreateTextFormat())
		return false;
	
	if (!CreateRenderTarget())
		return false;
	
	if (!CreateBrush())
		return false;

	return true;
}

bool MyWriterFont::CreateD2D1Factory()
{
	HRESULT hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, mD2dFactory.GetAddressOf());

	return !FAILED(hr);
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
		DWRITE_FONT_WEIGHT_THIN,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		mFontSize,
		L"ko-kr", // L"en-us"
		mWriteFont.GetAddressOf());

	return !FAILED(hr);
}

bool MyWriterFont::CreateRenderTarget()
{
	HRESULT hr; //IDXGISurface* dxgiSurface = nullptr;
	IDXGISurface* dxgiSurface;

	hr = mDevice.mSwapChain->GetBuffer(0, __uuidof(IDXGISurface),
		reinterpret_cast<void**>(&dxgiSurface));

	if (FAILED(hr))
		return false;

	D2D1_RENDER_TARGET_PROPERTIES rtp;
	rtp.type = D2D1_RENDER_TARGET_TYPE_DEFAULT;
	rtp.pixelFormat.format = DXGI_FORMAT_UNKNOWN;
	rtp.pixelFormat.alphaMode = D2D1_ALPHA_MODE_PREMULTIPLIED;
	rtp.dpiX = 0;
	rtp.dpiY = 0;
	rtp.usage = D2D1_RENDER_TARGET_USAGE_NONE;
	rtp.minLevel = D2D1_FEATURE_LEVEL_DEFAULT;

	// 3d : 2D 연동가능한 렌더타켓 생성(D3D11_CREATE_DEVICE_BGRA_SUPPORT)
	hr = mD2dFactory->CreateDxgiSurfaceRenderTarget(
		dxgiSurface,
		&rtp,
		mD2dRT.GetAddressOf());

	dxgiSurface->Release();

	return !FAILED(hr);
}

bool MyWriterFont::CreateBrush()
{
	HRESULT hr = mD2dRT->CreateSolidColorBrush(
		mColor,
		mDefaultColor.GetAddressOf());

	return !FAILED(hr);
}

void MyWriterFont::DrawTexts(std::wstring msg, RECT_F _pos)
{
	mD2dRT->BeginDraw();
	mDefaultColor->SetColor(mColor);
	mD2dRT->DrawText(msg.c_str(), msg.size(), mWriteFont.Get(),&_pos, mDefaultColor.Get());
	mD2dRT->EndDraw();
}

void MyWriterFont::InitComponent()
{
}

void MyWriterFont::UpdateComponent()
{
}

void MyWriterFont::RenderComponent()
{
}

void MyWriterFont::ReleaseComponent()
{
	mWriteFont->Release();
	mDefaultColor->Release();
	mD2dFactory->Release();
	mWriteFactory->Release();
	mD2dRT->Release();
}

