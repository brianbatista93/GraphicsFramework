#pragma once

#include "DX11Common.h"
#include "Interfaces/IGraphicsDevice.h"

class DX11Device : public IGraphicsDevice
{
  public:
    // Inherited via GraphicsDevice
    virtual bool               Initialize() override;
    virtual void               Shutdown() override;
    virtual IGraphicsSurface*  CreateSurface(void* windowHandle, uint32 width, uint32 height) override;
    virtual IGraphicsContext*  CreateGraphicsContext() override;
    virtual GpuVertexShader*   CreateVertexShader(const std::filesystem::path& filename) override;
    virtual GpuPixelShader*    CreatePixelShader(const std::filesystem::path& filename) override;
    virtual GpuDomainShader*   CreateDomainShader(const std::filesystem::path& filename) override;
    virtual GpuHullShader*     CreateHullShader(const std::filesystem::path& filename) override;
    virtual GpuGeometryShader* CreateGeometryShader(const std::filesystem::path& filename) override;
    virtual GpuComputeShader*  CreateComputeShader(const std::filesystem::path& filename) override;

    ComPtr<ID3D11Device>        GetD3D11Device() { return m_d3d11Device; }
    ComPtr<ID3D11DeviceContext> GetD3D11Context() { return m_d3d11Context; }

  private:
    bool CreateDeviceImpl();
    bool LoadPreCompiledShader(const std::filesystem::path& filename, void** data, uint64* size);

  private:
    ComPtr<ID3D11Device>        m_d3d11Device;
    ComPtr<ID3D11DeviceContext> m_d3d11Context;

    D3D_FEATURE_LEVEL m_featureLevel;
};