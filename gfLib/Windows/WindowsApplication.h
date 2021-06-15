#pragma once

#include "Interfaces/IApplication.h"
#include "Interfaces/IGraphicsDevice.h"
#include "Interfaces/IGraphicsSurface.h"
#include <Windows.h>

class WindowsApplication : public IApplication
{
  public:
    ~WindowsApplication();

    bool Create(IGraphicsDevice* device, const wchar_t* name, uint32 width, uint32 height);

    // Inherited via IApplication
    virtual void TickFrame() override;
    virtual bool IsExiting() override { return m_isExiting; }

    constexpr void Exit() { m_isExiting = true; }

    virtual IGraphicsSurface* GetSurface() override { return m_graphicsSurface.get(); }

  private:
    bool BootWindowsApplication();

    void PumpMessages();

  private:
    std::unique_ptr<IGraphicsDevice>  m_graphicsDevice;
    std::unique_ptr<IGraphicsSurface> m_graphicsSurface;
    std::wstring                      m_name;
    uint32                            m_width;
    uint32                            m_height;
    HWND                              m_hwnd;
    bool                              m_isExiting = false;
};