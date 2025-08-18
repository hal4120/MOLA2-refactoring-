#include"BlueStage.h"

BlueStage::BlueStage()
{
}

BlueStage::~BlueStage()
{
}

void BlueStage::Load(void)
{
	backSizeX = BACK_SIZE_X;
	backSizeY = BACK_SIZE_Y;
	backScrollSpeed = SCROLL_SPEED;
	Utility::LoadImg(backImg_, "Data/Image/Stage/Blue/Back.png");

	backDecorationScrollSpeed = BACK_DECRATION_SCROLL_SPEED;
	Utility::LoadImg(backDecorationImg_, "Data/Image/Stage/Blue/Stars.png");

	NewObject("Data/Image/Stage/Blue/PlanetBig.png", BIG_PLANET_SIZE, BIG_PLANET_SIZE, BIG_PLANET_NUM, BIG_PLANET_MAX_SPEED);

	NewObject("Data/Image/Stage/Blue/PlanetSmall.png", SMALL_PLANET_SIZE, SMALL_PLANET_SIZE, SMALL_PLANET_NUM, SMALL_PLANET_MAX_SPEED);
}