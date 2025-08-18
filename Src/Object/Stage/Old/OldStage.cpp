#include "OldStage.h"

OldStage::OldStage()
{
}

OldStage::~OldStage()
{
}


void OldStage::Load(void)
{
	backSizeX = BACK_SIZE_X;
	backSizeY = BACK_SIZE_Y;
	backScrollSpeed = SCROLL_SPEED;
	Utility::LoadImg(backImg_, "Data/Image/Stage/Old/Back.png");

	backDecorationScrollSpeed = BACK_DECRATION_SCROLL_SPEED;
	Utility::LoadImg(backDecorationImg_, "Data/Image/Stage/Blue/BackDecoration.png");

	NewObject("Data/Image/Stage/Old/Obj1.png", OBJ_1_SIZE, OBJ_1_SIZE, OBJ_1_NUM, OBJ_1_MAX_SPEED);

	NewObject("Data/Image/Stage/Old/Obj2.png", OBJ_2_SIZE_X, OBJ_2_SIZE_Y, OBJ_2_NUM, OBJ_2_MAX_SPEED);

	NewObject("Data/Image/Stage/Old/Obj3.png", OBJ_3_SIZE_X, OBJ_3_SIZE_Y, OBJ_3_NUM, OBJ_3_MAX_SPEED);
}