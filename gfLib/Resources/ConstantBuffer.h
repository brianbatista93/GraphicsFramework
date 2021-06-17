#pragma once

#include "Interfaces/GraphicsResources.h"

class ConstantBuffer
{
  public:
    ConstantBuffer(uint32 elementsCount, uint32 elementStride, const void* data = nullptr);
    ~ConstantBuffer() { SAFE_DELETE(m_cBuffer); }

    constexpr GpuConstantBuffer* GetGpuConstantBuffer() { return m_cBuffer; }

  private:
    GpuConstantBuffer* m_cBuffer;
};