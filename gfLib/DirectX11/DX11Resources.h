#pragma once

#include "Dx11Common.h"
#include "Interfaces/GraphicsResources.h"

class DX11Texture2D : public GpuTexture2D
{
  public:
    DX11Texture2D(class DX11Device* device, IDXGISwapChain* swapChain);

    DX11Texture2D(class DX11Device* device, uint32 width, uint32 height, EPixelFormat format);

    ~DX11Texture2D() { m_device = nullptr; }

    ComPtr<ID3D11Texture2D>           GetDx11Texture() { return m_dx11Texture; }
    ComPtr<ID3D11ShaderResourceView>  GetDx11SRV() { return m_dx11SRV; }
    ComPtr<ID3D11RenderTargetView>    GetDx11RT() { return m_dx11RT; }
    ComPtr<ID3D11DepthStencilView>    GetDx11DSV() { return m_dx11DSV; }
    ComPtr<ID3D11UnorderedAccessView> GetDx11UAV() { return m_dx11UAV; }

  private:
    void CreateViews();

  private:
    class DX11Device*                 m_device;
    ComPtr<ID3D11Texture2D>           m_dx11Texture;
    ComPtr<ID3D11ShaderResourceView>  m_dx11SRV;
    ComPtr<ID3D11RenderTargetView>    m_dx11RT;
    ComPtr<ID3D11DepthStencilView>    m_dx11DSV;
    ComPtr<ID3D11UnorderedAccessView> m_dx11UAV;
};