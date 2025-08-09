#pragma once

#include"../../../../UnitBase.h"

class Mizu : public UnitBase
{
public:
	static constexpr int SIZE = 140;
	static constexpr float CENTER_X = 600.0f;
	static constexpr float CENTER_Y = 500.0f;
	static constexpr float SCALE = 0.2f;
	static constexpr float SPEED = 5.0f;

	static constexpr int SHOT_TIME = 60;

	static constexpr float PARRY_SPEED = 20.0f;

	Mizu(const Vector2& bossPos,const Vector2& playerPos);
	~Mizu()override;

	void Load(void)override;
	void Init(void)override;
	void Update(void)override;
	void Draw(void)override;
	void Release(void)override;

	void OnCollision(UnitBase* other)override;
	
	void On(void);
	bool End(void);

private:
	int img_;

	Vector2 moveVec_;

	float angle_;

	int counter_;
	bool shot_;

	int arrowImg_;
	float arrowAngle_;
	bool arrow_;

	const Vector2& bossPos_;
	const Vector2& playerPos_;
};
