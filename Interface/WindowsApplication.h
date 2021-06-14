#pragma once

#include "GraphicsDevice.h"
#include "GraphicsSurface.h"
#include <iostream>
#include <memory>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

class WindowsApplication
{
  public:
    inline static bool sIsExiting = false;

    template<class GraphicsDeviceType>
    bool Create(const wchar_t* name, int width, int height)
    {
        {
            WNDCLASSEX wcex;
            wcex.cbSize        = sizeof(WNDCLASSEX);
            wcex.style         = CS_HREDRAW | CS_VREDRAW;
            wcex.lpfnWndProc   = WndProc;
            wcex.cbClsExtra    = 0;
            wcex.cbWndExtra    = 0;
            wcex.hInstance     = GetModuleHandle(NULL);
            wcex.hIcon         = LoadIcon(wcex.hInstance, IDI_APPLICATION);
            wcex.hCursor       = LoadCursor(nullptr, IDC_ARROW);
            wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
            wcex.lpszMenuName  = nullptr;
            wcex.lpszClassName = name;
            wcex.hIconSm       = LoadIcon(wcex.hInstance, IDI_APPLICATION);
            if (!::RegisterClassEx(&wcex)) {
                return false;
            }
        }

        /* Create and Show Window */
        {
            m_displayWidth  = width;
            m_displayHeight = height;

            RECT rc = {0, 0, (LONG)m_displayWidth, (LONG)m_displayHeight};
            AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

            m_hwnd = ::CreateWindow(name,
                                    name,
                                    WS_OVERLAPPEDWINDOW,
                                    CW_USEDEFAULT,
                                    CW_USEDEFAULT,
                                    rc.right - rc.left,
                                    rc.bottom - rc.top,
                                    nullptr,
                                    nullptr,
                                    GetModuleHandle(NULL),
                                    nullptr);
            if (m_hwnd == NULL) {
                return false;
            }

            ShowWindow(m_hwnd, SW_SHOWDEFAULT);
        }

        {
            m_graphicsDevice = std::make_unique<GraphicsDeviceType>();
            if (!m_graphicsDevice->Initialize()) {
                std::cout << "Could not initialize DirectX 11 graphics interce." << std::endl;
                std::cout << m_graphicsDevice->GetErrorMessage() << std::endl;
                return false;
            }

            m_graphicsSurface.reset(m_graphicsDevice->CreateSurface(m_hwnd));
        }

        sIsExiting = false;

        return true;
    }

    void RunFrame()
    {
        MSG msg = {};
        while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        m_graphicsSurface->Present();
    }

    constexpr bool IsExiting() const { return WindowsApplication::sIsExiting; }

    ~WindowsApplication()
    {
        m_graphicsDevice->Shutdown();
        DestroyWindow(m_hwnd);
    }

  private:
    int                              m_displayWidth;
    int                              m_displayHeight;
    HWND                             m_hwnd;
    std::unique_ptr<GraphicsDevice>  m_graphicsDevice;
    std::unique_ptr<GraphicsSurface> m_graphicsSurface;
};

LRESULT CALLBACK
WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message) {
        case WM_SIZE: {
            // Emit Resize Event
        } break;
        case WM_CLOSE: {
            WindowsApplication::sIsExiting = true;
        } break;
        case WM_DESTROY: {
            PostQuitMessage(0);
        } break;
    }

    return DefWindowProc(hWnd, message, wParam, lParam);
}