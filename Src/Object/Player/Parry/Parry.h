#pragma once

#include"../../UnitBase.h"

#include <functional>


class Parry : public UnitBase
{
public:
	static constexpr int ANIM_NUM_X = 11;
	static constexpr int ANIM_NUM_Y = 1;
	static constexpr int ANIM_NUM_ALL = ANIM_NUM_X * ANIM_NUM_Y;

	static constexpr int LOAD_SIZE_X = 75;
	static constexpr int LOAD_SIZE_Y = 100;

	static constexpr int COUNT_SPEED = 0;

	static constexpr float DEFAULT_MAG = 1.0f;
	static constexpr float MAG_ONE_SIZE_UP = 0.2f;
	static constexpr float MAX_MAG = 2.0f;

	static constexpr int COOL_TIME = 60;
	static constexpr float COOL_TIME_DRAW_SIZE_Y = 5.0f;

	Parry(const Vector2& playerPos);
	~Parry();

	void Load(void)override;
	void Init(void)override;
	void Update(void)override;
	void Draw(void)override;
	void Release(void)override;

	void OnCollision(UnitBase* other);

	void On(void);

	void MagReset(void) { mag_ = DEFAULT_MAG; unit_.para_.radius = LOAD_SIZE_X; }

	void SetSpChargeFun(std::function<void(void)>ptr) { spChargeFunPtr_ = std::move(ptr); }
private:
	int img_[ANIM_NUM_ALL];

	int counter_;
	int countInterval_;

	int coolTime_;

	float mag_;

	const Vector2& player_;
	std::function<void(void)>spChargeFunPtr_;
};

