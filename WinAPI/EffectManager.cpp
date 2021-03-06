#include "Stdafx.h"
#include "EffectManager.h"

HRESULT EffectManager::init(void)
{
	IMAGEMANAGER->addFrameImage("effect1", "Resource/Images/Project/effect1.bmp", 0.0f, 0.0f, 429, 193, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("effect2", "Resource/Images/Project/effect2.bmp", 0.0f, 0.0f, 531, 187, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Levelup", "Resource/Images/Lucie/CompleteImg/effect/levelup.bmp", 0.0f, 0.0f, 960, 576, 5, 3, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("WindEffect", "Resource/Images/Lucie/CompleteImg/effect/windEffect.bmp", 0.0f, 0.0f, 960, 384, 5, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Dead", "Resource/Images/Lucie/CompleteImg/effect/dead.bmp", 0.0f, 0.0f, 480, 1920, 5, 20, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("BowHit", "Resource/Images/Lucie/CompleteImg/effect/bowHit.bmp", 0.0f, 0.0f, 192, 48, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("NormalHit", "Resource/Images/Lucie/CompleteImg/effect/normalHit.bmp", 0.0f, 0.0f, 384, 96, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SkillHit", "Resource/Images/Lucie/CompleteImg/effect/skill_ms24@[40-3].bmp", 0.0f, 0.0f, 960, 1536, 5, 8, true, RGB(255, 0, 255));
	return S_OK;
}

void EffectManager::release(void)
{
	_viEffect = _vEffect.begin();
	for (; _viEffect != _vEffect.end(); ++_viEffect)
	{
		(*_viEffect)->release();
		SAFE_DELETE(*_viEffect);
		_vEffect.erase(_viEffect);
	}
}

void EffectManager::update(void)
{
	_viEffect = _vEffect.begin();
	for (; _viEffect != _vEffect.end(); ++_viEffect)
	{
		(*_viEffect)->update();

		//CheckIsActive
		if (!(*_viEffect)->getIsActive()) 
		{
			(*_viEffect)->release();
			SAFE_DELETE(*_viEffect);
			_vEffect.erase(_viEffect);
			break;
		}
	}
}

void EffectManager::render(void)
{
	_viEffect = _vEffect.begin();
	for (; _viEffect != _vEffect.end(); ++_viEffect)
	{
		(*_viEffect)->render();
	}
}

void EffectManager::createEffect(const char* fileName, RECT rc)
{
	CEffect* effect = new CEffect;
	effect->init(fileName, rc);
	_vEffect.push_back(effect);
}

void EffectManager::createEffect(const char* fileName, RECT* rc)
{
	CEffect* effect = new CEffect;
	effect->init(fileName, *rc);
	_vEffect.push_back(effect);
}

void EffectManager::createEffect(const char* fileName, RECT rc, float count)
{
	CEffect* effect = new CEffect;
	effect->init(fileName, rc, count);
	_vEffect.push_back(effect);
}

void EffectManager::createEffect(const char* fileName, RECT* rc, float count, float fixX, float fixY)
{
	CEffect* effect = new CEffect;
	effect->init(fileName, rc, count, fixX, fixY);
	_vEffect.push_back(effect);
}
