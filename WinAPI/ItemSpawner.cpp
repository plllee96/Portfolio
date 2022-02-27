#include "Stdafx.h"
#include "ItemSpawner.h"

//============================
//   ### ItemObject ###
//============================
HRESULT ItemObject::init(void)
{
	return S_OK;
}

HRESULT ItemObject::init(int x, int y, bool isCollider)
{
	_x = x;
	_y = y;
	_isCollider = isCollider;
	_rc = RectMakeCenter(_x, _y, ITEM_OBJ_SIZE, ITEM_OBJ_SIZE);
	_typeKey = ObservedType::ITEM;
	_itemManager = ItemManager::getSingleton();
	_itemIndex = RND->getInt(_itemManager->getItemSize());
	_increaseY = false;
	_isActive = true;
	_responseTime = _worldTime = TIMEMANAGER->getWorldTime();
	
	RECTOBSERVERMANAGER->registerObserved(this);
	return S_OK;
}

void ItemObject::release(void)
{
	RECTOBSERVERMANAGER->removeObserved(this);
}

void ItemObject::update(void)
{
	if (TIMEMANAGER->getWorldTime() > _worldTime + 1.0f)
	{
		_increaseY = !_increaseY;
		_worldTime = TIMEMANAGER->getWorldTime();
	}
	if (_increaseY) { _y--; }
	else { _y++; }
	_rc = RectMakeCenter(_x, _y, ITEM_OBJ_SIZE, ITEM_OBJ_SIZE);
}

void ItemObject::render(void)
{
	_itemManager->getBigItemIndexRender(getMemDC(), _itemIndex, _rc.left, _rc.right);
}

STObservedData ItemObject::getRectUpdate()
{
	STObservedData temp;
	temp.typeKey = &_typeKey;
	temp.number = &_itemIndex;
	temp.isActive = &_isActive;
	temp.rc = &_rc;
	temp.angle = &_responseTime;

	return temp;
}

void ItemObject::collideObject(STObservedData obData)
{
	if (_isCollider)
	{
		if (TIMEMANAGER->getWorldTime() > _responseTime + 1.0f)
		{
			_isActive = false;
		}
	}
}

//============================
//   ### ItemSpawner ###
//============================
HRESULT ItemSpawner::init(void)
{
	return S_OK;
}

void ItemSpawner::release(void)
{
	_viItemObj = _vItemObj.begin();
	for (; _viItemObj < _vItemObj.end(); ++_viItemObj)
	{
		(*_viItemObj)->release();
	}
	_vItemObj.clear();
}

void ItemSpawner::update(void)
{
	_viItemObj = _vItemObj.begin();
	for (; _viItemObj < _vItemObj.end(); ++_viItemObj)
	{
		(*_viItemObj)->update();
		if (!(*_viItemObj)->getIsActive())
		{
			(*_viItemObj)->release();
			_vItemObj.erase(_viItemObj);
		}
	}
}

void ItemSpawner::render(void)
{
	_viItemObj = _vItemObj.begin();
	for (; _viItemObj < _vItemObj.end(); ++_viItemObj)
	{
		(*_viItemObj)->render();
	}
}

void ItemSpawner::createItem(int x, int y, bool isCollider)
{
	ItemObject* itemObj = new ItemObject;
	itemObj->init(x, y, isCollider);
	_vItemObj.push_back(itemObj);
}

void ItemSpawner::clearItem(void)
{
	_viItemObj = _vItemObj.begin();
	for (; _viItemObj < _vItemObj.end(); ++_viItemObj)
	{
		(*_viItemObj)->release();
	}
	_vItemObj.clear();
}
