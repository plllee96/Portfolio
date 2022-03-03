#include "Stdafx.h"
#include "RepairMap.h"

HRESULT RepairMap::init(POINT location)
{
	_type = Map::MAPTYPE::REPAIR;
	_show = false;
	_clear = true;
	_image = IMAGEMANAGER->addImage("RepairGround", "Resource/Images/Lucie/CompleteImg/ground/map/ground57.bmp", 1008, 670, false, RGB(255, 0, 255));
	_minimapImage = IMAGEMANAGER->addImage("Minimap_Repair", "Resource/Images/Lucie/CompleteImg/miniMap/minimap_cellIcon_event.bmp", 30, 30, true, RGB(255, 0, 255));
	_pixelCollisionImage = IMAGEMANAGER->addImage("RepairPixel", "Resource/Images/Lucie/CompleteImg/ground/pixelmap/!m57.bmp", 1008, 670, false, RGB(255, 0, 255));
	_upWall = IMAGEMANAGER->addImage("UpWall1", "Resource/Images/Lucie/CompleteImg/ground/wall/upperWall1.bmp", 240, 240, true, RGB(255, 0, 255));
	_leftWall = IMAGEMANAGER->addImage("LeftWall2", "Resource/Images/Lucie/CompleteImg/ground/wall/LeftWall2.bmp", 288, 480, true, RGB(255, 0, 255));
	_rightWall = IMAGEMANAGER->addImage("RightWall3", "Resource/Images/Lucie/CompleteImg/ground/wall/RightWall3.bmp", 240, 480, true, RGB(255, 0, 255));
	_downWall = IMAGEMANAGER->addImage("DownWall1", "Resource/Images/Lucie/CompleteImg/ground/wall/downWall1.bmp", 240, 240, true, RGB(255, 0, 255));
	
	_anvilImage = IMAGEMANAGER->addFrameImage("Anvil", "Resource/Images/Lucie/CompleteImg/event/Anvil.bmp", 144, 384, 1, 4, true, RGB(255, 0, 255));
	
	_mapRC = { 200, 50, 700, 600 };
	_outsideRcWidth = { 0, 670, WINSIZE_X, WINSIZE_Y };
	_outsideRcLength = { 1008, 0, WINSIZE_X, WINSIZE_Y };
	_location = location;

	_repairEventObj = new EventObject;
	_repairEventRc = RectMakeCenter(CAMERAMANAGER->getDisplayCenterX() - 50, CAMERAMANAGER->getDisplayCenterY() - 50, _anvilImage->getFrameWidth() / 2, 32);
	_repairEventObj->init(EventObservedType::ANVIL, _repairEventRc, &_isActive, 0);

	return S_OK;
}

void RepairMap::release(void)
{
}

void RepairMap::update(void)
{
}

void RepairMap::render(void)
{
	_image->render(getMemDC(),
		-CAMERAMANAGER->getCameraRect().left,
		-CAMERAMANAGER->getCameraRect().top);

	_anvilImage->frameRender(getMemDC(),
		CAMERAMANAGER->getDisplayCenterX() - _anvilImage->getFrameWidth() + 20 - CAMERAMANAGER->getCameraRect().left,
		CAMERAMANAGER->getDisplayCenterY() - _anvilImage->getFrameHeight() - 50 - CAMERAMANAGER->getCameraRect().top, 0, _frameY);

	if (!_connectedMap[0] || !_clear) _leftWall->render(getMemDC(),
		0 - CAMERAMANAGER->getCameraRect().left,
		143 - CAMERAMANAGER->getCameraRect().top);
	if (!_connectedMap[1] || !_clear) _upWall->render(getMemDC(),
		CAMERAMANAGER->getDisplayCenterX() - 180 - CAMERAMANAGER->getCameraRect().left,
		-150 - CAMERAMANAGER->getCameraRect().top);
	if (!_connectedMap[2] || !_clear) _rightWall->render(getMemDC(),
		768 - CAMERAMANAGER->getCameraRect().left,
		143 - CAMERAMANAGER->getCameraRect().top);
	if (!_connectedMap[3] || !_clear) _downWall->render(getMemDC(),
		CAMERAMANAGER->getDisplayCenterX() - 170 - CAMERAMANAGER->getCameraRect().left,
		_image->getHeight() - 240 - CAMERAMANAGER->getCameraRect().top);
}
