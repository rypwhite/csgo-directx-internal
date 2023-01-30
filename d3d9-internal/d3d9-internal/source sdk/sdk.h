#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <iostream>
#include <stdio.h>
#include <map>
#include <psapi.h>
#include <memory>
#include <vector>

#include <d3d9.h>

#include "classes/IVEngineClient.h"
#include "classes/IClientEntityList.h"

class CInterfaces {
public:
	IDirect3DDevice9* g_D3DDevice9 = nullptr;
	IVEngineClient* g_pEngineClient = nullptr;
	IClientEntityList* g_pEntityList = nullptr;

	void initialise();

	std::uint8_t* scanPattern(void* module, const char* signature);
	void* scanInterface(const char* Module, const char* InterfaceName);
};

extern CInterfaces Interfaces;