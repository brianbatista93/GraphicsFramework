#pragma once

#include "Dx11Common.h"
#include "Interfaces/GraphicsResources.h"
#include "Math/Color.h"

class DX11Texture2D : public GpuTexture2D
{
  public:
    DX11Texture2D(class DX11Device* device, IDXGISwapChain* swapChain);

    DX11Texture2D(class DX11Device* device, uint32 width, uint32 height, EPixelFormat format, ETextureFlags flags);

    ~DX11Texture2D() { m_device = nullptr; }

    ComPtr<ID3D11Texture2D>           GetDx11Texture() { return m_dx11Texture; }
    ComPtr<ID3D11ShaderResourceView>  GetDx11SRV() { return m_dx11SRV; }
    ComPtr<ID3D11RenderTargetView>    GetDx11RT() { return m_dx11RT; }
    ComPtr<ID3D11DepthStencilView>    GetDx11DSV() { return m_dx11DSV; }
    ComPtr<ID3D11UnorderedAccessView> GetDx11UAV() { return m_dx11UAV; }

    virtual void SetPixelRow(uint32 rowIndex, const Color* color) override;

  private:
    void CreateViews();

  private:
    class DX11Device*                 m_device;
    ComPtr<ID3D11Texture2D>           m_dx11Texture;
    ComPtr<ID3D11ShaderResourceView>  m_dx11SRV;
    ComPtr<ID3D11RenderTargetView>    m_dx11RT;
    ComPtr<ID3D11DepthStencilView>    m_dx11DSV;
    ComPtr<ID3D11UnorderedAccessView> m_dx11UAV;
    D3D11_MAPPED_SUBRESOURCE          m_mappedSubRes;
};

class DX11ConstantBuffer : public GpuConstantBuffer
{
  public:
    DX11ConstantBuffer(class DX11Device* device, uint32 elementsCount, uint32 elementStride, const void* data);

    ComPtr<ID3D11Buffer> GetD3D11Buffer() { return m_buffer; }

  private:
    class DX11Device*    m_device;
    ComPtr<ID3D11Buffer> m_buffer;
};

class DX11Shader
{
  protected:
    DX11Shader(class DX11Device* device)
      : m_device(device)
    {}

  protected:
    class DX11Device* m_device;
};

class DX11VertexShader
  : public DX11Shader
  , public GpuVertexShader
{
  public:
    DX11VertexShader(class DX11Device* device, ID3D11VertexShader* shader, const void* blob, uint64 size)
      : DX11Shader(device)
      , m_vshader(shader)
      , m_blob(reinterpret_cast<const uint8*>(blob), reinterpret_cast<const uint8*>(blob) + size)
    {}

    ComPtr<ID3D11VertexShader> GetDx11Shader() const { return m_vshader; }

    virtual void SetConstantBuffer(uint32 index, class ConstantBuffer* buffer) override;

    virtual void SetTexture2D(uint32 index, class Texture2D* tex2D) override;

  private:
    ComPtr<ID3D11VertexShader> m_vshader;
    std::vector<uint8>         m_blob;
};

class DX11PixelShader
  : public DX11Shader
  , public GpuPixelShader
{
  public:
    DX11PixelShader(class DX11Device* device, ID3D11PixelShader* shader)
      : DX11Shader(device)
      , m_pshader(shader)
    {}

    ComPtr<ID3D11PixelShader> GetDx11Shader() const { return m_pshader; }

    virtual void SetConstantBuffer(uint32 index, class ConstantBuffer* buffer) override;

    virtual void SetTexture2D(uint32 index, class Texture2D* tex2D) override;

  private:
    ComPtr<ID3D11PixelShader> m_pshader;
};

class DX11DomainShader
  : public DX11Shader
  , public GpuDomainShader
{
  public:
    DX11DomainShader(class DX11Device* device, ID3D11DomainShader* shader)
      : DX11Shader(device)
      , m_dshader(shader)
    {}

    ComPtr<ID3D11DomainShader> GetDx11Shader() const { return m_dshader; }

    virtual void SetConstantBuffer(uint32 index, class ConstantBuffer* buffer) override;

    virtual void SetTexture2D(uint32 index, class Texture2D* tex2D) override;

  private:
    ComPtr<ID3D11DomainShader> m_dshader;
};

class DX11HullShader
  : public DX11Shader
  , public GpuHullShader
{
  public:
    DX11HullShader(class DX11Device* device, ID3D11HullShader* shader)
      : DX11Shader(device)
      , m_hshader(shader)
    {}

    ComPtr<ID3D11HullShader> GetDx11Shader() const { return m_hshader; }

    virtual void SetConstantBuffer(uint32 index, class ConstantBuffer* buffer) override;

    virtual void SetTexture2D(uint32 index, class Texture2D* tex2D) override;

  private:
    ComPtr<ID3D11HullShader> m_hshader;
};

class DX11GeometryShader
  : public DX11Shader
  , public GpuGeometryShader
{
  public:
    DX11GeometryShader(class DX11Device* device, ID3D11GeometryShader* shader)
      : DX11Shader(device)
      , m_gshader(shader)
    {}

    ComPtr<ID3D11GeometryShader> GetDx11Shader() const { return m_gshader; }

    virtual void SetConstantBuffer(uint32 index, class ConstantBuffer* buffer) override;

    virtual void SetTexture2D(uint32 index, class Texture2D* tex2D) override;

  private:
    ComPtr<ID3D11GeometryShader> m_gshader;
};

class DX11ComputeShader
  : public DX11Shader
  , public GpuComputeShader
{
  public:
    DX11ComputeShader(class DX11Device* device, ID3D11ComputeShader* shader)
      : DX11Shader(device)
      , m_cshader(shader)
    {}

    ComPtr<ID3D11ComputeShader> GetDx11Shader() const { return m_cshader; }

    virtual void SetConstantBuffer(uint32 index, class ConstantBuffer* buffer) override;

    virtual void SetTexture2D(uint32 index, class Texture2D* tex2D) override;

    virtual void SetUAV(uint32 index, class Texture2D* tex2D) override;

  private:
    ComPtr<ID3D11ComputeShader> m_cshader;
};