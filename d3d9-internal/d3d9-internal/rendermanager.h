#pragma once
#include <d3d9.h>
#include <d3dx9.h>

#include "interfaces.h"

class CRenderManager {
public:
    IDirect3DDevice9* device;
    ID3DXFont* font;

    void initialise() {
        // Get the Direct3D device
        device = Interfaces.g_D3DDevice9;

        //create the font object
        D3DXCreateFont(device, 20, 0, FW_BOLD, 1, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"Arial", &font);
    }

    void DrawText(int x, int y, DWORD color, const char* text) {
        RECT rect = { x, y, x + 100, y + 20 };
        font->DrawTextA(NULL, text, -1, &rect, DT_NOCLIP, color);
    }
};

extern CRenderManager RenderManager;