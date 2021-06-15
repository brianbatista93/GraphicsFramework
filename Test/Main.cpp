#include "pch.h"

#include "Windows/WindowsApplication.h"
#include "DirectX11/DX11Device.h"
#include "Interfaces/CommandList.h"
#include "Resources/Shaders.h"

int32 main(int32 argc, char* argv[]) {
	std::unique_ptr<IApplication> app;
	app.reset(CreateApplication<WindowsApplication, DX11Device>(L"Test Application", 1280u, 720u));

	app->GetDevice()->SetShaderDir("Shaders/");

	VertexShader* vshader = new VertexShader("VertexShader.cso");
	PixelShader* pshader = new PixelShader("PixelShader.cso");
	DomainShader* dshader = new DomainShader("DomainShader.cso");
	HullShader* hshader = new HullShader("HullShader.cso");
	GeometryShader* gshader = new GeometryShader("GeometryShader.cso");
	ComputeShader* cshader = new ComputeShader("ComputeShader.cso");

	bool validShaders = vshader->IsValid() && pshader->IsValid() && dshader->IsValid() && hshader->IsValid() && gshader->IsValid() && cshader->IsValid();

	if (!validShaders) { return 1; }

	while (!app->IsExiting()) {
		app->TickFrame();

		gCommandList.ClearRT(app->GetSurface()->GetBackBuffer(), { 0.25f,0.25f,1.0f,1.0f });
		gCommandList.SetVertexShader(vshader->GetGpuShader());
		gCommandList.SetPixelShader(pshader->GetGpuShader());
		// gCommandList.SetDomainShader(dshader->GetGpuShader());
		// gCommandList.SetHullShader(hshader->GetGpuShader());
		// gCommandList.SetGeometryShader(gshader->GetGpuShader());

		// gCommandList.SetTopology();

		gCommandList.Draw(3);

		app->GetSurface()->Present();
	}

	return 0;
}