#pragma once
#include"../StageBase.h"

class GreenStage : public StageBase
{
public:

	static constexpr int BACK_SIZE_X = 1632;
	static constexpr int BACK_SIZE_Y = 960;
	static constexpr float SCROLL_SPEED = 3.0f;

	static constexpr float BACK_DECRATION_SCROLL_SPEED = 4.0f;

	static constexpr int OBJECT_ONE_SIZE_X = 312;
	static constexpr int OBJECT_ONE_SIZE_Y = 564;
	static constexpr int OBJECT_ONE_NUM = 1;
	static constexpr float OBJECT_ONET_MAX_SPEED = 3.0f;

	static constexpr int  OBJECT_TWO_SIZE_X = 294;
	static constexpr int  OBJECT_TWO_SIZE_Y = 288;
	static constexpr int OBJECT_TWO_NUM = 2;
	static constexpr float OBJECT_TWO_MAX_SPEED = 5.0f;

	static constexpr int  OBJECT_THREE_SIZE_X = 294;
	static constexpr int  OBJECT_THREE_SIZE_Y = 288;
	static constexpr int OBJECT_THREE_NUM = 2;
	static constexpr float OBJECT_THREE_MAX_SPEED = 5.0f;

	static constexpr int  OBJECT_FOUR_SIZE_X = 198;
	static constexpr int  OBJECT_FOUR_SIZE_Y = 144;
	static constexpr int OBJECT_FOUR_NUM = 5;
	static constexpr float OBJECT_FOUR_MAX_SPEED = 5.0f;

	static constexpr int  OBJECT_FIVE_SIZE_X = 144;
	static constexpr int  OBJECT_FIVE_SIZE_Y = 162;
	static constexpr int OBJECT_FIVE_NUM = 5;
	static constexpr float OBJECT_FIVE_MAX_SPEED = 5.0f;


	GreenStage();
	~GreenStage();

	void Load(void)override;
};

