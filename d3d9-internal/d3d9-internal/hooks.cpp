#include "hooks.h"

CInterfaces Interfaces;

hooks::EndScene_t endscene_original = nullptr;

//https://learn.microsoft.com/en-us/windows/win32/api/d3d9/nf-d3d9-idirect3ddevice9-endscene
HRESULT __stdcall hooks::hkEndScene(IDirect3DDevice9* device) {
	return endscene_original(nullptr, device);
}

void hooks::initialise() {
	Interfaces.initialise();
	const auto endscene_target = reinterpret_cast<void*>(get_virtual(Interfaces.g_D3DDevice9, 42));

	if (MH_CreateHook(endscene_target, &hkEndScene, reinterpret_cast<void**>(&endscene_original)) != MH_OK)
		throw std::runtime_error("failed to initialize endscene. (outdated index?)");

}