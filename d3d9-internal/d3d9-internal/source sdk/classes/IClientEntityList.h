#pragma once

class IClientEntityList
{
public:

	virtual void PAD0();
	virtual void PAD1();
	virtual void PAD2();

	virtual void* GetClientEntity(int Index);
	virtual void* GetClientEntityFromHandle(void* _Handle);

	virtual int NumberOfEntities(bool NonNetworkable);
	virtual int GetHighestEntityIndex();
	virtual void SetMaxEntities(int Max);
	virtual void GetMaxEntities();

};