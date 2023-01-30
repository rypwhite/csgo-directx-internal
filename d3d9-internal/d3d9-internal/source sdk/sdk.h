#pragma once
#include <windows.h>
#include <iostream>
#include <stdio.h>
#include <map>
#include <psapi.h>
#include <memory>
#include <vector>

#include <d3d9.h>

#include "classes/IVEngineClient.h"

class CInterfaces {
public:
	IDirect3DDevice9* g_D3DDevice9 = nullptr;
	IVEngineClient* g_pEngineClient = nullptr;

	void initialise();
	std::uint8_t* pattern(void* module, const char* signature);
};

extern CInterfaces Interfaces;