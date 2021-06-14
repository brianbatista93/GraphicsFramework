#pragma once

#include "GraphicsObject.h"
#include <Windows.h>

struct GraphicsDevice : public GraphicsObject
{
    virtual ~GraphicsDevice() {}

    /**
	 * @brief Initialize the graphics device.
	 * Note that it is the full initialization including the swapchain.
	 * @See GetErrorMessage
	 * @return True if successfully initialized. False otherwise.
	*/
    virtual bool Initialize() = 0;

    /**
	 * @brief Shuts down and destroy all device related objects.
	*/
    virtual void Shutdown() = 0;

    virtual struct GraphicsSurface* CreateSurface(HWND windowHandle) = 0;
};