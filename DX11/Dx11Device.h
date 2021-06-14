#pragma once

#include "Dx11Common.h"
#include "GraphicsDevice.h"

class Dx11Device : public GraphicsDevice
{
  public:
    // Inherited via GraphicsDevice
    virtual bool             Initialize() override;
    virtual void             Shutdown() override;
    virtual GraphicsSurface* CreateSurface(HWND windowHandle) override;

    ComPtr<ID3D11Device>        GetD3D11Device() { return m_d3d11Device; }
    ComPtr<ID3D11DeviceContext> GetD3D11Context() { return m_d3d11Context; }

  private:
    bool CreateDeviceImpl();

  private:
    ComPtr<ID3D11Device>        m_d3d11Device;
    ComPtr<ID3D11DeviceContext> m_d3d11Context;

    D3D_FEATURE_LEVEL m_featureLevel;
};