#pragma once

#include "../math.h"

//https://github.com/frk1/hazedumper/blob/master/csgo.cs
class CBaseEntity
{
public:

	bool m_bDormant() {
		return *(bool*)(this + 0xED);
	}

	int m_iTeamNum() {
		return *(int*)(this + 0xF4);
	}

	int m_iHealth() {
		return *(int*)(this + 0x100);
	}

	Vector m_vecOrigin() {
		return *(Vector*)(this + 0x138);
	}
};