#include "pch.h"

#include "Windows/WindowsApplication.h"
#include "DirectX11/DX11Device.h"
#include "Interfaces/CommandList.h"

int32 main(int32 argc, char* argv[]) {
	std::unique_ptr<IApplication> app;
	app.reset(CreateApplication<WindowsApplication, DX11Device>(L"Test Application", 1280u, 720u));

	while (!app->IsExiting()) {
		app->TickFrame();

		gCommandList.ClearRT(app->GetSurface()->GetBackBuffer(), { 0.25f,0.25f,1.0f,1.0f });

		app->GetSurface()->Present();
	}

	return 0;
}