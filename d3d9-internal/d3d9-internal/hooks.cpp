#include "hooks.h"

CInterfaces Interfaces;

hooks::EndScene_t endscene_original = nullptr;

//https://learn.microsoft.com/en-us/windows/win32/api/d3d9/nf-d3d9-idirect3ddevice9-endscene
HRESULT __stdcall hooks::hkEndScene(IDirect3DDevice9* device) {
	IDirect3DVertexDeclaration9* vert_declaration;
	IDirect3DVertexShader9* vert_shader;
	DWORD old_d3drs_colorwriteenable;

	//https://www.unknowncheats.me/forum/counterstrike-global-offensive/292735-panorama-proper-rendering-fix.html
	// Save State
	device->GetRenderState(D3DRS_COLORWRITEENABLE, &old_d3drs_colorwriteenable);
	device->GetVertexDeclaration(&vert_declaration);
	device->GetVertexShader(&vert_shader);

	device->SetRenderState(D3DRS_COLORWRITEENABLE, 0xffffffff);
	device->SetRenderState(D3DRS_SRGBWRITEENABLE, false);
	device->SetSamplerState(NULL, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	device->SetSamplerState(NULL, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
	device->SetSamplerState(NULL, D3DSAMP_ADDRESSW, D3DTADDRESS_WRAP);
	device->SetSamplerState(NULL, D3DSAMP_SRGBTEXTURE, NULL);

	//surface is ready for rendering

	//https://www.unknowncheats.me/forum/counterstrike-global-offensive/292735-panorama-proper-rendering-fix.html
	// Restore State
	device->SetRenderState(D3DRS_COLORWRITEENABLE, old_d3drs_colorwriteenable);
	device->SetRenderState(D3DRS_SRGBWRITEENABLE, true);
	device->SetVertexDeclaration(vert_declaration);
	device->SetVertexShader(vert_shader);

	return endscene_original(Interfaces.g_D3DDevice9, device);
}

void hooks::initialise() {
	Interfaces.initialise();
	const auto endscene_target = reinterpret_cast<void*>(get_virtual(Interfaces.g_D3DDevice9, 42));

	if (MH_CreateHook(endscene_target, &hkEndScene, reinterpret_cast<void**>(&endscene_original)) != MH_OK)
		throw std::runtime_error("failed to initialize endscene. (outdated index?)");

}