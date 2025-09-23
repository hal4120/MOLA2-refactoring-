#pragma once

#include<DxLib.h>

class ClearPlayer
{
public:
	static constexpr int LOAD_SIZE_X = 42;
	static constexpr int LOAD_SIZE_Y = 66;

	static constexpr int ANIME_NUM = 7;
	static constexpr int ANIME_INTERVAL = 5;

	static constexpr int PLAYER_NUM = 2;

	static constexpr int POS_X[PLAYER_NUM] = { 210,1410 };
	static constexpr int POS_Y = 625;

	static constexpr float DEFAULT_ANGLE[PLAYER_NUM] = { -15.0f * (DX_PI_F / 180.0f),15.0f * (DX_PI_F / 180.0f) };

	ClearPlayer();
	~ClearPlayer();

	void Load(void);
	void Init(void);
	void Update(void);
	void Draw(void);
	void Release(void);

private:
	int img_[ANIME_NUM];
	int animeCounter_;
	int animeInterval_;

	float angle_;
};