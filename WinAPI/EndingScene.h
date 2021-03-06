#pragma once
#include "GameNode.h"
#define RATE_TIME 5.0f

class EndingScene : public GameNode
{
private:
	my::Image* _bg;
	my::Image* _changeScreen;
	my::Image* _titleChangeScreen;

	RECT _bgRc;

	float _changeSceneTime;
	float _endChangeScreenAlpha;
	float _titleChangeScreenAlpha;

	bool _isEndStart;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
};

