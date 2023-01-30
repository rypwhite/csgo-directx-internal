#pragma once
#include <Windows.h>
#include "../source sdk/sdk.h"
#include "../source sdk/math.h"
#include "../source sdk/rendermanager.h"

static bool WorldToScreen(const Vector& origin, Vector& screen)
{
    const auto screenTransform = [&origin, &screen]() -> bool
    {
        static std::uintptr_t pViewMatrix;
        if (!pViewMatrix)
        {
            pViewMatrix = (std::uintptr_t)(Interfaces.scanPattern(GetModuleHandleW(L"client.dll"), "0F 10 05 ? ? ? ? 8D 85 ? ? ? ? B9"));
            pViewMatrix += 3;
            pViewMatrix = *reinterpret_cast<std::uintptr_t*>(pViewMatrix);
            pViewMatrix += 176;
        }

        const VMatrix& w2sMatrix = *reinterpret_cast<VMatrix*>(pViewMatrix);
        screen.x = w2sMatrix.m[0][0] * origin.x + w2sMatrix.m[0][1] * origin.y + w2sMatrix.m[0][2] * origin.z + w2sMatrix.m[0][3];
        screen.y = w2sMatrix.m[1][0] * origin.x + w2sMatrix.m[1][1] * origin.y + w2sMatrix.m[1][2] * origin.z + w2sMatrix.m[1][3];
        screen.z = 0.0f;

        float w = w2sMatrix.m[3][0] * origin.x + w2sMatrix.m[3][1] * origin.y + w2sMatrix.m[3][2] * origin.z + w2sMatrix.m[3][3];

        if (w < 0.001f)
        {
            screen.x *= 100000;
            screen.y *= 100000;
            return true;
        }

        float invw = 1.f / w;
        screen.x *= invw;
        screen.y *= invw;

        return false;
    };

    if (!screenTransform())
    {
        int iScreenWidth, iScreenHeight;
        Interfaces.g_pEngineClient->GetScreenSize(iScreenWidth, iScreenHeight);

        screen.x = (iScreenWidth * 0.5f) + (screen.x * iScreenWidth) * 0.5f;
        screen.y = (iScreenHeight * 0.5f) - (screen.y * iScreenHeight) * 0.5f;

        return true;
    }
    return false;
}

namespace visuals {
	
	void onEndScene() {
		CBaseEntity* Local = (CBaseEntity*)Interfaces.g_pEntityList->GetClientEntity(Interfaces.g_pEngineClient->GetLocalPlayer());
		player_info_t info;
		int x, y;
		Vector player;
		Interfaces.g_pEngineClient->GetScreenSize(x, y);

		for (int i = 1; i <= Interfaces.g_pEngineClient->GetMaxClients(); i++) {
			CBaseEntity* Entity = (CBaseEntity*)Interfaces.g_pEntityList->GetClientEntity(i);

			if (!Entity || Entity->m_bDormant() || !Entity->m_iHealth()|| Entity == Local)
				continue;

			if (WorldToScreen(Entity->m_vecOrigin(), player)) {
				RenderManager.DrawLine(x / 2, y - 100, player.x, player.y, D3DCOLOR_ARGB(255, 255, 0, 0));

				//Interfaces.g_pEngineClient->GetPlayerInfo(i, &info);
				//RenderManager.DrawText(player.x, player.y, D3DCOLOR_ARGB(255, 255, 0, 0), info.szName);
			}
		}
	}
}
