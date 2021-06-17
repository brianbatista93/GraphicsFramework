#include "ConstantBuffer.h"
#include "Interfaces/IGraphicsDevice.h"

ConstantBuffer::ConstantBuffer(uint32 elementsCount, uint32 elementStride, const void* data)
{
    m_cBuffer = gGraphicsDevice->CreateConstantBuffer(elementsCount, elementStride, data);
}
