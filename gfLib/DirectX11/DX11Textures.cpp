#include "DX11Device.h"
#include "DX11Resources.h"
#include <assert.h>

DXGI_FORMAT
GetD3D11Format(EPixelFormat format)
{
    switch (format) {
        case PIXEL_FORMAT_R8G8B8A8:
            return DXGI_FORMAT_R8G8B8A8_UNORM;
        case PIXEL_FORMAT_R8G8B8A8_UINT:
            return DXGI_FORMAT_R8G8B8A8_UINT;
        case PIXEL_FORMAT_R10G10B10A2:
            return DXGI_FORMAT_R10G10B10A2_UNORM;
        default:
            return DXGI_FORMAT_UNKNOWN;
    }
}

EPixelFormat
GetFrameworkFormat(DXGI_FORMAT format)
{
    switch (format) {
        case DXGI_FORMAT_R8G8B8A8_UNORM:
            return PIXEL_FORMAT_R8G8B8A8;
        case DXGI_FORMAT_R8G8B8A8_UINT:
            return PIXEL_FORMAT_R8G8B8A8_UINT;
        case DXGI_FORMAT_R10G10B10A2_UNORM:
            return PIXEL_FORMAT_R10G10B10A2;
        default:
            return PIXEL_FORMAT_UNKNOWN;
    }
}

D3D11_USAGE
GetD3D11Usage(uint32_t flags) { return D3D11_USAGE_DEFAULT; }

DXGI_FORMAT
GetBaseFormat(DXGI_FORMAT format)
{
    switch (format) {
        case DXGI_FORMAT_R8G8B8A8_UNORM:
        case DXGI_FORMAT_R8G8B8A8_UNORM_SRGB:
            return DXGI_FORMAT_R8G8B8A8_TYPELESS;

        case DXGI_FORMAT_B8G8R8A8_UNORM:
        case DXGI_FORMAT_B8G8R8A8_UNORM_SRGB:
            return DXGI_FORMAT_B8G8R8A8_TYPELESS;

        case DXGI_FORMAT_B8G8R8X8_UNORM:
        case DXGI_FORMAT_B8G8R8X8_UNORM_SRGB:
            return DXGI_FORMAT_B8G8R8X8_TYPELESS;

        // 32-bit Z w/ Stencil
        case DXGI_FORMAT_R32G8X24_TYPELESS:
        case DXGI_FORMAT_D32_FLOAT_S8X24_UINT:
        case DXGI_FORMAT_R32_FLOAT_X8X24_TYPELESS:
        case DXGI_FORMAT_X32_TYPELESS_G8X24_UINT:
            return DXGI_FORMAT_R32G8X24_TYPELESS;

        // No Stencil
        case DXGI_FORMAT_R32_TYPELESS:
        case DXGI_FORMAT_D32_FLOAT:
        case DXGI_FORMAT_R32_FLOAT:
            return DXGI_FORMAT_R32_TYPELESS;

        // 24-bit Z
        case DXGI_FORMAT_R24G8_TYPELESS:
        case DXGI_FORMAT_D24_UNORM_S8_UINT:
        case DXGI_FORMAT_R24_UNORM_X8_TYPELESS:
        case DXGI_FORMAT_X24_TYPELESS_G8_UINT:
            return DXGI_FORMAT_R24G8_TYPELESS;

        // 16-bit Z w/o Stencil
        case DXGI_FORMAT_R16_TYPELESS:
        case DXGI_FORMAT_D16_UNORM:
        case DXGI_FORMAT_R16_UNORM:
            return DXGI_FORMAT_R16_TYPELESS;

        default:
            return format;
    }
}

DXGI_FORMAT
GetDSVFormat(DXGI_FORMAT format)
{
    switch (format) {
        // 32-bit Z w/ Stencil
        case DXGI_FORMAT_R32G8X24_TYPELESS:
        case DXGI_FORMAT_D32_FLOAT_S8X24_UINT:
        case DXGI_FORMAT_R32_FLOAT_X8X24_TYPELESS:
        case DXGI_FORMAT_X32_TYPELESS_G8X24_UINT:
            return DXGI_FORMAT_D32_FLOAT_S8X24_UINT;

        // No Stencil
        case DXGI_FORMAT_R32_TYPELESS:
        case DXGI_FORMAT_D32_FLOAT:
        case DXGI_FORMAT_R32_FLOAT:
            return DXGI_FORMAT_D32_FLOAT;

        // 24-bit Z
        case DXGI_FORMAT_R24G8_TYPELESS:
        case DXGI_FORMAT_D24_UNORM_S8_UINT:
        case DXGI_FORMAT_R24_UNORM_X8_TYPELESS:
        case DXGI_FORMAT_X24_TYPELESS_G8_UINT:
            return DXGI_FORMAT_D24_UNORM_S8_UINT;

        // 16-bit Z w/o Stencil
        case DXGI_FORMAT_R16_TYPELESS:
        case DXGI_FORMAT_D16_UNORM:
        case DXGI_FORMAT_R16_UNORM:
            return DXGI_FORMAT_D16_UNORM;

        default:
            return format;
    }
}

DXGI_FORMAT
GetUAVFormat(DXGI_FORMAT format)
{
    switch (format) {
        case DXGI_FORMAT_R8G8B8A8_TYPELESS:
        case DXGI_FORMAT_R8G8B8A8_UNORM:
        case DXGI_FORMAT_R8G8B8A8_UNORM_SRGB:
            return DXGI_FORMAT_R8G8B8A8_UNORM;

        case DXGI_FORMAT_B8G8R8A8_TYPELESS:
        case DXGI_FORMAT_B8G8R8A8_UNORM:
        case DXGI_FORMAT_B8G8R8A8_UNORM_SRGB:
            return DXGI_FORMAT_B8G8R8A8_UNORM;

        case DXGI_FORMAT_B8G8R8X8_TYPELESS:
        case DXGI_FORMAT_B8G8R8X8_UNORM:
        case DXGI_FORMAT_B8G8R8X8_UNORM_SRGB:
            return DXGI_FORMAT_B8G8R8X8_UNORM;

        case DXGI_FORMAT_R32_TYPELESS:
        case DXGI_FORMAT_R32_FLOAT:
            return DXGI_FORMAT_R32_FLOAT;

#ifdef _DEBUG
        case DXGI_FORMAT_R32G8X24_TYPELESS:
        case DXGI_FORMAT_D32_FLOAT_S8X24_UINT:
        case DXGI_FORMAT_R32_FLOAT_X8X24_TYPELESS:
        case DXGI_FORMAT_X32_TYPELESS_G8X24_UINT:
        case DXGI_FORMAT_D32_FLOAT:
        case DXGI_FORMAT_R24G8_TYPELESS:
        case DXGI_FORMAT_D24_UNORM_S8_UINT:
        case DXGI_FORMAT_R24_UNORM_X8_TYPELESS:
        case DXGI_FORMAT_X24_TYPELESS_G8_UINT:
        case DXGI_FORMAT_D16_UNORM:

            assert(false && "Requested a UAV Format for a depth stencil Format.");
#endif

        default:
            return format;
    }
}

UINT
GetD3D11BindFlags(uint32_t flags)
{
    UINT bind = 0;

    if (HAS_FLAG(flags, TEXTURE_FLAG_RENDER_TARGET)) {
        bind |= D3D11_BIND_RENDER_TARGET;
    }

    if (HAS_FLAG(flags, TEXTURE_FLAG_DEPTH_STENCIL)) {
        bind |= D3D11_BIND_DEPTH_STENCIL;
    }

    if (HAS_FLAG(flags, TEXTURE_FLAG_SHADER_RESOURCE)) {
        bind |= D3D11_BIND_SHADER_RESOURCE;
    }

    if (HAS_FLAG(flags, TEXTURE_FLAG_UNORDERED_ACCESS)) {
        bind |= D3D11_BIND_UNORDERED_ACCESS;
    }

    return bind;
}

DX11Texture2D::DX11Texture2D(DX11Device* device, IDXGISwapChain* swapChain)
  : m_device(device)
  , GpuTexture2D(0, 0, PIXEL_FORMAT_UNKNOWN)
{
    ThrowIfFailed(swapChain->GetBuffer(0, IID_PPV_ARGS(&m_dx11Texture)));

    D3D11_TEXTURE2D_DESC desc;
    m_dx11Texture->GetDesc(&desc);
    m_width  = desc.Width;
    m_height = desc.Height;
    m_format = GetFrameworkFormat(desc.Format);
    m_flags  = TEXTURE_FLAG_SWAP_CHAIN;

    CreateViews();
}

DX11Texture2D::DX11Texture2D(DX11Device* device, uint32 width, uint32 height, EPixelFormat format, ETextureFlags flags)
  : m_device(device)
  , GpuTexture2D(width, height, format, flags)
{
    D3D11_TEXTURE2D_DESC desc {
      .Width     = width,
      .Height    = height,
      .MipLevels = 0,
      .ArraySize = 1,
      .Format    = GetD3D11Format(format),
      .SampleDesc {
        .Count   = 1,
        .Quality = 0,
      },
      .Usage          = GetD3D11Usage(m_flags),
      .BindFlags      = GetD3D11BindFlags(m_flags),
      .CPUAccessFlags = 0,
      .MiscFlags      = 0,
    };

    ThrowIfFailed(device->GetD3D11Device()->CreateTexture2D(&desc, NULL, &m_dx11Texture));
    CreateViews();
}

void
DX11Texture2D::CreateViews()
{
    auto        dx11Device = m_device->GetD3D11Device();
    DXGI_FORMAT format     = GetD3D11Format(m_format);

    if (HAS_FLAG(m_flags, TEXTURE_FLAG_RENDER_TARGET)) {
        D3D11_RENDER_TARGET_VIEW_DESC rtDesc
          = CD3D11_RENDER_TARGET_VIEW_DESC(m_dx11Texture.Get(), D3D11_RTV_DIMENSION_TEXTURE2D, GetBaseFormat(format));

        ThrowIfFailed(dx11Device->CreateRenderTargetView(m_dx11Texture.Get(), &rtDesc, &m_dx11RT));
    } else if (HAS_FLAG(m_flags, TEXTURE_FLAG_SWAP_CHAIN)) {
        ThrowIfFailed(dx11Device->CreateRenderTargetView(m_dx11Texture.Get(), NULL, &m_dx11RT));
    }

    if (HAS_FLAG(m_flags, TEXTURE_FLAG_DEPTH_STENCIL)) {

        D3D11_DEPTH_STENCIL_VIEW_DESC dsDesc
          = CD3D11_DEPTH_STENCIL_VIEW_DESC(m_dx11Texture.Get(), D3D11_DSV_DIMENSION_TEXTURE2D, GetDSVFormat(format));

        ThrowIfFailed(dx11Device->CreateDepthStencilView(m_dx11Texture.Get(), &dsDesc, &m_dx11DSV));
    }

    if (HAS_FLAG(m_flags, TEXTURE_FLAG_SHADER_RESOURCE)) {

        D3D11_SHADER_RESOURCE_VIEW_DESC srDesc
          = CD3D11_SHADER_RESOURCE_VIEW_DESC(m_dx11Texture.Get(), D3D11_SRV_DIMENSION_TEXTURE2D, GetBaseFormat(format));

        ThrowIfFailed(dx11Device->CreateShaderResourceView(m_dx11Texture.Get(), &srDesc, &m_dx11SRV));
    }

    if (HAS_FLAG(m_flags, TEXTURE_FLAG_UNORDERED_ACCESS)) {

        D3D11_UNORDERED_ACCESS_VIEW_DESC uaDesc
          = CD3D11_UNORDERED_ACCESS_VIEW_DESC(m_dx11Texture.Get(), D3D11_UAV_DIMENSION_TEXTURE2D, GetUAVFormat(format));

        ThrowIfFailed(dx11Device->CreateUnorderedAccessView(m_dx11Texture.Get(), &uaDesc, &m_dx11UAV));
    }
}