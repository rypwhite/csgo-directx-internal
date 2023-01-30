#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include <stdexcept>

#include "../source sdk/sdk.h"
#include "../source sdk/rendermanager.h"

#include "../minhook/MinHook.h"
#include "../source sdk/math.h"

namespace hooks {
	void initialise();

	inline unsigned int get_virtual(void* _class, unsigned int index) { 
		return static_cast<unsigned int>((*static_cast<int**>(_class))[index]); 
	}

	using EndScene_t = HRESULT(__thiscall*)(void*, IDirect3DDevice9*);
	HRESULT __stdcall hkEndScene(IDirect3DDevice9* device);
}