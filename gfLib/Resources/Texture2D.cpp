#include "Texture2D.h"
#include "Interfaces/IGraphicsDevice.h"
#include "pch.h"

Texture2D::Texture2D(uint32 width, uint32 height, EPixelFormat format, uint32 flags)
{
    m_gpuTexture = gGraphicsDevice->CreateTexture2D(width, height, format, (ETextureFlags)flags);
}
