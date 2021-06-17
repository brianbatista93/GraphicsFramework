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
    GpuTexture2D(uint32 width, uint32 height, EPixelFormat format, uint32 flags = TEXTURE_FLAG_NONE)
      : m_width(width)
      , m_height(height)
      , m_format(format)
      , m_flags(flags)
    {}

    constexpr uint32       GetWidth() const { return m_width; }
    constexpr uint32       GetHeight() const { return m_height; }
    constexpr uint32       GetFlags() const { return m_flags; }
    constexpr EPixelFormat GetFormat() const { return m_format; }

  protected:
    uint32       m_width;
    uint32       m_height;
    uint32       m_flags;
    EPixelFormat m_format;
};

class GpuConstantBuffer : public GpuResource
{
  public:
    GpuConstantBuffer(uint32 elementsCount, uint32 elementStride)
      : m_elementsCount(elementsCount)
      , m_elementStride(elementStride)
    {}

    constexpr uint32 GetElementsCount() const { return m_elementsCount; }
    constexpr uint32 GetElementStride() const { return m_elementStride; }

  protected:
    uint32 m_elementsCount;
    uint32 m_elementStride;
};

class GpuShader
{
  public:
    virtual ~GpuShader() {}

    constexpr EShaderStage GetStage() const { return m_stage; }

    virtual void SetConstantBuffer(uint32 index, class ConstantBuffer* buffer) {}
    virtual void SetTexture2D(uint32 index, class Texture2D* tex2D) {}

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

class GpuComputeShader : public TGpuShader<SHADER_STAGE_COMPUTE>
{
  public:
    virtual void SetUAV(uint32 index, class Texture2D* tex2D) {}
};

typedef TGpuShader<SHADER_STAGE_VERTEX>   GpuVertexShader;
typedef TGpuShader<SHADER_STAGE_PIXEL>    GpuPixelShader;
typedef TGpuShader<SHADER_STAGE_DOMAIN>   GpuDomainShader;
typedef TGpuShader<SHADER_STAGE_HULL>     GpuHullShader;
typedef TGpuShader<SHADER_STAGE_GEOMETRY> GpuGeometryShader;
