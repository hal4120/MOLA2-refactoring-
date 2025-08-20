#pragma once


class SelectPlayer
{
public:
	static constexpr int LOAD_SIZE_X = 42;
	static constexpr int LOAD_SIZE_Y = 66;

	static constexpr float DRAW_SCALE = 3.0f;

	static constexpr int SIZE_X = (int)(LOAD_SIZE_X * DRAW_SCALE);
	static constexpr int SIZE_Y = (int)(LOAD_SIZE_Y * DRAW_SCALE);

	static constexpr int ANIME_NUM = 7;
	static constexpr int ANIME_INTERVAL = 10;

	static constexpr int POS_X = 100;
	static constexpr int POS_Y = 600;


	static constexpr int PARRY_LOAD_SIZE_X = 75;
	static constexpr int PARRY_LOAD_SIZE_Y = 100;

	static constexpr float PARRY_DRAW_SCALE = 3.0f;

	static constexpr int PARRY_SIZE_X = (int)(PARRY_LOAD_SIZE_X * PARRY_DRAW_SCALE);
	static constexpr int PARRY_SIZE_Y = (int)(PARRY_LOAD_SIZE_Y * PARRY_DRAW_SCALE);

	static constexpr int PARRY_ANIME_NUM = 11;
	static constexpr int PARRY_ANIME_INTERVAL = 0;

	SelectPlayer();
	~SelectPlayer();


	void Load(void);
	void Init(void);
	void Update(void);
	void Draw(void);
	void Release(void);


	bool Parry(void);

private:
	int img_[ANIME_NUM];
	int animeCounter_;
	int animeInterval_;

	int parryImg_[PARRY_ANIME_NUM];
	bool isParry_;
	int parryAnimeCounter_;
	int parryAnimeInterval_;


	struct KeyInfo { bool prev = false, now = false, down = false, up = false; };
	KeyInfo parryKey_;
	void Input(void);
};