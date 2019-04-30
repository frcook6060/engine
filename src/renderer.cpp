#include "sys.h"

// Swap Chain
static IDXGISwapChain* swapChain = nullptr;
// Device
static ID3D11Device* device = nullptr;
// Context
static ID3D11DeviceContext* context = nullptr;
// Render Target View
static ID3D11RenderTargetView* renderTargetView = nullptr;
// Depth Buffer Texture
static ID3D11Texture2D* depthBufferTexture = nullptr;
// Depth Stencil State
static ID3D11DepthStencilState* depthBufferState = nullptr;
// Depth Stencil View
static ID3D11DepthStencilView* depthBufferView = nullptr;
// Raster State
static ID3D11RasterizerState* rasterState = nullptr;

void rend_init()
{
	HRESULT r;

	DXGI_SWAP_CHAIN_DESC desc = {};
	desc.BufferCount = 1;

	desc.BufferDesc.Width = app_getConfig()->width;
	desc.BufferDesc.Height = app_getConfig()->height;
	desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.BufferDesc.RefreshRate.Numerator = 0;
	desc.BufferDesc.RefreshRate.Denominator = 1;
	desc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	desc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;

	desc.OutputWindow = app_getConfig()->hwnd;

	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;

	desc.Windowed = TRUE;

	desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	desc.Flags = 0;

	// Create SwapChain, Device, and Context
	r = D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		0,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		&desc,
		&swapChain,
		&device,
		nullptr,
		&context);

	if (FAILED(r))
	{
		throw std::runtime_error("Failed to create swap chain, device, and context.");
	}

	ID3D11Texture2D* backBuffer = nullptr;
	r = swapChain->GetBuffer(
		0,
		__uuidof(ID3D11Texture2D),
		(void**)&backBuffer
	);

	if (FAILED(r))
	{
		throw std::runtime_error("Failed to grab backbuffer...");
	}

	r = device->CreateRenderTargetView(
		backBuffer,
		nullptr,
		&renderTargetView
	);

	if (FAILED(r))
	{
		throw std::runtime_error("Failed to create render view");
	}

	if (backBuffer)
	{
		backBuffer->Release();
	}

	// Depth Buffer Desc
	D3D11_TEXTURE2D_DESC depthBufferDesc = {};
	depthBufferDesc.Width = app_getConfig()->width;
	depthBufferDesc.Height = app_getConfig()->height;
	depthBufferDesc.MipLevels = 1;
	depthBufferDesc.ArraySize = 1;
	depthBufferDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthBufferDesc.SampleDesc.Count = 1;
	depthBufferDesc.SampleDesc.Quality = 0;
	depthBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	depthBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthBufferDesc.CPUAccessFlags = 0;
	depthBufferDesc.MiscFlags = 0;

	r = device->CreateTexture2D(
		&depthBufferDesc,
		nullptr,
		&depthBufferTexture);

	if (FAILED(r))
	{
		throw std::runtime_error("Error: Failed to create depth buffer texture");
	}

	D3D11_DEPTH_STENCIL_DESC depthStencilDesc = {};
	depthStencilDesc.DepthEnable = true;
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;
	depthStencilDesc.StencilEnable = false;
	r = device->CreateDepthStencilState(
		&depthStencilDesc,
		&depthBufferState);

	if (FAILED(r))
	{
		throw std::runtime_error("Failed to create depth stencil state.");
	}

	D3D11_DEPTH_STENCIL_VIEW_DESC depthViewDesc = {};
	depthViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	depthViewDesc.Texture2D.MipSlice = 0;
	r = device->CreateDepthStencilView(
		depthBufferTexture,
		&depthViewDesc,
		&depthBufferView);

	if (FAILED(r))
	{
		std::runtime_error("Error Failed to create depth view...");
	}


	D3D11_RASTERIZER_DESC rastDesc = {};
	rastDesc.AntialiasedLineEnable = false;
	rastDesc.CullMode = D3D11_CULL_NONE;
	rastDesc.DepthBias = 0;
	rastDesc.SlopeScaledDepthBias = 0.0f;
	rastDesc.DepthClipEnable = true;
	rastDesc.FillMode = D3D11_FILL_SOLID;
	rastDesc.FrontCounterClockwise = false;
	rastDesc.MultisampleEnable = false;
	rastDesc.ScissorEnable = false;
	rastDesc.SlopeScaledDepthBias = 0.0f;

	r = rend_getDevice()->CreateRasterizerState(
		&rastDesc,
		&rasterState
	);

	if (FAILED(r))
	{
		std::runtime_error("Error: raster state wasn't created...");
	}
	context->OMSetDepthStencilState(depthBufferState, 1);
	context->OMSetRenderTargets(1, &renderTargetView, depthBufferView);
	context->RSSetState(rasterState);

}

void rend_release()
{
	SAFE_RELEASE(rasterState);
	SAFE_RELEASE(depthBufferView);
	SAFE_RELEASE(depthBufferState);
	SAFE_RELEASE(depthBufferTexture);
	SAFE_RELEASE(renderTargetView);
	SAFE_RELEASE(context);
	SAFE_RELEASE(device);
	SAFE_RELEASE(swapChain);
}

IDXGISwapChain* rend_getSwapChain()
{
	return swapChain;
}

ID3D11Device* rend_getDevice()
{
	return device;
}

ID3D11DeviceContext* rend_getContext()
{
	return context;
}

void rend_clear(const glm::vec4& color, float depth)
{
	rend_clearColor(color);
	rend_clearDepth(depth);
}

void rend_clearColor(const glm::vec4& color)
{
	context->ClearRenderTargetView(renderTargetView, (float*)&color);
}

void rend_clearDepth(float depth)
{
	context->ClearDepthStencilView(depthBufferView, D3D11_CLEAR_DEPTH, depth, 0);
}

void rend_present()
{
	swapChain->Present(0, 0);
}