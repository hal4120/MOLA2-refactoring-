#pragma once

#include"../../../../UnitBase.h"

class Involute : public UnitBase
{
public:
	Involute(std::vector<int>image,int arrowImg);
	~Involute();

	void Load(void)override;
	void Init(void)override;
	void Update(void)override;
	void Draw(void)override;
	void Release(void)override;

	void OnCollision(UnitBase* other)override;

	void On(Vector2 bossPos);

private:
	std::vector<int>image_;

	float angle_;

	Vector2 parryVec_;

	Vector2 centerPos_;

	float centerDiff_;

	VECTOR DrawDiff = { 0.0f,-20.0f,0.0f };

	int arrowImg_;
	float arrowAngle_;
	bool arrow_;

	const float PARRY_SPEED = 15.0f;

	const int ANIME_INTERVAL = 5;
	int animeInterval_;
	int animeCounter_;
	void Animation(void);
};