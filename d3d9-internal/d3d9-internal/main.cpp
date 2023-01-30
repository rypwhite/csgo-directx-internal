#include <Windows.h>
#include <iostream>

#include "core/hooks.h"

DWORD WINAPI DllThread(PVOID pThreadParameter)
{
    //wait until all modules are loaded into the game (serverbrowser.dll is the last one)
    while (!GetModuleHandle(L"serverbrowser.dll"))
        Sleep(100);

    AllocConsole();
    SetConsoleTitle(L"CS:GO D3D9 Internal");
    //avoid _CRT_SECURE_NO_WARNINGS by using freopen_s
    freopen_s((FILE**)stdin, "CONIN$", "r", stdin);
    freopen_s((FILE**)stdin, "CONOUT$", "w", stdout);
    freopen_s((FILE**)stdin, "CONOUT$", "w", stderr);

    if (MH_Initialize() != MH_OK)
        throw std::runtime_error("failed to initialize MH_Initialize.");

    hooks::initialise();

    return TRUE;
}

//https://learn.microsoft.com/en-us/windows/win32/dlls/dllmain
BOOL WINAPI DllMain(
    HINSTANCE hinstDLL,  // handle to DLL module
    DWORD fdwReason,     // reason for calling function
    LPVOID lpvReserved)  // reserved
{
    // Perform actions based on the reason for calling.
    switch (fdwReason)
    {
    case DLL_PROCESS_ATTACH:
        // Initialize once for each new process.
        // Return FALSE to fail DLL load.
        DisableThreadLibraryCalls(hinstDLL);
        CreateThread(0, 0, (LPTHREAD_START_ROUTINE)DllThread, hinstDLL, 0, 0);
        break;

    case DLL_THREAD_ATTACH:
        // Do thread-specific initialization.
        break;

    case DLL_THREAD_DETACH:
        // Do thread-specific cleanup.
        break;

    case DLL_PROCESS_DETACH:

        if (lpvReserved != nullptr)
        {
            break; // do not do cleanup if process termination scenario
        }

        // Perform any necessary cleanup.
        break;
    }
    return TRUE;  // Successful DLL_PROCESS_ATTACH.
}