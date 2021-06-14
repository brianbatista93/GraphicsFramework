#include "DX11Surface.h"
#include "pch.h"

DX11Surface::DX11Surface(DX11Device* device, IDXGISwapChain* swapChain)
  : m_swapChain(swapChain)
{}

DX11Surface::~DX11Surface()
{
    m_swapChain->SetFullscreenState(FALSE, NULL);
    m_swapChain.Reset();
}

void
DX11Surface::Present()
{
    m_swapChain->Present(0, 0);
}
