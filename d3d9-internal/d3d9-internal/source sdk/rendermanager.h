#pragma once
#include <d3d9.h>
#include <d3dx9.h>

#include "../source sdk/sdk.h"

class CRenderManager {
public:
    IDirect3DDevice9* device;
    ID3DXFont* font;
    ID3DXLine* line;

    void initialise() {
        // Get the Direct3D device
        device = Interfaces.g_D3DDevice9;

        //create the font object
        D3DXCreateFont(device, 16, 0, FW_EXTRALIGHT, 1, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"Arial", &font);

        //create the line object
        D3DXCreateLine(device, &line);
    }

    void DrawText(int x, int y, DWORD color, const char* text) {
        RECT rect = { x, y, x + 100, y + 20 };
        font->DrawTextA(NULL, text, -1, &rect, DT_NOCLIP, color);
    }

    void DrawLine(int x1, int y1, int x2, int y2, DWORD color) {
        D3DXVECTOR2 points[2] = { D3DXVECTOR2((float)x1, (float)y1), D3DXVECTOR2((float)x2, (float)y2) };
        line->Begin();
        line->Draw(points, 2, color);
        line->End();
    }

    void DrawOutlinedRectangle(int x, int y, int w, int h, DWORD color) {
        DrawLine(x, y, x + w, y, color);
        DrawLine(x, y, x, y + h, color);
        DrawLine(x + w, y, x + w, y + h, color);
        DrawLine(x, y + h, x + w, y + h, color);
    }

    void DrawFilledRectangle(int x, int y, int w, int h, DWORD color) {
        D3DRECT rect = { x, y, x + w, y + h };
        device->Clear(1, &rect, D3DCLEAR_TARGET, color, 0, 0);
    }
};

extern CRenderManager RenderManager;