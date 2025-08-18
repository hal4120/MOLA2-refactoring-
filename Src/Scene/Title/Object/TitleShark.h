#pragma once

#include<vector>

class TitleShark
{
public:
	static constexpr int LOAD_SIZE = 96;
	static constexpr float DRAW_SCALE = 10.0f;

	static constexpr int ANIME_NUM = 6;
	static constexpr int ANIME_INTERVAL = 10;

	static constexpr int POS_X = 1300;
	static constexpr int POS_Y = 250;


	static constexpr int LASER_LOAD_SIZE_X = 1500;
	static constexpr int LASER_LOAD_SIZE_Y = 66;
	static constexpr float LASER_DRAW_SCALE = 3.0f;

	static constexpr int LASER_ANIME_NUM = 8;
	static constexpr int LASER_ANIME_INTERVAL = 5;

	static constexpr int LASER_POS_X = 900;
	static constexpr int LASER_POS_Y = 350;


	TitleShark();
	~TitleShark();

	void Load(void);
	void Init(void);
	void Update(void);
	void Draw(void);
	void Release(void);

private:
	int img_[ANIME_NUM];

	int animeCounter_;
	int animeInterval_;

	int laserImg_[LASER_ANIME_NUM];
	int laserCounter_;
	int laserInterval_;
};