#include "hooks.h"

enum indexes {
	endscene = 0
};
hooks::EndScene_t endscene_original = nullptr;

HRESULT __stdcall hooks::hkEndScene(IDirect3DDevice9* device) {
	return endscene_original(nullptr, device);
}

void hooks::initialise() {
	const auto endscene_target = nullptr;

	if (MH_CreateHook(endscene_target, &hkEndScene, reinterpret_cast<void**>(&endscene_original)) != MH_OK)
		throw std::runtime_error("failed to initialize endscene. (outdated index?)");

}