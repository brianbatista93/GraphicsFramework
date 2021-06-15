#include "DX11Surface.h"
#include "DX11Resources.h"
#include "pch.h"

DX11Surface::DX11Surface(DX11Device* device, IDXGISwapChain* swapChain)
  : m_swapChain(swapChain)
  , m_images(new DX11Texture2D(device, swapChain))

{}

DX11Surface::~DX11Surface()
{
    SAFE_DELETE(m_images);

    m_swapChain->SetFullscreenState(FALSE, NULL);
    m_swapChain.Reset();
}

void
DX11Surface::Present()
{
    m_swapChain->Present(0, 0);
}

GpuTexture2D*
DX11Surface::GetBackBuffer()
{
    return m_images;
}
