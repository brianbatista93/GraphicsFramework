#include "DX11GraphicsContext.h"
#include "DX11Device.h"
#include "Interfaces/CommandList.h"
#include "pch.h"

CommandList gCommandList;

DX11GraphicsContext::DX11GraphicsContext(DX11Device* device)
  : m_device(device)
  , m_d3d11Device(device->GetD3D11Device())
  , m_d3d11Context(device->GetD3D11Context())
{}

void
DX11GraphicsContext::ClearRT(GpuTexture2D* texture, XMVECTOR color)
{
    DX11Texture2D* dxTexture = dynamic_cast<DX11Texture2D*>(texture);
    assert(dxTexture);
    auto rtView = dxTexture->GetDx11RT();
    assert(rtView);
    m_d3d11Context->ClearRenderTargetView(rtView.Get(), &color.m128_f32[0]);
}

void
DX11GraphicsContext::Finish()
{
    m_d3d11Context->ClearState();
}
