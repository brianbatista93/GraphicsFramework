#pragma once

#include "Dx11Common.h"
#include "GraphicsResources.h"

class Dx11Texture2D : public GpuTexture2D
{
  public:
    Dx11Texture2D(class Dx11Device* device, IDXGISwapChain* swapChain);

    Dx11Texture2D(class Dx11Device* device, uint32_t width, uint32_t height, EPixelFormat format);

    ~Dx11Texture2D() { m_device = nullptr; }

  private:
    void CreateViews();

  private:
    class Dx11Device*                 m_device;
    ComPtr<ID3D11Texture2D>           m_dx11Texture;
    ComPtr<ID3D11ShaderResourceView>  m_dx11SRV;
    ComPtr<ID3D11RenderTargetView>    m_dx11RT;
    ComPtr<ID3D11DepthStencilView>    m_dx11DSV;
    ComPtr<ID3D11UnorderedAccessView> m_dx11UAV;
};