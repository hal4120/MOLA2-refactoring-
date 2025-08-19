#include"ClearScene.h"

#include<DxLib.h>

#include"../../Utility/Utility.h"
#include"../../Manager/Score/Score.h"
#include"../../Application/Application.h"
#include"../SceneManager/SceneManager.h"
#include"../../Manager/Sound/SoundManager.h"

#include"Object/ClearPlayer.h"
#include"../../Object/Stage/Old/OldStage.h"
#include"../../Object/Stage/Blue/BlueStage.h"

ClearScene::ClearScene():
	gameClearImg_(-1),
	timeFrameImg_(-1),
	rankImg_(-1),
	stage_(nullptr),
	player_(nullptr)
{
}

ClearScene::~ClearScene()
{
}

void ClearScene::Load(void)
{
	Utility::LoadImg(gameClearImg_, "Data/Image/Clear/GameClear.png");
	Utility::LoadImg(timeFrameImg_, "Data/Image/Clear/TimeFrame.png");

	auto score = Score::GetIns().GetNowScore();
	if (score.newRecord_) {
		Utility::LoadImg(rankImg_, "Data/Image/Clear/Rank/" + std::to_string(score.rank_) + ".png");
	}

	stage_ = new BlueStage();
	stage_->Load();

	player_ = new ClearPlayer();
	player_->Load();

	Smng::GetIns().Load(SOUND::CLEAR);
}

void ClearScene::Init(void)
{
	stage_->Init();
	player_->Init();

	Smng::GetIns().Play(SOUND::CLEAR);
}

void ClearScene::Update(void)
{
	stage_->Update();
	player_->Update();



	if (CheckHitKeyAll()) { SceneManager::GetInstance().ChangeScene(SCENE_ID::TITLE); }
}

void ClearScene::Draw(void)
{
	using app = Application;
	int xx = app::SCREEN_SIZE_X;
	int yy = app::SCREEN_SIZE_Y;
	int x = xx / 2;
	int y = yy / 2;

	stage_->Draw();

	DrawRotaGraph(x, TIME_FRAME_POS_Y, 1, 0, timeFrameImg_, true);

	auto score = Score::GetIns().GetNowScore();
	SetFontSize(140);
	DrawFormatString(x - 240, y + 120, 0x5555ff, "%.2fs", score.score_);
	SetFontSize(16);

	if (score.newRecord_) {
		static size_t Blinking = 0;
		if (++Blinking > 60000) { Blinking = 0; }
		if (Blinking / 8 % 2 == 0) { SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150); }
		DrawRotaGraph(x + TIME_FRAME_IMG_LOAD_SIZE_X / 3, TIME_FRAME_POS_Y - TIME_FRAME_IMG_LOAD_SIZE_Y / 3, 2, Utility::Deg2RadF(20.0f), rankImg_, true);
		if (Blinking / 8 % 2 == 0) { SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0); }
	}

	player_->Draw();

	DrawRotaGraph(x, GAME_CLEAR_IMG_LOAD_SIZE_Y / 2, 1, 0, gameClearImg_, true);
}

void ClearScene::Release(void)
{
	Smng::GetIns().Delete(SOUND::CLEAR);

	if (player_) {
		player_->Release();
		delete player_;
		player_ = nullptr;
	}
	if (stage_) {
		stage_->Release();
		delete stage_;
		stage_ = nullptr;
	}

	DeleteGraph(timeFrameImg_);
	DeleteGraph(gameClearImg_);
}