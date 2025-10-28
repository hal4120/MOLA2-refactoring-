#pragma once

#include"../../../../UnitBase.h"

class Involute : public UnitBase
{
public:
	Involute(std::vector<int>image);
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

	bool parry_;

	Vector2 bossPos_;

	float radius_;

	const int ANIME_INTERVAL = 10;
	int animeInterval_;
	int animeCounter_;
	void Animation(void);
};