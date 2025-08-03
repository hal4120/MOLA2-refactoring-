#pragma once

#include "../UnitBase.h"

#include"../../Application/Application.h"

class EnemyBase : public UnitBase
{
public:
	enum NUMBER { ONE, TWO, THREE, FOUR, FIVE, MAX };

	const Vector2 RES_POS[NUMBER::MAX] =
	{
		{Application::SCREEN_SIZE_X + (unit_.para_.size.x / 2.0f),
		(Application::SCREEN_SIZE_Y / NUMBER::MAX) * 1 - (Application::SCREEN_SIZE_Y / NUMBER::MAX / 2)},

		{Application::SCREEN_SIZE_X + (unit_.para_.size.x / 2.0f),
		(Application::SCREEN_SIZE_Y / NUMBER::MAX) * 2 - (Application::SCREEN_SIZE_Y / NUMBER::MAX / 2)},

		{Application::SCREEN_SIZE_X + (unit_.para_.size.x / 2.0f),
		(Application::SCREEN_SIZE_Y / NUMBER::MAX) * 3 - (Application::SCREEN_SIZE_Y / NUMBER::MAX / 2)},

		{Application::SCREEN_SIZE_X + (unit_.para_.size.x / 2.0f),
		(Application::SCREEN_SIZE_Y / NUMBER::MAX) * 4 - (Application::SCREEN_SIZE_Y / NUMBER::MAX / 2)},

		{Application::SCREEN_SIZE_X + (unit_.para_.size.x / 2.0f),
		(Application::SCREEN_SIZE_Y / NUMBER::MAX) * 5 - (Application::SCREEN_SIZE_Y / NUMBER::MAX / 2)}
	};

	static constexpr float PARRY_SPEED = 20.0f;

	EnemyBase(NUMBER num);
	virtual ~EnemyBase() {};

	virtual void Load(void)override;
	virtual void Init(void)override;
	virtual void Update(void)override;
	virtual void Draw(void)override;
	virtual void Release(void)override;

	virtual void OnCollision(UnitBase* other)override;

	bool GetParry(void) { return parry_; }

protected:
	NUMBER number_;

	std::vector<int>imgs_;

	int animSpeed;

	int animCounter_;
	int animInterval_;

	int respawnCounter_;
	int respawnTime;

	Vector2 moveVec_;

	int arrowImg_;
	float arrowAngle_;
	bool arrow_;

	bool parry_;

	virtual void Move(void);
	virtual void Respawn(void);
	virtual void Animation(void);
};

using NUMBER = EnemyBase::NUMBER;