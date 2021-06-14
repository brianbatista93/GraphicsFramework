#include "Dx11Device.h"
#include "WindowsApplication.h"

int
main(int argc, char* argv[])
{
    WindowsApplication app;
    app.Create<Dx11Device>(L"Test Application", 1280, 720);
    while (!app.IsExiting())
        app.RunFrame();

    return 0;
}