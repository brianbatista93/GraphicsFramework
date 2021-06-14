#pragma once

#include "Interfaces/IApplication.h"
#include "Interfaces/IGraphicsDevice.h"

class WindowsApplication : public IApplication
{
  public:
    bool Create(IGraphicsDevice* device, const wchar_t* name, uint32 width, uint32 height);

    // Inherited via IApplication
    virtual void TickFrame() override;
    virtual bool IsExiting() override { return false; }

  private:
    std::unique_ptr<IGraphicsDevice> m_graphicsDevice;
};