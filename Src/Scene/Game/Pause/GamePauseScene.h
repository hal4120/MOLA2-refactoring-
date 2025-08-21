#pragma once

#include"../../SceneBase.h"

class GamePauseScene : public SceneBase
{
public:

	GamePauseScene();
	~GamePauseScene()override;


	void Load(void)override;
	void Init(void)override;
	void Update(void)override;
	void Draw(void)override;
	void Release(void)override;

private:

	int img_;

	static constexpr int MABO_LOAD_SIZE_X = 42;;
	static constexpr int MABO_LOAD_SIZE_Y = 66;
	static constexpr float MABO_DRAW_SCALE = 3.0f;
	static constexpr int MABO_ANIME_NUM = 7;
	static constexpr int MABO_ANIME_INTERVAL = 10;
	int maboImg_[MABO_ANIME_NUM];
	int animeCounter_;
	int animeInterval_;

	enum class PAUSE_SELECT { NON = -1, PLAY, REPLAY, TITLE, MAX };
	PAUSE_SELECT nowSelect_;

	static constexpr int POS_X = 170;
	static constexpr int POS_Y[(int)PAUSE_SELECT::MAX] = { 395,610,820 };


	struct KeyInfo { bool down = false, up = false, prev = false, now = false; };
	KeyInfo pauseKey_;
	KeyInfo upKey_;
	KeyInfo downKey_;
	KeyInfo deciKey_;
	void Input(void);
};

