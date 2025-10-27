#pragma once

#include"../../../../UnitBase.h"

class Sphere : public UnitBase
{
public:
	static constexpr float RADIUS = 30.0f;
	static constexpr int ANIME_NUM = 9;

	static constexpr int LOCK_ON_INTERVAL = 60;

	Sphere(std::vector<int> image, const Vector2& bossPos, const float& bossAngle, const Vector2& playerPos);
	~Sphere();

	void Load(void)override;
	void Init(void)override;
	void Update(void)override;
	void Draw(void)override;
	void Release(void)override;

	void OnCollision(UnitBase* other)override;

	void On(void);

	const bool End(void)const { return end_; }


private:
	std::vector<int> img_;
	int animeCounter_;
	int animeInterval_;

	Vector2 moveVec_;

	int lockOnInterval_;

	float rot_;

	int arrowImg_;
	float arrowAngle_;
	bool arrow_;

	bool end_;

	const Vector2& bossPos_;
	const float& bossAngle_;
	const Vector2& playerPos_;
};