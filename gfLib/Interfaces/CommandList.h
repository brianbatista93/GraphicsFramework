#pragma once

#include "GraphicsResources.h"
#include "IGraphicsContext.h"

class CommandList
{
  public:
    void SetGraphicsContext(IGraphicsContext* context) { m_context.reset(context); }

    void ClearRT(GpuTexture2D* texture, XMVECTOR color) { m_context->ClearRT(texture, color); }

  private:
    std::unique_ptr<IGraphicsContext> m_context;
};

extern CommandList gCommandList;