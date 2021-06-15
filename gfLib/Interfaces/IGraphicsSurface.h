#pragma once

#include "IGraphicsObject.h"

struct IGraphicsSurface : public IGraphicsObject
{
    virtual ~IGraphicsSurface() {}
    virtual void                 Present()       = 0;
    virtual class GpuTexture2D* GetBackBuffer() = 0;
};