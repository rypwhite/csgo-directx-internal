#include "sdk.h"

void CInterfaces::initialise() {

	g_D3DDevice9 = **(IDirect3DDevice9***)(scanPattern(GetModuleHandleW(L"shaderapidx9.dll"), "A1 ? ? ? ? 50 8B 08 FF 51 0C") + 1);
	g_pEngineClient = reinterpret_cast<IVEngineClient*>(scanInterface("engine.dll", "VEngineClient"));
	g_pEntityList = reinterpret_cast<IClientEntityList*>(scanInterface("client.dll", "VClientEntityList"));
	g_pClient = reinterpret_cast<IBaseClientDLL*>(scanInterface("client.dll", "VClient"));
}

std::uint8_t* CInterfaces::scanPattern(void* module, const char* signature) {
	static auto pattern_to_byte = [](const char* pattern) {
		auto bytes = std::vector<int>{};
		auto start = const_cast<char*>(pattern);
		auto end = const_cast<char*>(pattern) + strlen(pattern);

		for (auto current = start; current < end; ++current) {
			if (*current == '?') {
				++current;
				if (*current == '?')
					++current;
				bytes.push_back(-1);
			}
			else {
				bytes.push_back(strtoul(current, &current, 16));
			}
		}
		return bytes;
	};

	auto dosHeader = (PIMAGE_DOS_HEADER)module;
	auto ntHeaders = (PIMAGE_NT_HEADERS)((std::uint8_t*)module + dosHeader->e_lfanew);

	auto sizeOfImage = ntHeaders->OptionalHeader.SizeOfImage;
	auto patternBytes = pattern_to_byte(signature);
	auto scanBytes = reinterpret_cast<std::uint8_t*>(module);

	auto s = patternBytes.size();
	auto d = patternBytes.data();

	for (auto i = 0ul; i < sizeOfImage - s; ++i) {
		bool found = true;
		for (auto j = 0ul; j < s; ++j) {
			if (scanBytes[i + j] != d[j] && d[j] != -1) {
				found = false;
				break;
			}
		}
		if (found) {
			return &scanBytes[i];
		}
	}
	return nullptr;
}

typedef void* (*createInterface)(const char* Name, int* ReturnCode);
void* CInterfaces::scanInterface(const char* Module, const char* InterfaceName)
{
	void* Interface = nullptr;
	auto CreateInterface = reinterpret_cast<createInterface>(GetProcAddress(GetModuleHandleA(Module), "CreateInterface"));

	char PossibleInterfaceName[1024];
	for (int i = 1; i < 100; i++)
	{
		sprintf(PossibleInterfaceName, "%s0%i", InterfaceName, i);
		Interface = CreateInterface(PossibleInterfaceName, 0);
		if (Interface) {
			std::cout << InterfaceName << " 0x" << Interface << std::endl;
			break;
		}

		sprintf(PossibleInterfaceName, "%s00%i", InterfaceName, i);
		Interface = CreateInterface(PossibleInterfaceName, 0);
		if (Interface) {
			std::cout << InterfaceName << " 0x" << Interface << std::endl;
			break;
		}
	}

	return Interface;
}
