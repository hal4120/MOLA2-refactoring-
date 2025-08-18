#pragma once


class TitlePlayer
{
public:
	static constexpr int LOAD_SIZE_X = 42;
	static constexpr int LOAD_SIZE_Y = 66;
	static constexpr float DRAW_SCALE = 3.0f;
	static constexpr int SIZE_X = (int)(LOAD_SIZE_X * DRAW_SCALE);
	static constexpr int SIZE_Y = (int)(LOAD_SIZE_Y * DRAW_SCALE);

	static constexpr int POS_X = 90;
	static constexpr int POS_Y = 800;

	static constexpr int ANIME_INTERVAL = 5;
	static constexpr int ANIME_NUM = 7;


	static constexpr int HUKIDASI_LOAD_SIZE_X = 1200;
	static constexpr int HUKIDASI_LOAD_SIZE_Y = 300;
	static constexpr float HUKIDASI_DRAW_SCALE_X = 0.43f;
	static constexpr float HUKIDASI_DRAW_SCALE_Y = 0.4f;
	static constexpr int HUKIDASI_SIZE_X = (int)(HUKIDASI_LOAD_SIZE_X * HUKIDASI_DRAW_SCALE_X);
	static constexpr int HUKIDASI_SIZE_Y = (int)(HUKIDASI_LOAD_SIZE_Y * HUKIDASI_DRAW_SCALE_Y);


	TitlePlayer();
	~TitlePlayer();

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

	int hukidasi_;
};