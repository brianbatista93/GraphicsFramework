#include "WindowsApplication.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

void
WindowsApplication::TickFrame()
{
    PumpMessages();

    m_graphicsSurface->Present();
}

bool
WindowsApplication::BootWindowsApplication()
{
    // Register class
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
        wcex.lpszClassName = m_name.c_str();
        wcex.hIconSm       = LoadIcon(wcex.hInstance, IDI_APPLICATION);
        if (!::RegisterClassEx(&wcex)) {
            return false;
        }
    }

    /* Create and Show Window */
    {
        RECT rc = {0, 0, (LONG)m_width, (LONG)m_height};
        AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

        m_hwnd = ::CreateWindow(m_name.c_str(),
                                m_name.c_str(),
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

        SetWindowLongPtr(m_hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));

        ShowWindow(m_hwnd, SW_SHOWDEFAULT);
    }

    return true;
}

void
WindowsApplication::PumpMessages()
{
    MSG msg = {};
    while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

WindowsApplication::~WindowsApplication() { UnregisterClass(m_name.c_str(), GetModuleHandle(NULL)); }

bool
WindowsApplication::Create(IGraphicsDevice* device, const wchar_t* name, uint32 width, uint32 height)
{
    if (!device) {
        return false;
    }

    m_name   = name;
    m_width  = width;
    m_height = height;

    BootWindowsApplication();

    m_graphicsDevice.reset(device);
    if (!m_graphicsDevice->Initialize()) {
        return false;
    }

    m_graphicsSurface.reset(m_graphicsDevice->CreateSurface(m_hwnd, width, height));

    return true;
}

LRESULT CALLBACK
WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static WindowsApplication* application = nullptr;
    switch (message) {
        case WM_SHOWWINDOW: {
            LONG_PTR applicationPtr = GetWindowLongPtr(hWnd, GWLP_USERDATA);
            if (applicationPtr) {
                application = reinterpret_cast<WindowsApplication*>(applicationPtr);
            }
        } break;
        case WM_SIZE: {
            // Emit Resize Event
        } break;
        case WM_CLOSE: {
            application->Exit();
        } break;
        case WM_DESTROY: {
            PostQuitMessage(0);
        } break;
    }

    return DefWindowProc(hWnd, message, wParam, lParam);
}