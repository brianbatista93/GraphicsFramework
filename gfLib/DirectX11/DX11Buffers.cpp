#include "DX11Device.h"
#include "DX11Resources.h"

DX11ConstantBuffer::DX11ConstantBuffer(DX11Device* device, uint32 elementsCount, uint32 elementStride, const void* data)
  : m_device(device)
  , GpuConstantBuffer(elementsCount, elementStride)
{
    const uint32 byteWidth = elementsCount * elementStride;

    D3D11_BUFFER_DESC bufferDesc {
      .ByteWidth           = byteWidth,
      .Usage               = data ? D3D11_USAGE_DEFAULT : D3D11_USAGE_DYNAMIC,
      .BindFlags           = D3D11_BIND_CONSTANT_BUFFER,
      .CPUAccessFlags      = data ? 0u : D3D11_CPU_ACCESS_WRITE,
      .MiscFlags           = 0,
      .StructureByteStride = 0,
    };

    D3D11_SUBRESOURCE_DATA  subResData;
    D3D11_SUBRESOURCE_DATA* subResDataPtr = nullptr;

    if (data) {
        subResData = {
          .pSysMem          = data,
          .SysMemPitch      = 0,
          .SysMemSlicePitch = 0,
        };

        subResDataPtr = &subResData;
    }

    ThrowIfFailed(m_device->GetD3D11Device()->CreateBuffer(&bufferDesc, subResDataPtr, &m_buffer));
}

GpuConstantBuffer*
DX11Device::CreateConstantBuffer(uint32 elementsCount, uint32 elementStride, const void* data)
{
    assert(elementsCount);
    assert(elementStride);

    return new DX11ConstantBuffer(this, elementsCount, elementStride, data);
}

GpuTexture2D*
DX11Device::CreateTexture2D(uint32 width, uint32 height, EPixelFormat format, ETextureFlags flags)
{
    assert(width);
    assert(height);

    return new DX11Texture2D(this, width, height, format, flags);
}
