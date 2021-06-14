#pragma once

#include "Dx11Common.h"
#include "GraphicsSurface.h"

class Dx11Surface : public GraphicsSurface
{
  public:
    Dx11Surface(class Dx11Device* device, IDXGISwapChain* swapChain);

    ~Dx11Surface();

    // Inherited via GraphicsSurface
    virtual void Present() override;

  private:
    ComPtr<IDXGISwapChain> m_swapChain;
    class Dx11Texture2D*   m_images;
};