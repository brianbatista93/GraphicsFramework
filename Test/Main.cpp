#include "pch.h"

#include "Windows/WindowsApplication.h"
#include "DirectX11/DX11Device.h"
#include "Interfaces/CommandList.h"
#include "Resources/Shaders.h"
#include "Resources/Texture2D.h"
#include "Resources/ConstantBuffer.h"
#include "Math/Vector3D.h"

int32 main(int32 argc, char* argv[]) {
	std::unique_ptr<IApplication> app;
	app.reset(CreateApplication<WindowsApplication, DX11Device>(L"Test Application", 1280u, 720u));

	app->GetDevice()->SetShaderDir("Shaders/");

	XMVECTOR color = { 1.0f,0.0f,0.0f,1.0f };

	Texture2D* tex = new Texture2D(512, 512, PIXEL_FORMAT_R8G8B8A8_UINT, TEXTURE_FLAG_UNORDERED_ACCESS | TEXTURE_FLAG_SHADER_RESOURCE);

	VertexShader* vshader = new VertexShader("VertexShader.cso");
	PixelShader* pshader = new PixelShader("PixelShader.cso");
	DomainShader* dshader = new DomainShader("DomainShader.cso");
	HullShader* hshader = new HullShader("HullShader.cso");
	GeometryShader* gshader = new GeometryShader("GeometryShader.cso");
	ComputeShader* cshader = new ComputeShader("ComputeShader.cso");
	ConstantBuffer* colorBuffer = new ConstantBuffer(1, sizeof(XMVECTOR), &color);

	cshader->SetUAV(0, tex);

	bool validShaders = vshader->IsValid() && pshader->IsValid() && dshader->IsValid() && hshader->IsValid() && gshader->IsValid() && cshader->IsValid();

	if (!validShaders) {
		return 1;
	}

	gCommandList.SetComputeShader(cshader->GetGpuShader());
	gCommandList.Dispatch(512, 512, 1);
	gCommandList.Finish();

	pshader->SetConstantBuffer(0, colorBuffer);
	pshader->SetTexture2D(0, tex);

	gCommandList.SetVertexShader(vshader->GetGpuShader());
	gCommandList.SetPixelShader(pshader->GetGpuShader());
	// gCommandList.SetDomainShader(dshader->GetGpuShader());
	// gCommandList.SetHullShader(hshader->GetGpuShader());
	// gCommandList.SetGeometryShader(gshader->GetGpuShader());

	gCommandList.SetPrimitiveTopology(PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	gCommandList.SetViewport(0, 0, 1280, 720);
	gCommandList.SetScissor(0, 0, 1280, 720);

	while (!app->IsExiting()) {
		app->TickFrame();

		gCommandList.SetRenderTargetsDepthStencil({ app->GetSurface()->GetBackBuffer() }, nullptr);
		gCommandList.ClearRT(app->GetSurface()->GetBackBuffer(), { 0.25f,0.25f,1.0f,1.0f });
		gCommandList.Draw(3);

		app->GetSurface()->Present();
	}

	return 0;
}