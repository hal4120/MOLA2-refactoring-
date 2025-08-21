#include"GreenStage.h"
GreenStage::GreenStage()
{
}

GreenStage::~GreenStage()
{
}

void GreenStage::Load(void)
{
	backSizeX = BACK_SIZE_X;
	backSizeY = BACK_SIZE_Y;
	backScrollSpeed = SCROLL_SPEED;
	Utility::LoadImg(backImg_, "Data/Image/Stage/Green/Back.png");

	backDecorationScrollSpeed = BACK_DECRATION_SCROLL_SPEED;
	Utility::LoadImg(backDecorationImg_, "Data/Image/Stage/Green/BackDecoration.png");

	NewObject("Data/Image/Stage/Green/Object1.png", OBJECT_ONE_SIZE_X, OBJECT_ONE_SIZE_Y, OBJECT_ONE_NUM, OBJECT_ONET_MAX_SPEED);

	NewObject("Data/Image/Stage/Green/Object2.png", OBJECT_TWO_SIZE_X, OBJECT_TWO_SIZE_Y, OBJECT_TWO_NUM, OBJECT_TWO_MAX_SPEED);

	NewObject("Data/Image/Stage/Green/Object3.png", OBJECT_THREE_SIZE_X, OBJECT_THREE_SIZE_Y, OBJECT_THREE_NUM, OBJECT_THREE_MAX_SPEED);

	NewObject("Data/Image/Stage/Green/Object4.png", OBJECT_FOUR_SIZE_X, OBJECT_FOUR_SIZE_Y, OBJECT_FOUR_NUM, OBJECT_FOUR_MAX_SPEED);

	NewObject("Data/Image/Stage/Green/Object5.png", OBJECT_FIVE_SIZE_X, OBJECT_FIVE_SIZE_Y, OBJECT_FIVE_NUM, OBJECT_FIVE_MAX_SPEED);
}