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
	_ASSERT(CreateDevice());
}

MyWriterFont::~MyWriterFont()
{
	MyWriterFont::ReleaseComponent();
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
		mFontWeight,
		mFontStyle,
		mFontStretch,
		mFontSize,
		mFontLocalName.c_str(),
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
	COLOR_F color = { 1.f, 1.f, 1.f, 1.f };
	HRESULT hr = mD2dRT->CreateSolidColorBrush(
		color,
		mDefaultColor.GetAddressOf());
	return !FAILED(hr);
}

void MyWriterFont::DrawTexts(const wstringV _msg, POINT_F _pos, COLOR_F _color) const
{
	RECT_F rc = { 
		_pos.x, 
		_pos.y, 
		mWindow.GetWindowSizeF().x*2, 
		mWindow.GetWindowSizeF().y*2 };

	mD2dRT->BeginDraw();
	mDefaultColor->SetColor(_color);
	mD2dRT->DrawText(_msg.data(), _msg.size(), mWriteFont.Get(),&rc, mDefaultColor.Get());
	mD2dRT->EndDraw();
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

