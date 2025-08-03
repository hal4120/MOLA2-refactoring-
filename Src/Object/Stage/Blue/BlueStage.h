#pragma once

#include"../StageBase.h"

class BlueStage : public StageBase
{
public:
	static constexpr int BACK_SIZE_X = 1632;
	static constexpr int BACK_SIZE_Y = 960;
	static constexpr float SCROLL_SPEED = 3.0f;

	static constexpr int BIG_PLANET_SIZE = 258;
	static constexpr int BIG_PLANET_NUM = 2;
	static constexpr float BIG_PLANET_MAX_SPEED = 3.0f;

	static constexpr int SMALL_PLANET_SIZE = 96;
	static constexpr int SMALL_PLANET_NUM = 5;
	static constexpr float SMALL_PLANET_MAX_SPEED = 5.0f;

	BlueStage();
	~BlueStage();

	void Load(void)override;

};
