#pragma once
#include "GameNode.h"
#include "ItemManager.h"
#include "ItemSpawner.h"
#include "EventObject.h"


class Player;
class ItemObject;
class EventObject;
class ItemManager;
class ItemSpawner;

class Map : public GameNode
{
public:
	enum class MAPTYPE
	{
		DEFAULT, START, TREASURE, REPAIR, SHOP, BOSS
	};
protected:
	my::Image* _minimapImage;
	my::Image* _image;
	my::Image* _upWall;
	my::Image* _downWall;
	my::Image* _leftWall;
	my::Image* _rightWall;
	my::Image* _pixelCollisionImage;

	Map** _currentMap;

	POINT _location;
	MAPTYPE _type;

	//ĳ???? Ȱ???ݰ?
	RECT _mapRC;

	//?ٱ? ??
	RECT _outsideRcWidth;
	RECT _outsideRcLength;

	RECT _mapRectSize;

	bool _show;
	bool _clear;
	bool _connectedMap[4]; //Left, Up, Right, Down
	bool _isActive;

public:
	virtual HRESULT init(POINT location);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	void showMinimapIcon(int x, int y);
	MAPTYPE getType() { return _type; }
	POINT getLocation() { return _location; }

	void setCurrentMap(Map** currentMap) { _currentMap = currentMap; }
	bool checkActiveMap();

	bool isShow() { return _show; }
	void setShow(bool show) { _show = show; }
	bool isClear() { return _clear; }
	void setClear(bool clear) { _clear = clear; }
	RECT getMapAreaRect(){return _mapRectSize;}

	void setConnectedMap(int arrayNum, bool connected)
	{
		_connectedMap[arrayNum] = connected;
	}

	my::Image* getPixelCollisionImage() { return _pixelCollisionImage; }
	MAPTYPE getMapType() { return _type; }
	bool isConnected(int map) { return _connectedMap[map]; }

	RECT getMapRC() { return _mapRC; }
	void printOutsideRC();

	Map() :_mapRectSize({ 0,0,WINSIZE_X,WINSIZE_Y }), _mapRC({ 0,0,WINSIZE_X,WINSIZE_Y }), _isActive(false) {}
};

