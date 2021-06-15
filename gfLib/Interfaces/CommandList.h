#pragma once

#include "GraphicsResources.h"
#include "IGraphicsContext.h"

class CommandList
{
  public:
    void SetGraphicsContext(IGraphicsContext* context) { m_context.reset(context); }

    void ClearRT(GpuTexture2D* texture, XMVECTOR color) { m_context->ClearRT(texture, color); }
    void SetVertexShader(GpuVertexShader* vshader) { m_context->SetVertexShader(vshader); }
    void SetPixelShader(GpuPixelShader* pshader) { m_context->SetPixelShader(pshader); }
    void SetDomainShader(GpuDomainShader* dshader) { m_context->SetDomainShader(dshader); }
    void SetHullShader(GpuHullShader* hshader) { m_context->SetHullShader(hshader); }
    void SetGeometryShader(GpuGeometryShader* gshader) { m_context->SetGeometryShader(gshader); }
    void SetComputeShader(GpuComputeShader* cshader) { m_context->SetComputeShader(cshader); }
    void Draw(uint32 vertexCount, uint32 vertexStart = 0) { m_context->Draw(vertexCount, vertexStart); }

  private:
    std::unique_ptr<IGraphicsContext> m_context;
};

extern CommandList gCommandList;