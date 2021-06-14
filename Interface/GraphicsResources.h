#pragma once

#include "GraphicsDefinitions.h"
#include <cstdint>

class GpuResource
{
  public:
    virtual ~GpuResource() {}
};

class GpuTexture2D : public GpuResource
{
  public:
    GpuTexture2D(uint32_t width, uint32_t height, EPixelFormat format, uint32_t flags = TEXTURE_FLAG_NONE)
      : m_width(width)
      , m_height(height)
      , m_format(format)
      , m_flags(flags)
    {}

  protected:
    uint32_t     m_width;
    uint32_t     m_height;
    uint32_t     m_flags;
    EPixelFormat m_format;
};