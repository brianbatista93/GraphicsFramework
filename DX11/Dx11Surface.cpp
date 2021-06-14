#include "Dx11Surface.h"
#include "Dx11Device.h"
#include "Dx11Resources.h"

Dx11Surface::Dx11Surface(Dx11Device* device, IDXGISwapChain* swapChain)
  : m_swapChain(swapChain)
  , m_images(new Dx11Texture2D(device, swapChain))
{}

Dx11Surface::~Dx11Surface()
{
    delete m_images;
    m_images = nullptr;

    m_swapChain->SetFullscreenState(FALSE, NULL);
    m_swapChain.Reset();
}

void
Dx11Surface::Present()
{
    m_swapChain->Present(0, 0);
}
