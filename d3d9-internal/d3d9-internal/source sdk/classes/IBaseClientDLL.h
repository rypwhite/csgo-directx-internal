#pragma once
class ClientClass;

class CGlobalVarsBase
{
public:
	float     realtime;
	int       framecount;
	float     absoluteframetime;
	float     absoluteframestarttimestddev;
	float     curtime;
	float     frametime;
	int       maxClients;
	int       tickcount;
	float     intervalPerTick;
	float     interpolationAmount;
	int       simTicksThisFrame;
	int       networkProtocol;
	void* pSaveData;
	bool      bClient;
	bool      bRemoteClient;

private:
	// 100 (i.e., tickcount is rounded down to this base and then the "delta" from this base is networked
	int       nTimestampNetworkingBase;
	// 32 (entindex() % nTimestampRandomizeWindow ) is subtracted from gpGlobals->tickcount to set the networking basis, prevents
	//  all of the entities from forcing a new PackedEntity on the same tick (i.e., prevents them from getting lockstepped on this)
	int       nTimestampRandomizeWindow;
};

typedef void* (*CreateInterfaceFn) (const char* pName, int* pReturnCode); //to do | same as in tools.cpp
class IBaseClientDLL
{
public:
	// Connect appsystem components, get global interfaces, don't run any other init code
	virtual int              Connect(CreateInterfaceFn appSystemFactory, CGlobalVarsBase* pGlobals) = 0;
	virtual int              Disconnect(void) = 0;
	virtual int              Init(CreateInterfaceFn appSystemFactory, CGlobalVarsBase* pGlobals) = 0;
	virtual void             PostInit() = 0;
	virtual void             Shutdown(void) = 0;
	virtual void             LevelInitPreEntity(char const* pMapName) = 0;
	virtual void             LevelInitPostEntity() = 0;
	virtual void             LevelShutdown(void) = 0;
	virtual ClientClass* GetAllClasses(void) = 0;
};
extern IBaseClientDLL* g_pClient;