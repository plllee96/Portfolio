#pragma once
#include "GameNode.h"
class CEffect : public GameNode
{
private:

public:
	my::Image* _image;
	RECT _rc;
	int _currentFrameX;
	int _currentFrameY;

	float _x, _y;
	float _fixX, _fixY;
	RECT* _prc;
	float _rndTimeCount;
	float _worldTimeCount;
	float _isActive;

	HRESULT init(void);
	virtual HRESULT init(const char* imageName, RECT rc);
	virtual HRESULT init(const char* imageName, RECT rc, float count);
	virtual HRESULT init(const char* imageName, RECT* rc, float count, float fixX, float fixY);
	void release(void);
	void update(void);
	void render(void);
	void draw(void);
	void animation(void);

	bool getIsActive(void) { return _isActive; }

	CEffect(void);
	virtual~CEffect(void);
};

