#pragma once

#include"../EnemyBase.h"

class Ika :public EnemyBase
{
public:
	static constexpr int SIZE_X = 100;
	static constexpr int SIZE_Y = 98;

	static constexpr float MOVE_SPEED = 5.0f;

	static constexpr int RESPAWN_TIME = 100;

	Ika(NUMBER num);
	~Ika();

	void Load(void)override;

	void OnCollision(UnitBase* other)override;

private:
	void Move(void)override;

	void Respawn(void)override;
};