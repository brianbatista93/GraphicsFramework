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

class DX11Shader
{};

class DX11VertexShader
  : public DX11Shader
  , public GpuVertexShader
{
  public:
    DX11VertexShader(ID3D11VertexShader* shader, const void* blob, uint64 size)
      : m_vshader(shader)
      , m_blob(reinterpret_cast<const uint8*>(blob), reinterpret_cast<const uint8*>(blob) + size)
    {}

    ComPtr<ID3D11VertexShader> GetDx11Shader() const { return m_vshader; }

  private:
    ComPtr<ID3D11VertexShader> m_vshader;
    std::vector<uint8>         m_blob;
};

class DX11PixelShader
  : public DX11Shader
  , public GpuPixelShader
{
  public:
    DX11PixelShader(ID3D11PixelShader* shader)
      : m_pshader(shader)
    {}

    ComPtr<ID3D11PixelShader> GetDx11Shader() const { return m_pshader; }

  private:
    ComPtr<ID3D11PixelShader> m_pshader;
};

class DX11DomainShader
  : public DX11Shader
  , public GpuDomainShader
{
  public:
    DX11DomainShader(ID3D11DomainShader* shader)
      : m_dshader(shader)
    {}

    ComPtr<ID3D11DomainShader> GetDx11Shader() const { return m_dshader; }

  private:
    ComPtr<ID3D11DomainShader> m_dshader;
};

class DX11HullShader
  : public DX11Shader
  , public GpuHullShader
{
  public:
    DX11HullShader(ID3D11HullShader* shader)
      : m_hshader(shader)
    {}

    ComPtr<ID3D11HullShader> GetDx11Shader() const { return m_hshader; }

  private:
    ComPtr<ID3D11HullShader> m_hshader;
};

class DX11GeometryShader
  : public DX11Shader
  , public GpuGeometryShader
{
  public:
    DX11GeometryShader(ID3D11GeometryShader* shader)
      : m_gshader(shader)
    {}

    ComPtr<ID3D11GeometryShader> GetDx11Shader() const { return m_gshader; }

  private:
    ComPtr<ID3D11GeometryShader> m_gshader;
};

class DX11ComputeShader
  : public DX11Shader
  , public GpuComputeShader
{
  public:
    DX11ComputeShader(ID3D11ComputeShader* shader)
      : m_cshader(shader)
    {}

    ComPtr<ID3D11ComputeShader> GetDx11Shader() const { return m_cshader; }

  private:
    ComPtr<ID3D11ComputeShader> m_cshader;
};