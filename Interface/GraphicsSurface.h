#pragma once

#include "GraphicsObject.h"

struct GraphicsSurface : public GraphicsObject
{
    virtual ~GraphicsSurface() {}
    virtual void Present() = 0;
};