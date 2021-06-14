#include "WindowsApplication.h"

void
WindowsApplication::TickFrame()
{}

bool
WindowsApplication::Create(IGraphicsDevice* device, const wchar_t* name, uint32 width, uint32 height)
{
    if (!device) {
        return false;
    }

    m_graphicsDevice.reset(device);

    if (!m_graphicsDevice->Initialize()) {
        return false;
    }

    return true;
}
