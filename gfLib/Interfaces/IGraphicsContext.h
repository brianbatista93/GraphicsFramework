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

    virtual void SetPrimitiveTopology(EPrimitiveTopology topology) = 0;

    virtual void Draw(uint32 vertexCount, uint32 vertexStart) = 0;

    virtual void SetRenderTargetsDepthStencil(std::vector<GpuTexture2D*> rt, GpuTexture2D* ds) = 0;

    virtual void SetViewport(float x, float y, float width, float height, float nearPlane = 0.0f, float farPlane = 1.0f) = 0;
    virtual void SetScissor(long left, long top, long right, long bottom)                                                = 0;

    virtual void Dispatch(uint32 x, uint32 y, uint32 z) = 0;
};