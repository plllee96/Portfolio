#include "Stdafx.h"
#include "Bullets.h"


//=============================================
// ### AMissile ###
//=============================================

HRESULT AMissile::init(int bulletMax, float range)
{
	_range = range;
	_bulletMax = bulletMax;

	return S_OK;
}

void AMissile::release(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		SAFE_DELETE((*_viBullet)->img);
	}
	_vBullet.clear();
}

void AMissile::update(void)
{
	move();
	isRange();
	CheckFire();
}

void AMissile::render(void)
{
	draw();
}

void AMissile::fire(float x, float y)
{

}

void AMissile::draw(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		(*_viBullet)->img->frameRender(getMemDC(), (*_viBullet)->rc.left, (*_viBullet)->rc.top);

		(*_viBullet)->count++;
		if ((*_viBullet)->count % 3 == 0)
		{
			(*_viBullet)->img->setFrameX((*_viBullet)->img->getFrameX() + 1);
			if ((*_viBullet)->img->getFrameX() >= (*_viBullet)->img->getMaxFrameX())
			{
				(*_viBullet)->img->setFrameX(0);
			}
			(*_viBullet)->count = 0;
		}
	}
}

void AMissile::move(void)
{

}

void AMissile::isRange()
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();)
	{
		//��Ÿ� ������ ������
		if (_range < getDistance((*_viBullet)->fireX, (*_viBullet)->fireY, (*_viBullet)->x, (*_viBullet)->y + 100))
		{
			SAFE_DELETE((*_viBullet)->img);
			(*_viBullet)->fire = false;
			(*_viBullet)->release();
			_viBullet = _vBullet.erase(_viBullet);
		}
		else ++_viBullet;
	}

}

void AMissile::CheckFire()
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (!(*_viBullet)->fire)
		{
			SAFE_DELETE((*_viBullet)->img);
			(*_viBullet)->release();
			_viBullet = _vBullet.erase(_viBullet);
			break;
		}
	}
}



//=============================================
// ### Bullet ###
//=============================================

HRESULT Bullet::init(const char* imageName, int bulletMax, float range)
{
	_imageName = imageName;
	_range = range;
	_bulletMax = bulletMax;
	
	return S_OK;
}

void Bullet::release(void)
{
	_vBullet.clear();
}

void Bullet::update(void)
{
	CheckFire();
	move();
}

void Bullet::render(void)
{
	draw();
}

void Bullet::fire(float x, float y, float angle, float speed)
{
	//�ִ� �߻簹�� ���´�.
	if (_bulletMax <= _vBullet.size()) return;
	
	tagCBullet* bullet = new tagCBullet;
	bullet->img = IMAGEMANAGER->findImage(_imageName);
	bullet->speed = speed;
	bullet->angle = angle;
	bullet->x = bullet->fireX = x;
	bullet->y = bullet->fireY = y;
	bullet->rc = RectMakeCenter(bullet->x, bullet->y, bullet->img->getFrameHeight(), bullet->img->getFrameHeight());
	bullet->type = ObservedType::MINION_MISSILE;
	bullet->fire = true;
	bullet->count = RND->getFromIntTo(1, 16);
	bullet->init();

	_vBullet.push_back(bullet);
}

void Bullet::draw(void)
{
	
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet) 
	{
		(*_viBullet)->img->frameRender(getMemDC(), (*_viBullet)->rc.left, (*_viBullet)->rc.top, (*_viBullet)->count,1);
	}
}



void Bullet::move(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();) 
	{
		(*_viBullet)->x += cosf((*_viBullet)->angle)*(*_viBullet)->speed;
		(*_viBullet)->y += -sinf((*_viBullet)->angle)*(*_viBullet)->speed;
		(*_viBullet)->rc = RectMakeCenter((*_viBullet)->x, (*_viBullet)->y, (*_viBullet)->img->getFrameWidth(), (*_viBullet)->img->getFrameHeight());
		if (_range < getDistance((*_viBullet)->fireX, (*_viBullet)->fireY, (*_viBullet)->x, (*_viBullet)->y))
		{
			(*_viBullet)->fire = false;
			(*_viBullet)->release();
			_viBullet = _vBullet.erase(_viBullet);
		}
		else ++_viBullet;
	}
}

void Bullet::CheckFire(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (!(*_viBullet)->fire)
		{
			(*_viBullet)->release();
			_viBullet = _vBullet.erase(_viBullet);
			break;
		}
	}
}

void Bullet::removeBullet(int arrNum)
{
	(*_viBullet)->fire = false;
	(*_viBullet)->release();
	_vBullet.erase(_vBullet.begin() + arrNum);
}


//==================================
// ### LinearMissile ###
//==================================

HRESULT LinearMissile::init(int bulletMax, float range)
{
	AMissile::init(bulletMax, range);
	return S_OK;
}

void LinearMissile::move(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();++_viBullet)
	{
		(*_viBullet)->y -= (*_viBullet)->speed;
		(*_viBullet)->rc = RectMakeCenter((*_viBullet)->x, (*_viBullet)->y,
			(*_viBullet)->img->getWidth(), (*_viBullet)->img->getHeight());
	}
}

void LinearMissile::fire(float x, float y)
{
	if (_bulletMax <= _vBullet.size())return;
	tagCBullet* bullet = new tagCBullet;
	bullet->img = new my::Image;
	bullet->type = ObservedType::ROCKET_MISSILE;
	bullet->img->init("Resource/Images/Project/playerBullet3.bmp", 14, 18,  true, RGB(255, 0, 255));
	bullet->speed = 15.0f;
	bullet->x = bullet->fireX = x;
	bullet->y = bullet->fireY = y;
	bullet->rc = RectMakeCenter(bullet->x, bullet->y, bullet->img->getWidth(), bullet->img->getHeight());
	bullet->fire = true;
	bullet->init();

	_vBullet.push_back(bullet);
}

void LinearMissile::draw(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		(*_viBullet)->img->render(getMemDC(), (*_viBullet)->rc.left, (*_viBullet)->rc.top);
		
	}
}

//==================================
// ### CaseShotMissile ###
//==================================

HRESULT CaseShotMissile::init(int bulletMax, float range)
{
	AMissile::init(bulletMax, range);
	_bulletCount = 0;
	_firstAngle = (PI/2)+(static_cast<float>(bulletMax / 2)*_offsetAngle);
	return S_OK;
}

void CaseShotMissile::move(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		(*_viBullet)->x += cosf((*_viBullet)->angle)*(*_viBullet)->speed;
		(*_viBullet)->y += -sinf((*_viBullet)->angle)*(*_viBullet)->speed;
		(*_viBullet)->rc = RectMakeCenter((*_viBullet)->x, (*_viBullet)->y,
			(*_viBullet)->img->getWidth(), (*_viBullet)->img->getHeight());
	}
}

void CaseShotMissile::fire(float x, float y)
{
	if (_bulletMax <= _vBullet.size())return;

	for (int i = 0; i < _bulletMax; i++)
	{
		tagCBullet* bullet = new tagCBullet;
		bullet->img = new my::Image;
		bullet->img->init("Resource/Images/Project/playerBullet1.bmp",14, 15,true, RGB(255, 0, 255));
		bullet->type = ObservedType::ROCKET_MISSILE;
		bullet->speed = 4.0f;
		bullet->x = bullet->fireX = x;
		bullet->y = bullet->fireY = y;
		bullet->angle = _firstAngle - (_bulletCount*_offsetAngle);
		bullet->rc = RectMakeCenter(bullet->x, bullet->y, bullet->img->getWidth(), bullet->img->getHeight());
		bullet->fire = true;
		bullet->init();
		_vBullet.push_back(bullet);

		_bulletCount++;
	}
	_bulletCount = 0;
	
}
void CaseShotMissile::draw(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		(*_viBullet)->img->render(getMemDC(), (*_viBullet)->rc.left, (*_viBullet)->rc.top);

	}
}

//==================================
// ### BlackholeMissile ###
//==================================
HRESULT BlackholeMissile::init(int bulletMax, float range)
{
	AMissile::init(bulletMax, range);
	return S_OK;
}

void BlackholeMissile::move(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();++_viBullet)
	{
		(*_viBullet)->y -= (*_viBullet)->speed;
		(*_viBullet)->rc = RectMakeCenter((*_viBullet)->x, (*_viBullet)->y,
			(*_viBullet)->img->getFrameWidth(), (*_viBullet)->img->getFrameHeight());
	}
}

void BlackholeMissile::fire(float x, float y)
{
	//�ִ� �߻� ������ ���´�.
	if (_bulletMax <= _vBullet.size())return;

	//�޸� ���� ũ�� ��ŭ 
	tagCBullet* bullet= new tagCBullet;
	bullet->type = ObservedType::ROCKET_MISSILE;
	bullet->img = new my::Image;
	bullet->img->init("Resource/Images/Rocket/Missile.BMP", 0.0f, 0.0f, 416, 64, 13, 1, true, RGB(255, 0, 255));
	bullet->speed = 4.0f;
	bullet->x = bullet->fireX = x;
	bullet->y = bullet->fireY = y;
	bullet->rc = RectMakeCenter(bullet->x, bullet->y, bullet->img->getFrameWidth(), bullet->img->getFrameHeight());
	bullet->fire = true;
	bullet->init();

	_vBullet.push_back(bullet);
}

//==================================
// ### tagCBullet ###
//==================================
void tagCBullet::init(void)
{
	RECTOBSERVERMANAGER->registerObserved(this);
}

void tagCBullet::release(void)
{
	RECTOBSERVERMANAGER->removeObserved(this);
}

STObservedData tagCBullet::getRectUpdate()
{
	STObservedData temp;
	temp.rc = &rc;
	temp.typeKey = &type;
	temp.isActive = &fire;
	return temp;
}

void tagCBullet::collideObject()
{
	fire = false;
}