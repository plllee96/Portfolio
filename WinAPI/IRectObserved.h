#pragma once
#include "Stdafx.h"


//=====================================
//	## ObjectObserved ##
//=====================================
enum class ObservedType
{
	PLAYER = 0,
	PLAYER_MISSILE,
	MINION,
	MINION_MISSILE,
	PLAYER_SWORD,
	ITEM
};

typedef struct tagObservedInfo
{
	ObservedType* typeKey;
	RECT* rc;
	bool* isActive;	
	float* damage;
	float* angle;
	int* number;
	bool* magic;

	tagObservedInfo()
	{
		typeKey = nullptr;
		rc = nullptr;
		isActive = nullptr;
		damage = nullptr;
		angle = nullptr;
		number = nullptr;
		magic = nullptr;
	}
}STObservedData;

class IRectObserved 
{
public:
	virtual STObservedData getRectUpdate() = 0;
	virtual void collideObject(STObservedData obData) = 0;	//type 충돌된 상대 객체

	IRectObserved() {}
	virtual ~IRectObserved() {}
};

//=====================================
//	## EventObserved ##
//=====================================

enum class EventObservedType
{
	SHOP =0,
	CHEST,
	ANVIL
};

typedef struct tagEventObservedInfo
{
	EventObservedType* typeKey;
	RECT* rc;
	bool* isActive;	
	int* num;

	tagEventObservedInfo()
	{
		typeKey = nullptr;
		rc = nullptr;
		isActive = nullptr;
		num = nullptr;
	}
}STEventObservedData;

class IEventObservered
{
public:
	virtual STEventObservedData getEventUpdate() = 0;
	virtual void collideEventObject(STEventObservedData obEventData) = 0;

	IEventObservered() {}
	~IEventObservered() {}
};

