#pragma once
#include "Enemy.h"
#include "Animation.h"
#include "Bullets.h"

enum class SLIMESTATE { SL_IDLE, SL_MOVE, SL_ATTACK, SL_DEAD, SL_END };
enum class SLIMEDIRECTION { SL_LEFT, SL_RIGHT, SL_UP, SL_DOWN, SL_END };
enum class SLIMEATTACK { SL_PARTTERN1, SL_PARTTERN2, SL_PARTTERN_END };


class Slime:public Enemy
{
private:
	ThreeDirectionMissile*	_threeDirectionBullet;
	CircleMissile*			_circleBullet;

	SLIMEDIRECTION			_direction;
	SLIMESTATE				_state;
	SLIMEATTACK				_attackParttern;

	float	_speed;				//이동 속도
	float	_angle;
	float	_playerDistance;
	float	_moveWorldTime;
	float	_attacWorldTime;
	float	_randomTimeCount;
	float	_frameSpeed;
	float	_deadTimeCount;
	int		_randomX, _randomY;
	int		_range;				//플레이어 탐지 범위
	int		_attackRange;		//공격 사거리
	bool	_moveCheck;			//공격시 움직임 체크
	bool	_deadForOb;		//사망 여부 [Enemy의 isActive는 몹 삭제 전용, deadForOb는 체력 0 여부]


public:
	HRESULT init(const char* imageName, POINT position);
	void release(void);
	void update(void);
	void render(void);

	void move(void);
	void draw(void);
	void frame();
	void animation();
	void pursuePlayer();	//플레이어 추적
	void randomMove();		//랜덤으로 이동 기능
	bool playerCheck();		//플레이어 감지함수
	void randomPosCreate();
	void attackParttern();	//공격 패턴 정해줌
	void circleDirectionBullet();
	void threeDirectionBullet();


public:
	virtual STObservedData getRectUpdate();
	virtual void collideObject(STObservedData obData);

	Slime();
	virtual ~Slime();
};
