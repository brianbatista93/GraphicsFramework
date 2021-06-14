#include "pch.h"

#include "Windows/WindowsApplication.h"
#include "DirectX11/DX11Device.h"

int32 main(int32 argc, char* argv[]) {
	std::unique_ptr<IApplication> app;
	app.reset(CreateApplication<WindowsApplication, DX11Device>(L"Test Application", 1280u, 720u));

	while (!app->IsExiting()) {
		app->TickFrame();
	}

	return 0;
}