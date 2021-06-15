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

  private:
    ShaderType* m_shader;
};

using VertexShader   = TShader<GpuVertexShader>;
using PixelShader    = TShader<GpuPixelShader>;
using DomainShader   = TShader<GpuDomainShader>;
using HullShader     = TShader<GpuHullShader>;
using GeometryShader = TShader<GpuGeometryShader>;
using ComputeShader  = TShader<GpuComputeShader>;