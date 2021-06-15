#pragma once

#include "DX11Common.h"
#include "Interfaces/IGraphicsDevice.h"

class DX11Device : public IGraphicsDevice
{
  public:
    // Inherited via GraphicsDevice
    virtual bool              Initialize() override;
    virtual void              Shutdown() override;
    virtual IGraphicsSurface* CreateSurface(void* windowHandle, uint32 width, uint32 height) override;
    virtual IGraphicsContext* CreateGraphicsContext() override;

    ComPtr<ID3D11Device>        GetD3D11Device() { return m_d3d11Device; }
    ComPtr<ID3D11DeviceContext> GetD3D11Context() { return m_d3d11Context; }

  private:
    bool CreateDeviceImpl();

  private:
    ComPtr<ID3D11Device>        m_d3d11Device;
    ComPtr<ID3D11DeviceContext> m_d3d11Context;

    D3D_FEATURE_LEVEL m_featureLevel;
};