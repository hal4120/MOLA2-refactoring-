#pragma once
#include "../../../../UnitBase.h"

class Scissors : public UnitBase
{
public:


	static constexpr float RADIUS = 60.0f;

	Scissors(const Vector2& boss, const Vector2& player);
	~Scissors() override;

	void Load(void) override;
	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Release(void) override;

	void OnCollision(UnitBase* other) override;

	bool End(void) { return !end_; }

private:

	int img_;
	bool end_;

	int lifeTime_;

	const Vector2& bossPos_;
	const Vector2& playerPos_;
	Vector2 moveDir_;
};
