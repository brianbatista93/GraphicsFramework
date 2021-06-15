#include "DX11GraphicsContext.h"
#include "DX11Device.h"
#include "Interfaces/CommandList.h"
#include "Interfaces/GraphicsResources.h"
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

void
DX11GraphicsContext::SetVertexShader(GpuVertexShader* vshader)
{
    assert(vshader);

    auto* dx11Shader = dynamic_cast<DX11VertexShader*>(vshader);
    assert(dx11Shader);
    auto d3d11Shader = dx11Shader->GetDx11Shader();

    m_d3d11Context->VSSetShader(d3d11Shader.Get(), nullptr, 0);
}

void
DX11GraphicsContext::SetPixelShader(GpuPixelShader* pshader)
{
    assert(pshader);

    auto* dx11Shader = dynamic_cast<DX11PixelShader*>(pshader);
    assert(dx11Shader);
    auto d3d11Shader = dx11Shader->GetDx11Shader();

    m_d3d11Context->PSSetShader(d3d11Shader.Get(), nullptr, 0);
}

void
DX11GraphicsContext::SetDomainShader(GpuDomainShader* dshader)
{
    assert(dshader);

    auto* dx11Shader = dynamic_cast<DX11DomainShader*>(dshader);
    assert(dx11Shader);
    auto d3d11Shader = dx11Shader->GetDx11Shader();

    m_d3d11Context->DSSetShader(d3d11Shader.Get(), nullptr, 0);
}

void
DX11GraphicsContext::SetHullShader(GpuHullShader* hshader)
{
    assert(hshader);

    auto* dx11Shader = dynamic_cast<DX11HullShader*>(hshader);
    assert(dx11Shader);
    auto d3d11Shader = dx11Shader->GetDx11Shader();

    m_d3d11Context->HSSetShader(d3d11Shader.Get(), nullptr, 0);
}

void
DX11GraphicsContext::SetGeometryShader(GpuGeometryShader* gshader)
{
    assert(gshader);

    auto* dx11Shader = dynamic_cast<DX11GeometryShader*>(gshader);
    assert(dx11Shader);
    auto d3d11Shader = dx11Shader->GetDx11Shader();

    m_d3d11Context->GSSetShader(d3d11Shader.Get(), nullptr, 0);
}

void
DX11GraphicsContext::SetComputeShader(GpuComputeShader* cshader)
{
    assert(cshader);

    auto* dx11Shader = dynamic_cast<DX11ComputeShader*>(cshader);
    assert(dx11Shader);
    auto d3d11Shader = dx11Shader->GetDx11Shader();

    m_d3d11Context->CSSetShader(d3d11Shader.Get(), nullptr, 0);
}

void
DX11GraphicsContext::Draw(uint32 vertexCount, uint32 vertexStart)
{
    m_d3d11Context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    m_d3d11Context->Draw(vertexCount, vertexStart);
}
