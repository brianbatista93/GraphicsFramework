#pragma once

#include "Interfaces/GraphicsResources.h"
#include "Math/Color.h"

class Texture2D
{
  public:
    Texture2D(uint32 width, uint32 height, EPixelFormat format, uint32 flags = TEXTURE_FLAG_NONE);

    ~Texture2D() { SAFE_DELETE(m_gpuTexture); }

    constexpr GpuTexture2D* GetGpuTexture2D() { return m_gpuTexture; }
    constexpr uint32        GetFlags() const { return m_gpuTexture->GetFlags(); }

    void SetPixelRow(uint32 rowIndex, const Color* color);

  private:
    GpuTexture2D* m_gpuTexture;
};