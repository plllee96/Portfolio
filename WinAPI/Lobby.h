#pragma once
#include "GameNode.h"
#include "TextSystemManager.h"
#include "LobbyPlayer.h"
#include "MainGame.h"

class Lobby : public GameNode
{
private:
	TextSystemManager* _tsm;
	
	my::Image* _WhitefadeOutImg;
	my::Image* _BlackfadeOutImg;
	my::Image* _bookImg;

	Animation* _anim;
	LobbyPlayer* _player;

	RECT rc;
	RECT _p_rc;
	RECT _Imgbook_rc;
	RECT _book_rc;
	RECT _box_rc;
	RECT _closet_rc;
	RECT _mirror_rc;
	RECT _window_rc;
	RECT _door_rc;
	RECT _select_rc;

	float _worldTimeCount;
	float _frameSpeed;
	float _index;

	bool _bookOpen;

	float _fadeOutWhiteAlpha;
	float _fadeOutBlackAlpha;
	float _startAlpha;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	void animation(void);
	virtual void Collision(void);
	void LobbyCollision(void);

	bool _collBox;

	Lobby() {}
	~Lobby() {}
};

