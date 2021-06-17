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
    virtual void SetVertexShader(GpuVertexShader* vshader) override;
    virtual void SetPixelShader(GpuPixelShader* pshader) override;
    virtual void SetDomainShader(GpuDomainShader* dshader) override;
    virtual void SetHullShader(GpuHullShader* hshader) override;
    virtual void SetGeometryShader(GpuGeometryShader* gshader) override;
    virtual void SetComputeShader(GpuComputeShader* cshader) override;
    virtual void Draw(uint32 vertexCount, uint32 vertexStart) override;
    virtual void SetRenderTargetsDepthStencil(std::vector<GpuTexture2D*> rt, GpuTexture2D* ds) override;
    virtual void SetViewport(float x, float y, float width, float height, float nearPlane, float farPlane) override;
    virtual void SetScissor(long left, long top, long right, long bottom) override;
    virtual void SetPrimitiveTopology(EPrimitiveTopology topology) override;
    virtual void Dispatch(uint32 x, uint32 y, uint32 z) override;

  private:
    class DX11Device*           m_device;
    ComPtr<ID3D11Device>        m_d3d11Device;
    ComPtr<ID3D11DeviceContext> m_d3d11Context;
};