#pragma once

#include"../EnemyBase.h"

class CrayFish :public EnemyBase
{
public:
	static constexpr int SIZE_X = 64;
	static constexpr int SIZE_Y = 38;

	static constexpr float MOVE_SPEED = 5.0f;

	static constexpr int RESPAWN_TIME = 100;

	CrayFish(NUMBER num);
	~CrayFish();

	void Load(void)override;

	void OnCollision(UnitBase* other)override;

private:
	void Move(void)override;
};