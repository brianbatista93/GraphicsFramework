#pragma once

struct IGraphicsContext
{
    virtual ~IGraphicsContext() {}

    virtual void Finish() = 0;

    virtual void ClearRT(GpuTexture2D* texture, XMVECTOR color) = 0;
    virtual void SetVertexShader(GpuVertexShader* vshader)      = 0;
    virtual void SetPixelShader(GpuPixelShader* pshader)        = 0;
    virtual void SetDomainShader(GpuDomainShader* dshader)      = 0;
    virtual void SetHullShader(GpuHullShader* hshader)          = 0;
    virtual void SetGeometryShader(GpuGeometryShader* gshader)  = 0;
    virtual void SetComputeShader(GpuComputeShader* cshader)    = 0;

    virtual void Draw(uint32 vertexCount, uint32 vertexStart) = 0;
};