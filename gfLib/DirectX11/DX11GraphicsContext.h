#pragma once

#include "DX11Common.h"
#include "DX11Resources.h"
#include "Interfaces/IGraphicsContext.h"

class DX11GraphicsContext : public IGraphicsContext
{
  public:
    DX11GraphicsContext(class DX11Device* device);

    // Inherited via IGraphicsContext
    virtual void ClearRT(GpuTexture2D* texture, XMVECTOR color) override;
    virtual void Finish() override;

  private:
    class DX11Device*           m_device;
    ComPtr<ID3D11Device>        m_d3d11Device;
    ComPtr<ID3D11DeviceContext> m_d3d11Context;
};