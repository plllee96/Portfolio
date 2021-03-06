#include "Stdafx.h"
#include "StartMap.h"

HRESULT StartMap::init(POINT location)
{
	_type = Map::MAPTYPE::START;
	_show = true;
	_clear = true;
	_image = IMAGEMANAGER->addImage("StartGround", "Resource/Images/Lucie/CompleteImg/ground/map/Ground101.bmp", 1008, 816, false, RGB(255, 0, 255));
	_minimapImage = IMAGEMANAGER->addImage("Minimap_Start", "Resource/Images/Lucie/CompleteImg/miniMap/minimap_cellIcon_start.bmp", 30, 30, true, RGB(255, 0, 255));
	_pixelCollisionImage = IMAGEMANAGER->addImage("StartPixel", "Resource/Images/Lucie/CompleteImg/ground/pixelmap/!m101.bmp", 1008, 816, false, RGB(255, 0, 255));
	_upWall = IMAGEMANAGER->addImage("UpWall2", "Resource/Images/Lucie/CompleteImg/ground/wall/upperWall2.bmp", 240, 240, true, RGB(255, 0, 255));
	_leftWall = IMAGEMANAGER->addImage("LeftWall4", "Resource/Images/Lucie/CompleteImg/ground/wall/LeftWall4.bmp", 281, 600, true, RGB(255, 0, 255));
	_rightWall = IMAGEMANAGER->addImage("RightWall4", "Resource/Images/Lucie/CompleteImg/ground/wall/RightWall4.bmp", 281, 588, true, RGB(255, 0, 255));
	_downWall = IMAGEMANAGER->addImage("DownWall1", "Resource/Images/Lucie/CompleteImg/ground/wall/downWall1.bmp", 240, 240, true, RGB(255, 0, 255));
	_floorText = IMAGEMANAGER->addImage("MapName", "Resource/Images/Lucie/CompleteImg/pitures/mapName_forest.bmp", 284, 136, true, RGB(255, 0, 255));
	_textAlpha = 0;
	_textFadeIn = true;
	_outsideRcWidth = { 0, 816, 1104, 960 };
	_outsideRcLength = { 1008, 0, 1104, 960 };
	_location = location;
	_mapRC = { 200, 50, 700, 600 };

	_showTextTime = 0;
	_pixel = false;

	_mapRectSize = RectMake(0,0,1008,816);

	return S_OK;
}

void StartMap::release(void)
{
}

void StartMap::update(void)
{
	_outsideRcWidth = { 0, 816 - CAMERAMANAGER->getCameraRect().top, 1104, 960 };
	_outsideRcLength = { 1008 - CAMERAMANAGER->getCameraRect().left, 0, 1104, 960 };
	if (KEYMANAGER->isOnceKeyDown('Z'))
	{
		_pixel = !_pixel;
	}
	mapText();
}

void StartMap::render(void)
{
	_image->render(getMemDC(),
		-CAMERAMANAGER->getCameraRect().left,
		-CAMERAMANAGER->getCameraRect().top);

	if (_pixel) _pixelCollisionImage->render(getMemDC(),
		-CAMERAMANAGER->getCameraRect().left,
		-CAMERAMANAGER->getCameraRect().top);

	if (!_connectedMap[0] || !_clear) _leftWall->render(getMemDC(),
		0 - CAMERAMANAGER->getCameraRect().left,
		2 - CAMERAMANAGER->getCameraRect().top);

	if (!_connectedMap[1] || !_clear) _upWall->render(getMemDC(),
		380 - CAMERAMANAGER->getCameraRect().left,
		-130 - CAMERAMANAGER->getCameraRect().top);

	if (!_connectedMap[2] || !_clear) _rightWall->render(getMemDC(),
		728 - CAMERAMANAGER->getCameraRect().left,
		2 - CAMERAMANAGER->getCameraRect().top);

	if (!_connectedMap[3] || !_clear) _downWall->render(getMemDC(),
		390 - CAMERAMANAGER->getCameraRect().left,
		_image->getHeight() - 240 - CAMERAMANAGER->getCameraRect().top);

	_floorText->alphaRender(getMemDC(), 330, 100, _textAlpha);
}

void StartMap::mapText(void)
{
	if (_textFadeIn) _textAlpha += 2;
	else _textAlpha -= 2;
	if (_textAlpha == 252) _showTextTime = TIMEMANAGER->getWorldTime();
	if (_textAlpha >= 254) _textAlpha = 254;
	if (_textAlpha < 0) _textAlpha = 0;

	if (_showTextTime + 3.0f < TIMEMANAGER->getWorldTime()) _textFadeIn = false;
}
