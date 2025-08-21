#pragma once

#include"../StageBase.h"

class OrangeStage : public StageBase
{
public:
	static constexpr int BACK_SIZE_X = 1632;
	static constexpr int BACK_SIZE_Y = 960;
	static constexpr float SCROLL_SPEED = 3.0f;

	static constexpr float BACK_DECRATION_SCROLL_SPEED = 4.0f;

	static constexpr int OBJECT_ONE_SIZE_X = 360;
	static constexpr int OBJECT_ONE_SIZE_Y = 354;
	static constexpr int OBJECT_ONE_NUM = 2;
	static constexpr float OBJECT_ONET_MAX_SPEED = 3.0f;

	static constexpr int  OBJECT_TWO_SIZE_X = 366;
	static constexpr int  OBJECT_TWO_SIZE_Y = 156;
	static constexpr int OBJECT_TWO_NUM = 2;
	static constexpr float OBJECT_TWO_MAX_SPEED = 5.0f;

	static constexpr int  OBJECT_THREE_SIZE_X = 108;
	static constexpr int  OBJECT_THREE_SIZE_Y = 150;
	static constexpr int OBJECT_THREE_NUM = 5;
	static constexpr float OBJECT_THREE_MAX_SPEED = 5.0f;

	static constexpr int  OBJECT_FOUR_SIZE_X = 150;
	static constexpr int  OBJECT_FOUR_SIZE_Y = 114;
	static constexpr int OBJECT_FOUR_NUM = 5;
	static constexpr float OBJECT_FOUR_MAX_SPEED = 5.0f;

	OrangeStage();
	~OrangeStage();

	void Load(void)override;
};

