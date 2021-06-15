#pragma once

#include "Interfaces/GraphicsResources.h"

class Texture2D
{
  public:
    Texture2D() {}

    ~Texture2D() { SAFE_DELETE(m_gpuTexture); }

  private:
    GpuTexture2D* m_gpuTexture;
};