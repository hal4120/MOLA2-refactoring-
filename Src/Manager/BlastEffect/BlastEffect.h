#pragma once

#include<vector>

#include"../../Common/Vector2.h"

class BlastEffect
{
public:
	static constexpr int ANIME_SPEED = 0;

	BlastEffect();
	~BlastEffect();

	void Load(std::vector<int> image);
	void On(Vector2 pos);
	void Update(void);
	void Draw(void);
	void Release(void);

	const bool GetAlive(void)const { return isAlive_; }

private:
	std::vector<int> image_;
	bool isAlive_;
	Vector2 pos_;
	int animeCounter_;
	int animeInterval_;
};

