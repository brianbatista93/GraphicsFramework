#pragma once

#include "IGraphicsObject.h"

struct IGraphicsDevice : public IGraphicsObject
{
	virtual ~IGraphicsDevice() {}

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
};