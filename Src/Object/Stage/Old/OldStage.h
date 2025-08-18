#pragma once

#include"../StageBase.h"

class OldStage : public StageBase
{
public:
	static constexpr int BACK_SIZE_X = 1632;
	static constexpr int BACK_SIZE_Y = 960;
	static constexpr float SCROLL_SPEED = 3.0f;

	static constexpr float BACK_DECRATION_SCROLL_SPEED = 4.0f;

	static constexpr int OBJ_1_SIZE = 528;
	static constexpr int OBJ_1_NUM = 3;
	static constexpr float OBJ_1_MAX_SPEED = 3.0f;

	static constexpr int OBJ_2_SIZE_X = 306;
	static constexpr int OBJ_2_SIZE_Y = 690;
	static constexpr int OBJ_2_NUM = 2;
	static constexpr float OBJ_2_MAX_SPEED = 5.0f;

	static constexpr int OBJ_3_SIZE_X = 1632;
	static constexpr int OBJ_3_SIZE_Y = 960;
	static constexpr int OBJ_3_NUM = 5;
	static constexpr float OBJ_3_MAX_SPEED = 1.0f;

	OldStage();
	~OldStage();

	void Load(void)override;
};

