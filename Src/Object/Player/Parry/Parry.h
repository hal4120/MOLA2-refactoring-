#pragma once

#include"../../UnitBase.h"

class Parry : UnitBase
{
public:
	static constexpr int ANIM_NUM_X = 11;
	static constexpr int ANIM_NUM_Y = 1;
	static constexpr int ANIM_NUM_ALL = ANIM_NUM_X * ANIM_NUM_Y;

	static constexpr int LOAD_SIZE_X = 75;
	static constexpr int LOAD_SIZE_Y = 100;

	static constexpr int COUNT_SPEED = 0;

	Parry();
	~Parry();

	void Load(void)override;
	void Init(void)override;
	void Update(void)override;
	void Draw(void)override;
	void Release(void)override;

	void On(void) { unit_.isAlive_ = true; }
	void takePlayerPosPtr(const Vector2& playerPos) { player_ = &playerPos; }

private:
	int img_[ANIM_NUM_ALL];

	int counter_;
	int countInterval_;

	const Vector2* player_;
};

