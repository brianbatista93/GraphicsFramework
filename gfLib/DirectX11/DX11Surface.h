#pragma once

#include "DX11Common.h"
#include "Interfaces/IGraphicsSurface.h"

class DX11Surface : public IGraphicsSurface
{
  public:
    DX11Surface(class DX11Device* device, IDXGISwapChain* swapChain);

    ~DX11Surface();

    // Inherited via GraphicsSurface
    virtual void Present() override;

  private:
    ComPtr<IDXGISwapChain> m_swapChain;
    class Dx11Texture2D*   m_images;
};