#pragma once

#include "GraphicsResources.h"
#include "IGraphicsContext.h"

class CommandList
{
  public:
    void SetGraphicsContext(IGraphicsContext* context) { m_context.reset(context); }

    __forceinline void ClearRT(GpuTexture2D* texture, XMVECTOR color) { m_context->ClearRT(texture, color); }
    __forceinline void SetVertexShader(GpuVertexShader* vshader) { m_context->SetVertexShader(vshader); }
    __forceinline void SetPixelShader(GpuPixelShader* pshader) { m_context->SetPixelShader(pshader); }
    __forceinline void SetDomainShader(GpuDomainShader* dshader) { m_context->SetDomainShader(dshader); }
    __forceinline void SetHullShader(GpuHullShader* hshader) { m_context->SetHullShader(hshader); }
    __forceinline void SetGeometryShader(GpuGeometryShader* gshader) { m_context->SetGeometryShader(gshader); }
    __forceinline void SetComputeShader(GpuComputeShader* cshader) { m_context->SetComputeShader(cshader); }
    __forceinline void Draw(uint32 vertexCount, uint32 vertexStart = 0) { m_context->Draw(vertexCount, vertexStart); }
    __forceinline void SetRenderTargetsDepthStencil(std::vector<GpuTexture2D*> rt, GpuTexture2D* ds)
    {
        m_context->SetRenderTargetsDepthStencil(rt, ds);
    }
    __forceinline void SetViewport(float x, float y, float width, float height, float nearPlane = 0.0f, float farPlane = 1.0f)
    {
        m_context->SetViewport(x, y, width, height, nearPlane, farPlane);
    }
    __forceinline void SetScissor(long left, long top, long right, long bottom) { m_context->SetScissor(left, top, right, bottom); }
    __forceinline void SetPrimitiveTopology(EPrimitiveTopology topology) { m_context->SetPrimitiveTopology(topology); }

    __forceinline void Dispatch(uint32 x, uint32 y, uint32 z) { m_context->Dispatch(x, y, z); }

    __forceinline void Finish() { m_context->Finish(); }

  private:
    std::unique_ptr<IGraphicsContext> m_context;
};

extern CommandList gCommandList;