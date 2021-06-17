#pragma once

#include "Interfaces/GraphicsResources.h"
#include "Interfaces/IGraphicsDevice.h"

template<class ShaderType>
class TShader
{
  public:
    TShader(const std::filesystem::path& filename) { m_shader = gGraphicsDevice->CreateShader<ShaderType>(filename); }

    ~TShader() { SAFE_DELETE(m_shader); }

    constexpr bool IsValid() const { return m_shader != nullptr; }

    constexpr ShaderType* GetGpuShader() { return m_shader; }

    __forceinline void SetConstantBuffer(uint32 index, class ConstantBuffer* buffer)
    {
        assert(buffer);
        m_shader->SetConstantBuffer(index, buffer);
    }

    __forceinline void SetTexture2D(uint32 index, class Texture2D* tex2D)
    {
        assert(tex2D);
        m_shader->SetTexture2D(index, tex2D);
    }

  protected:
    ShaderType* m_shader;
};

class ComputeShader : public TShader<GpuComputeShader>
{
  public:
    ComputeShader(const std::filesystem::path& filename)
      : TShader<GpuComputeShader>::TShader(filename)
    {}

    __forceinline void SetUAV(uint32 index, class Texture2D* tex2D)
    {
        assert(tex2D);
        m_shader->SetUAV(index, tex2D);
    }
};

using VertexShader   = TShader<GpuVertexShader>;
using PixelShader    = TShader<GpuPixelShader>;
using DomainShader   = TShader<GpuDomainShader>;
using HullShader     = TShader<GpuHullShader>;
using GeometryShader = TShader<GpuGeometryShader>;
