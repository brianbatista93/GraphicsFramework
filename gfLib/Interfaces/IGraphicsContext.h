#pragma once

struct IGraphicsContext
{
    virtual ~IGraphicsContext() {}

    virtual void ClearRT(GpuTexture2D* texture, XMVECTOR color) = 0;
    virtual void Finish()                                       = 0;
};