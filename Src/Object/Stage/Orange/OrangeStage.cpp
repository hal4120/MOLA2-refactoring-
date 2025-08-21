#include "OrangeStage.h"

OrangeStage::OrangeStage()
{
}

OrangeStage::~OrangeStage()
{
}

void OrangeStage::Load(void)
{
	backSizeX = BACK_SIZE_X;
	backSizeY = BACK_SIZE_Y;
	backScrollSpeed = SCROLL_SPEED;
	Utility::LoadImg(backImg_, "Data/Image/Stage/Orange/Back.png");

	backDecorationScrollSpeed = BACK_DECRATION_SCROLL_SPEED;
	Utility::LoadImg(backDecorationImg_, "Data/Image/Stage/Orange/BackDecoration.png");

	NewObject("Data/Image/Stage/Orange/Object1.png", OBJECT_ONE_SIZE_X, OBJECT_ONE_SIZE_Y, OBJECT_ONE_NUM, OBJECT_ONET_MAX_SPEED);

	NewObject("Data/Image/Stage/Orange/Object2.png", OBJECT_TWO_SIZE_X, OBJECT_TWO_SIZE_Y, OBJECT_TWO_NUM, OBJECT_TWO_MAX_SPEED);

	NewObject("Data/Image/Stage/Orange/Object3.png", OBJECT_THREE_SIZE_X, OBJECT_THREE_SIZE_Y, OBJECT_THREE_NUM, OBJECT_THREE_MAX_SPEED);

	NewObject("Data/Image/Stage/Orange/Object4.png", OBJECT_FOUR_SIZE_X, OBJECT_FOUR_SIZE_Y, OBJECT_FOUR_NUM, OBJECT_FOUR_MAX_SPEED);

}