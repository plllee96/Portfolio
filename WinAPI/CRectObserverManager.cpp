#include "Stdafx.h"
#include "CRectObserverManager.h"
#include "EffectManager.h"
#include "PlayScene.h"
#include "DamageEffectManager.h"

HRESULT CRectObserverManager::init()
{
	_effectManager = new EffectManager;
	_effectManager->init();

	_damageManager = new DamageEffectManager;
	_damageManager->init();
	return S_OK;
}

void CRectObserverManager::release(void)
{
	_vRect.clear();
}

void CRectObserverManager::update(void)
{
	_effectManager->update();
	_damageManager->update();
	getRectFromObserved();
	getEventFormObserved();
}

void CRectObserverManager::render(void)
{
	_effectManager->render();
	_damageManager->render();
}

void CRectObserverManager::registerObserved(IRectObserved* observed)
{
	_vRect.push_back(observed);
}

void CRectObserverManager::removeObserved(IRectObserved* observed)
{
	_viRect = _vRect.begin();
	for (; _viRect != _vRect.end(); ++_viRect) 
	{
		if (*_viRect == observed) 
		{
			_vRect.erase(_viRect);
			break;
		}
	}
}

void CRectObserverManager::registerPlayer(Player* player)
{
	_player = player;
}

void CRectObserverManager::registerEventObserved(IEventObservered* observed)
{
	_vEvent.push_back(observed);
}

void CRectObserverManager::removeEventObserved(IEventObservered* observed)
{
	_viEvent = _vEvent.begin();
	for (; _viEvent != _vEvent.end(); ++_viEvent)
	{
		if (*_viEvent == observed)
		{
			_vEvent.erase(_viEvent);
			break;
		}
	}
}

void CRectObserverManager::getEventFormObserved()
{
	_viEvent = _vEvent.begin();
	for (; _viEvent != _vEvent.end(); ++_viEvent)
	{
		STEventObservedData obData;
		obData = (*_viEvent)->getEventUpdate();
		RECT collisionRect;
		if (*obData.isActive) continue;
		if (IntersectRect(&collisionRect, &_player->getRect(), obData.rc))
		{
			if (*obData.typeKey == EventObservedType::SHOP)
			{
				(*_viEvent)->collideEventObject(obData);
			}
			else if (*obData.typeKey == EventObservedType::CHEST)
			{
				(*_viEvent)->collideEventObject(obData);
			}
			else if (*obData.typeKey == EventObservedType::ANVIL)
			{
				(*_viEvent)->collideEventObject(obData);
			}
		}
	}
}

void CRectObserverManager::getRectFromObserved()
{
	if (_vRect.size() == 0) return;
	_viRect = _vRect.begin();
	for (; _viRect != _vRect.end(); ++_viRect)
	{
		STObservedData obData;
		obData = (*_viRect)->getRectUpdate();

		_viRectCompare = _vRect.begin();
		for (;_viRectCompare != _vRect.end(); ++_viRectCompare)
		{
			STObservedData obDataCompare;
			obDataCompare = (*_viRectCompare)->getRectUpdate();
			if ((*obData.typeKey) == (*obDataCompare.typeKey)) continue;

			//적 피격 (obData : 내 총알, Compare : 적)
			if (((*obData.typeKey) == ObservedType::ROCKET_MISSILE || (*obData.typeKey) == ObservedType::PLAYER_SWORD) &&
				(*obDataCompare.typeKey) == ObservedType::MINION && !(*obDataCompare.isActive))
			{
				RECT collisionRect;
				if (IntersectRect(&collisionRect, obData.rc, obDataCompare.rc))
				{
					if (*obData.isActive)
					{
						_damageManager->createDamage((int)(*obData.damage), false,
							(*obDataCompare.rc).left + (((*obDataCompare.rc).right - (*obDataCompare.rc).left) / 2),
							(*obDataCompare.rc).top + (((*obDataCompare.rc).bottom - (*obDataCompare.rc).top) / 2));

						_effectManager->createEffect("effect2", (*obDataCompare.rc));

						(*_viRectCompare)->collideObject(obData);			//받은 data의 Active가 false일 경우에만 체력 감소
						(*_viRect)->collideObject(obDataCompare);			//Active를 false로 변환

					}

					continue;
				}
			}

			//플레이어 피격 (obData : 적 총알, Compare : 플레이어)
			if ((*obData.typeKey) == ObservedType::MINION_MISSILE &&
				(*obDataCompare.typeKey) == ObservedType::ROCKET)
			{
				RECT collisionRect;
				if (IntersectRect(&collisionRect, obData.rc, obDataCompare.rc))
				{
					(*_viRect)->collideObject(obDataCompare);
					(*_viRectCompare)->collideObject(obData);

					continue;
				}
			}

			//Sword 반격 (obData : 
			if ((*obData.typeKey) == ObservedType::PLAYER_SWORD &&
				(*obDataCompare.typeKey) == ObservedType::MINION_MISSILE)
			{
				RECT collisionRect;
				if (IntersectRect(&collisionRect, obData.rc, obDataCompare.rc))
				{
					//sword인지 조건 추가
					(*_viRectCompare)->collideObject(obData);	//각도 변환, type 변환

					continue;
				}
			}

			//아이템 충돌 (obData : 아이템, Compare : 플레이어)
			if ((*obData.typeKey) == ObservedType::ITEM &&
				(*obDataCompare.typeKey) == ObservedType::ROCKET)
			{
				RECT collisionRect;
				if (IntersectRect(&collisionRect, obData.rc, obDataCompare.rc))
				{
					(*_viRect)->collideObject(obDataCompare);
					(*_viRectCompare)->collideObject(obData);

					continue;
				}
			}

		}

	}

}

