#include "DX11Device.h"
#include "DX11GraphicsContext.h"
#include "DX11Surface.h"
#include "Interfaces/CommandList.h"

bool
DX11Device::Initialize()
{
    if (!CreateDeviceImpl()) {
        return false;
    }

    gCommandList.SetGraphicsContext(new DX11GraphicsContext(this));

    return true;
}

void
DX11Device::Shutdown()
{
    m_d3d11Context.Reset();
    m_d3d11Device.Reset();
}

bool
DX11Device::CreateDeviceImpl()
{
    UINT flags = 0;

    D3D_FEATURE_LEVEL featureLevels[] = {D3D_FEATURE_LEVEL_11_0};

#ifdef _DEBUG
    flags |= D3D11_CREATE_DEVICE_DEBUG;
#endif // _DEBUG

    ComPtr<ID3D11Device>        device  = nullptr;
    ComPtr<ID3D11DeviceContext> context = nullptr;

    HRESULT result = D3D11CreateDevice(nullptr,
                                       D3D_DRIVER_TYPE_HARDWARE,
                                       NULL,
                                       flags,
                                       featureLevels,
                                       _countof(featureLevels),
                                       D3D11_SDK_VERSION,
                                       &device,
                                       &m_featureLevel,
                                       &context);

    if (FAILED(device.As(&m_d3d11Device))) {
        return false;
    }

    if (FAILED(context.As(&m_d3d11Context))) {
        return false;
    }

    if (FAILED(result)) {
        SetErrorMessage("D3D11CreateDevice failed: " + std::to_string(result));
        return false;
    }

    return true;
}

IGraphicsContext*
DX11Device::CreateGraphicsContext()
{
    return new DX11GraphicsContext(this);
}

IGraphicsSurface*
DX11Device::CreateSurface(void* windowHandle, uint32 width, uint32 height)
{
    ComPtr<IDXGIFactory>   dxgiFactory;
    ComPtr<IDXGIDevice>    dxgiDevice;
    ComPtr<IDXGIAdapter>   dxgiAdapter;
    ComPtr<IDXGISwapChain> swapChain;

    if (FAILED(m_d3d11Device->QueryInterface(IID_PPV_ARGS(&dxgiDevice)))) {
        return nullptr;
    }

    if (FAILED(dxgiDevice->GetAdapter(&dxgiAdapter))) {
        return nullptr;
    }

    if (FAILED(dxgiAdapter->GetParent(IID_PPV_ARGS(&dxgiFactory)))) {
        return nullptr;
    }

    DXGI_SWAP_CHAIN_DESC swapChainDesc {
      .BufferDesc {
        .Width  = width,
        .Height = height,
        .Format = DXGI_FORMAT_R10G10B10A2_UNORM,
      },
      .SampleDesc {
        .Count   = 1,
        .Quality = 0,
      },
      .BufferUsage  = DXGI_USAGE_RENDER_TARGET_OUTPUT | DXGI_USAGE_SHADER_INPUT,
      .BufferCount  = 2,
      .OutputWindow = reinterpret_cast<HWND>(windowHandle),
      .Windowed     = TRUE,
      .SwapEffect   = DXGI_SWAP_EFFECT_FLIP_DISCARD,
      .Flags        = 0,
    };

    if (FAILED(dxgiFactory->CreateSwapChain(m_d3d11Device.Get(), &swapChainDesc, &swapChain))) {
        SetErrorMessage("CreateSwapChain failed.");
        return nullptr;
    }

    return new DX11Surface(this, swapChain.Get());
}
