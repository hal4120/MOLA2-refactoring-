#pragma once
#include"../SceneBase.h"

class StageBase;
class ClearPlayer;

class ClearScene : public SceneBase
{
public:
	static constexpr int GAME_CLEAR_IMG_LOAD_SIZE_X = 1500;
	static constexpr int GAME_CLEAR_IMG_LOAD_SIZE_Y = 410;

	static constexpr int TIME_FRAME_IMG_LOAD_SIZE_X = 865;
	static constexpr int TIME_FRAME_IMG_LOAD_SIZE_Y = 525;
	static constexpr int TIME_FRAME_POS_Y = 600;


	ClearScene();
	~ClearScene();

	void Load(void)override;
	void Init(void)override;
	void Update(void)override;
	void Draw(void)override;
	void Release(void)override;

private:
	int gameClearImg_;
	int timeFrameImg_;

	int rankImg_;

	StageBase* stage_;
	ClearPlayer* player_;
};

