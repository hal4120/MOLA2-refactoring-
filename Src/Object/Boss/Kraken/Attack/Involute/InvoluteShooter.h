#pragma once
#include"Involute.h"

class InvoluteShooter
{
public:
	static constexpr int ONE_SHOT_NUM = 12;

	static constexpr int ANIME_NUM = 4;

	InvoluteShooter(const Vector2& bossPos, const float& bossAngle);
	~InvoluteShooter();

	void Load(void);
	void Update(void);
	void Draw(void);
	void Release(void);

	void On(void) { shotCount_ = ONE_SHOT_NUM; }

	bool End(void) { return shotCount_ <= 0; }

private:
	std::vector<int>image_;
	std::vector<Involute*>involute_;

	int shotCount_;

	const int SHOT_INTERVAL = 12;
	int shotInterval_;
	void Shot(void);

	const Vector2& bossPos;
	const float& bossAngle;
};