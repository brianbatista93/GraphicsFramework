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

class GpuShader
{
  public:
    virtual ~GpuShader() {}

    constexpr EShaderStage GetStage() const { return m_stage; }

  protected:
    GpuShader(EShaderStage stage)
      : m_stage(stage)
    {}

  protected:
    EShaderStage m_stage;
};

template<EShaderStage StageType>
class TGpuShader : public GpuShader
{
  public:
    TGpuShader()
      : GpuShader(StageType)
    {}
};

typedef TGpuShader<SHADER_STAGE_VERTEX>   GpuVertexShader;
typedef TGpuShader<SHADER_STAGE_PIXEL>    GpuPixelShader;
typedef TGpuShader<SHADER_STAGE_DOMAIN>   GpuDomainShader;
typedef TGpuShader<SHADER_STAGE_HULL>     GpuHullShader;
typedef TGpuShader<SHADER_STAGE_GEOMETRY> GpuGeometryShader;
typedef TGpuShader<SHADER_STAGE_COMPUTE>  GpuComputeShader;