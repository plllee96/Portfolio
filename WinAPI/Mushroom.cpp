#include "Stdafx.h"
#include "Mushroom.h"

Mushroom::Mushroom()
{
}

Mushroom::~Mushroom()
{
}

HRESULT Mushroom::init(const char* imageName)
{
	_image = IMAGEMANAGER->findImage(imageName);
	_hp = 30;
	_attackTime = TIMEMANAGER->getWorldTime();

	//Observer code
	_type = ObservedType::MINION;
	_isActive = true;
	_deadForOb = false;
	RECTOBSERVERMANAGER->registerObserved(this);

	_bullet = new CircleMissile;
	_bullet->init(10, 200);

	_bullet2 = new GuidedBullet;
	_bullet2->init(1, 200);
	
	return S_OK;
}

void Mushroom::release(void)
{
	Enemy::release();
	_bullet->release();
	SAFE_DELETE(_bullet);

	_bullet2->release();
	SAFE_DELETE(_bullet2);
}

void Mushroom::update(void)
{
	Enemy::update();
	_bullet2->update();


	if (_deadForOb)
		_isActive = false;


	_rc = RectMakeCenter(_x, _y, _image->getWidth(), _image->getHeight());
}

void Mushroom::render(void)
{
	Enemy::render();
	_bullet->render();
	_bullet2->render();
}

void Mushroom::move(void)
{
}

void Mushroom::draw(void)
{
	_image->render(getMemDC(), _rc.left, _rc.top);
}

void Mushroom::animation(void)
{
}

void Mushroom::fire(float angle)
{
	_bullet2->setAngle(angle);
	if (3.f + _attackTime <= TIMEMANAGER->getWorldTime())
	{
		_attackTime = TIMEMANAGER->getWorldTime();
		//_bullet->fire(_x, _y);
		_bullet2->fire(_x, _y, angle);
	}
}

STObservedData Mushroom::getRectUpdate()
{
	STObservedData temp;
	temp.rc = &_rc;
	temp.typeKey = &_type;
	temp.isActive = &_deadForOb;
	temp.damage = &_attack;
	return temp;
}

void Mushroom::collideObject(STObservedData obData)
{
	if (((*obData.typeKey) == ObservedType::ROCKET_MISSILE || (*obData.typeKey) == ObservedType::PLAYER_SWORD)
		&& (*obData.isActive))
	{
		if (_hp <= (*obData.damage))
		{
			//나중에 죽는 애니메이션 넣는걸로 바꿀 것. isActive를 false로 바꾸는 작업은 죽은 애니메이션 전부 실행 뒤 바꿔주는 것으로 변경	
			_deadForOb = true;
		}
		else
		{
			_hp -= (*obData.damage);
		}
		(*obData.isActive) = false;
	}
}
