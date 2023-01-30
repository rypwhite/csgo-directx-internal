#pragma once
#include <stdint.h>

class IVEngineClient
{
public:
	virtual bool IsInGame(void) = 0;
	virtual bool IsConnected(void) = 0;
};