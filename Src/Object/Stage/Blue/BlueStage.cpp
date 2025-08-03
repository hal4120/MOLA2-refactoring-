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
	Utility::LoadImg(backDecorationImg_, "Data/Image/Stage/Blue/Stars.png");


	object1SizeX = BIG_PLANET_SIZE;
	object1SizeY = BIG_PLANET_SIZE;
	object1Num = BIG_PLANET_NUM;
	object1MaxSpeed = BIG_PLANET_MAX_SPEED;
	Utility::LoadImg(object1Img_, "Data/Image/Stage/Blue/PlanetBig.png");


	object2SizeX = SMALL_PLANET_SIZE;
	object2SizeY = SMALL_PLANET_SIZE;
	object2Num = SMALL_PLANET_NUM;
	object2MaxSpeed = SMALL_PLANET_MAX_SPEED;
	Utility::LoadImg(object2Img_, "Data/Image/Stage/Blue/PlanetSmall.png");
}