#pragma once
#include"Involute.h"

class InvoluteShooter
{
public:
	static constexpr int ONE_SHOT_NUM = 12;

	static constexpr int ANIME_NUM = 4;

	static constexpr VECTOR LOCAL_POS = { 30.0f,0.0f,0.0f };

	InvoluteShooter();
	~InvoluteShooter();

	void Load(void);
	void Update(void);
	void Draw(void);
	void Release(void);

	void On(void);

private:
	std::vector<int>image_;
	std::vector<Involute*>involute_;
};