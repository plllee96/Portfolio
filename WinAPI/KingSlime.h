#pragma once
#include "Enemy.h"

#define FRAMEDELAY		0.5f;

class KingSlime : public Enemy
{
private:
	//NormalBullet* _normalBullet				탄막 여러개
	//BubbleBullet	* _bubbleBullet				큰 탄환->작은 탄환 여러개
	//BounceBullet* _bounceBullet				튕기는 탄환
	enum class STATE {STOP, WALK, ATTACK_BUBBLE, ATTACK_NORMAL, ATTACK_BOUNCE};
	enum class DIRECTION {DOWN = 0, LEFT, RIGHT, UP};

	STATE _state;
	DIRECTION _direction;

	bool _deadForOb;
	int _frameX, _frameY;
	int _frameSet;			//3프레임 단위를 한 동작.

	int _stopSet;				//보스명 문구가 나오는 동안 멈춰있음
	int _walkRndSet;		//플레이어를 향해 걸어오는 동작. (4~7 랜덤)
	int _attackSet;
	float _frameDelayTime;
public:
	HRESULT init(const char* imageName, POINT position);
	void release(void);
	void update(void);
	void render(void);

	virtual STObservedData getRectUpdate();
	virtual void collideObject(STObservedData obData);

	void frameUpdate();
	void move();

	void changeState(STATE state);
	void changeAnotherState();

	KingSlime() : _frameY(0) {}
	virtual ~KingSlime() {}
};

