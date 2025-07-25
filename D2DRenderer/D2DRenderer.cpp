#include "pch.h"
#include "D2DRenderer.h"

void D2DRenderer::Initialize(HWND hwnd)
{
	m_hwnd = hwnd;

	CreateDeviceAndSwapChain(hwnd);
	CreateRenderTargets();
	CreateWriteResource();

	ComPtr<IWICImagingFactory> wicFactory;

	HRESULT hr = CoCreateInstance(CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&wicFactory));

	DX::ThrowIfFailed(hr);

	m_wicFactory = wicFactory;
}


void D2DRenderer::UnInitialize()
{
	ReleaseRenderTargets();

	m_wicFactory = nullptr;

	m_targetBitmap = nullptr;
	m_brush = nullptr;

	m_d2dContext = nullptr;
	m_d2dDevice = nullptr;

	m_swapChain = nullptr;
	m_d3dDevice = nullptr;
}

void D2DRenderer::Resize(int width, int height)
{
	if (nullptr == m_swapChain) return;
	ReleaseRenderTargets();

	DX::ThrowIfFailed(m_swapChain->ResizeBuffers(0, width, height, DXGI_FORMAT_UNKNOWN, 0));

	CreateRenderTargets();
}

void D2DRenderer::DrawLine(float x1, float y1, float x2, float y2, const D2D1::ColorF& color)
{
	m_brush->SetColor(color);
	m_d2dContext->DrawLine(D2D1::Point2F(x1, y1), D2D1::Point2F(x2, y2), m_brush.Get());
}

void D2DRenderer::DrawCircle(float x, float y, float radius, const D2D1::ColorF& color)
{
	m_brush->SetColor(color);
	m_d2dContext->DrawEllipse(D2D1::Ellipse(D2D1::Point2F(x, y), radius, radius), m_brush.Get());
}

void D2DRenderer::DrawRectangle(float left, float top, float right, float bottom, const D2D1::ColorF& color)
{
	m_brush->SetColor(color);
	m_d2dContext->DrawRectangle(D2D1::Rect(left, top, right, bottom), m_brush.Get());
}

void D2DRenderer::DrawBitmap(ID2D1Bitmap1* bitmap, D2D1_RECT_F dest)
{
	m_d2dContext->DrawBitmap(bitmap, dest);
}

void D2DRenderer::DrawBitmap(ID2D1Bitmap1* bitmap, D2D1_RECT_F destRect, D2D1_RECT_F srcRect, float opacity /*= 1.0f*/)
{
	m_d2dContext->DrawBitmap(
		bitmap, 
		destRect, 
		opacity, 
		D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, 
		srcRect
	);
}

void D2DRenderer::DrawMessage(const wchar_t* text, float left, float top, float width, float height, const D2D1::ColorF& color)
{
	if (nullptr == m_textBrush)
	{
		m_d2dContext->CreateSolidColorBrush(D2D1::ColorF(color), &m_textBrush);
	}

	m_textBrush->SetColor(color);
	D2D1_RECT_F layoutRect = D2D1::RectF(left, top, left + width, top + height);

	m_d2dContext->DrawTextW(
		text,
		static_cast<UINT32>(wcslen(text)),
		m_textFormat.Get(),
		layoutRect,
		m_textBrush.Get(),
		D2D1_DRAW_TEXT_OPTIONS_NONE,
		DWRITE_MEASURING_MODE_NATURAL
	);
}

void D2DRenderer::SetTransform(const D2D1_MATRIX_3X2_F tm)
{
	if (m_d2dContext) m_d2dContext->SetTransform(tm);
}

void D2DRenderer::RenderBegin()
{
	m_d2dContext->BeginDraw();
	m_d2dContext->Clear(D2D1::ColorF(D2D1::ColorF::White));
}

void D2DRenderer::RenderEnd(bool bPresent /*= true*/)
{
	m_d2dContext->EndDraw();

	if (bPresent)
	{
		Present();
	}
}

void D2DRenderer::Present()
{
	HRESULT hr = m_swapChain->Present(1, 0);

	if (hr == DXGI_ERROR_DEVICE_REMOVED || hr == DXGI_ERROR_DEVICE_RESET)
	{
		UnInitialize();
		Initialize(m_hwnd);
	}
	else
	{
		DX::ThrowIfFailed(hr);
	}
}

void D2DRenderer::CreateBitmapFromFile(const wchar_t* path, ID2D1Bitmap1*& outBitmap)
{
	ComPtr<IWICBitmapDecoder>		decoder;
	ComPtr<IWICBitmapFrameDecode>	frame;
	ComPtr<IWICFormatConverter>		converter;

	HRESULT hr = m_wicFactory->CreateDecoderFromFilename(path, nullptr, GENERIC_READ, WICDecodeMetadataCacheOnLoad, &decoder);

	DX::ThrowIfFailed(hr);

	hr = decoder->GetFrame(0, &frame);

	DX::ThrowIfFailed(hr);

	hr = m_wicFactory->CreateFormatConverter(&converter);

	DX::ThrowIfFailed(hr);

	hr = converter->Initialize(
		frame.Get(),
		GUID_WICPixelFormat32bppPBGRA,
		WICBitmapDitherTypeNone,
		nullptr,
		0.0f, 
		WICBitmapPaletteTypeCustom
	);

	DX::ThrowIfFailed(hr);

	D2D1_BITMAP_PROPERTIES1 bmpProps = D2D1::BitmapProperties1(
		D2D1_BITMAP_OPTIONS_NONE, 
		D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_PREMULTIPLIED)
	);

	hr = m_d2dContext->CreateBitmapFromWicBitmap(converter.Get(), &bmpProps, &outBitmap);

}

void D2DRenderer::CreateDeviceAndSwapChain(HWND hwnd)
{
	D3D_FEATURE_LEVEL featureLevels[] = { D3D_FEATURE_LEVEL_11_0 };
	ComPtr<ID3D11Device> d3dDevice;
	ComPtr<ID3D11DeviceContext> d3dContext;

	HRESULT hr = D3D11CreateDevice(
		nullptr, 
		D3D_DRIVER_TYPE_HARDWARE, 
		nullptr, 
		D3D11_CREATE_DEVICE_BGRA_SUPPORT, 
		featureLevels, 
		ARRAYSIZE(featureLevels), 
		D3D11_SDK_VERSION, 
		&d3dDevice, 
		nullptr, 
		&d3dContext
	);

	DX::ThrowIfFailed(hr);

	ComPtr<IDXGIDevice> dxgiDevice;
	hr = d3dDevice.As(&dxgiDevice);

	DX::ThrowIfFailed(hr);

	ComPtr<IDXGIAdapter> dxgiAdapter;
	hr = dxgiDevice->GetAdapter(&dxgiAdapter);

	DX::ThrowIfFailed(hr);

	ComPtr<IDXGIFactory2> dxgiFactory;
	hr = dxgiAdapter->GetParent(IID_PPV_ARGS(&dxgiFactory));

	DX::ThrowIfFailed(hr);

	DXGI_SWAP_CHAIN_DESC1 scDesc = {};
	scDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	scDesc.SampleDesc.Count = 1;
	scDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	scDesc.BufferCount = 2;
	scDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	scDesc.Scaling = DXGI_SCALING_STRETCH;

	ComPtr<IDXGISwapChain1> swapChain;

	hr = dxgiFactory->CreateSwapChainForHwnd(d3dDevice.Get(), hwnd, &scDesc, nullptr, nullptr, &swapChain);

	DX::ThrowIfFailed(hr);

	D2D1_FACTORY_OPTIONS opts = {};
	ComPtr<ID2D1Factory8> d2dFactory;

#if defined(_DEBUG)
	opts.debugLevel = D2D1_DEBUG_LEVEL_INFORMATION;
#endif

	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, __uuidof(ID2D1Factory8), &opts, reinterpret_cast<void**>(d2dFactory.GetAddressOf()));

	DX::ThrowIfFailed(hr);

	ComPtr<ID2D1Device> baseDevice;
	hr = d2dFactory->CreateDevice(dxgiDevice.Get(), &baseDevice);

	DX::ThrowIfFailed(hr);

	ComPtr<ID2D1Device7> d2dDevice;
	hr = baseDevice.As(&d2dDevice);

	DX::ThrowIfFailed(hr);

	ComPtr<ID2D1DeviceContext7> d2dContext;
	hr = d2dDevice->CreateDeviceContext(D2D1_DEVICE_CONTEXT_OPTIONS_NONE, &d2dContext);

	DX::ThrowIfFailed(hr);

	m_d3dDevice = d3dDevice;
	m_d3dContext = d3dContext;
	m_swapChain = swapChain;

	m_d2dDevice = d2dDevice;
	m_d2dContext = d2dContext;
}

void D2DRenderer::CreateRenderTargets()
{
	ComPtr<IDXGISurface> dxgiSurface;
	HRESULT hr = m_swapChain->GetBuffer(0, IID_PPV_ARGS(&dxgiSurface));

	DX::ThrowIfFailed(hr);

	D2D1_BITMAP_PROPERTIES1 bitmapProps = {};
	bitmapProps.bitmapOptions = D2D1_BITMAP_OPTIONS_TARGET | D2D1_BITMAP_OPTIONS_CANNOT_DRAW;
	bitmapProps.pixelFormat.format = DXGI_FORMAT_B8G8R8A8_UNORM;
	bitmapProps.pixelFormat.alphaMode = D2D1_ALPHA_MODE_PREMULTIPLIED;
	bitmapProps.dpiX = bitmapProps.dpiY = 96.0f;

	ComPtr<ID2D1Bitmap1> targetBitmap;
	hr = m_d2dContext->CreateBitmapFromDxgiSurface(dxgiSurface.Get(), &bitmapProps, targetBitmap.GetAddressOf());

	DX::ThrowIfFailed(hr);

	m_d2dContext->SetTarget(targetBitmap.Get());

	m_targetBitmap = targetBitmap;

	hr = m_d2dContext->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Blue), &m_brush);

	DX::ThrowIfFailed(hr);

	ComPtr<ID3D11Texture2D> backBuffer;
	hr = m_swapChain->GetBuffer(0, IID_PPV_ARGS(&backBuffer));

	DX::ThrowIfFailed(hr);

	ComPtr<ID3D11RenderTargetView> mainRTV;
	hr = m_d3dDevice->CreateRenderTargetView(backBuffer.Get(), nullptr, &mainRTV);

	DX::ThrowIfFailed(hr);

	m_d3dRenderTargetView = mainRTV;
}

void D2DRenderer::CreateWriteResource()
{
	ComPtr<IDWriteFactory> writeFactory = nullptr;
	HRESULT hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), reinterpret_cast<IUnknown**>(writeFactory.GetAddressOf()));

	DX::ThrowIfFailed(hr);

	writeFactory->CreateTextFormat(
		L"",
		NULL,
		DWRITE_FONT_WEIGHT_NORMAL,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		15.0f,
		L"",
		&m_textFormat);

	DX::ThrowIfFailed(hr);

	m_textFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
	m_textFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
	m_textFormat->SetWordWrapping(DWRITE_WORD_WRAPPING_WRAP);
}

void D2DRenderer::ReleaseRenderTargets()
{
	if (m_d2dContext)
	{
		m_d2dContext->SetTarget(nullptr);
	}

	m_d3dRenderTargetView.Reset();
	
	m_targetBitmap.Reset();
	m_brush.Reset();
	m_textBrush.Reset();
}
