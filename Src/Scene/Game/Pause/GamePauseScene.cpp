#include "GamePauseScene.h"

#include"../../../Utility/Utility.h"

#include"../../../Manager/Sound/SoundManager.h"

#include"../../../Application/Application.h"
#include"../../SceneManager/SceneManager.h"

GamePauseScene::GamePauseScene():
	img_(-1),
	maboImg_(),
	animeCounter_(0),
	animeInterval_(0),
	pauseKey_(),
	upKey_(),
	downKey_(),
	deciKey_(),
	nowSelect_(PAUSE_SELECT::NON)
{
}

GamePauseScene::~GamePauseScene()
{
}



void GamePauseScene::Load(void)
{
	Utility::LoadImg(img_, "Data/Image/Pause.png");

	Utility::LoadArrayImg("Data/Image/Player/‚Ü‚Ú.png",
		MABO_ANIME_NUM, MABO_ANIME_NUM, 1,
		MABO_LOAD_SIZE_X, MABO_LOAD_SIZE_Y, maboImg_);
}

void GamePauseScene::Init(void)
{
	animeCounter_ = 0;
	animeInterval_ = 0;

	pauseKey_.prev = pauseKey_.now = true;
	upKey_.prev = upKey_.now = true;
	downKey_.prev = downKey_.now = true;
	deciKey_.prev = deciKey_.now = true;

	nowSelect_ = PAUSE_SELECT::PLAY;

	Smng::GetIns().AllStop();
}

void GamePauseScene::Update(void)
{
	Input();

	if (pauseKey_.down) {
		Smng::GetIns().Play(SOUND::BUTTON, true);
		Smng::GetIns().PausePlay();
		SceneManager::GetInstance().PopScene();
		return;
	}

	switch (nowSelect_)
	{
	case GamePauseScene::PAUSE_SELECT::PLAY:
		if (downKey_.down) {
			nowSelect_ = PAUSE_SELECT::REPLAY;
			Smng::GetIns().Play(SOUND::SELECT, true);
		}
		break;
	case GamePauseScene::PAUSE_SELECT::REPLAY:
		if (upKey_.down) {
			nowSelect_ = PAUSE_SELECT::PLAY;
			Smng::GetIns().Play(SOUND::SELECT, true);
		}
		if (downKey_.down) {
			nowSelect_ = PAUSE_SELECT::TITLE;
			Smng::GetIns().Play(SOUND::SELECT, true);
		}
		break;
	case GamePauseScene::PAUSE_SELECT::TITLE:
		if (upKey_.down) {
			nowSelect_ = PAUSE_SELECT::REPLAY;
			Smng::GetIns().Play(SOUND::SELECT, true);
		}
		break;
	}

	if (deciKey_.down) {

		switch (nowSelect_)
		{
		case GamePauseScene::PAUSE_SELECT::PLAY:
			SceneManager::GetInstance().PopScene();
			break;
		case GamePauseScene::PAUSE_SELECT::REPLAY:
			SceneManager::GetInstance().JumpScene(SCENE_ID::GAME);
			break;
		case GamePauseScene::PAUSE_SELECT::TITLE:
			SceneManager::GetInstance().JumpScene(SCENE_ID::TITLE);
			break;
		}
		Smng::GetIns().Play(SOUND::BUTTON, true);

		return;
	}

	if (++animeInterval_ >= MABO_ANIME_INTERVAL) {
		animeInterval_ = 0;
		if (++animeCounter_ >= MABO_ANIME_NUM) {
			animeCounter_ = 0;
		}
	}

}

void GamePauseScene::Draw(void)
{
	using app = Application;
	int xx = app::SCREEN_SIZE_X;
	int yy = app::SCREEN_SIZE_Y;
	int x = xx / 2;
	int y = yy / 2;

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);
	DrawBox(0, 0, xx, yy, 0x808080, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	DrawRotaGraph(x, y, 1, 0, img_, true);

	DrawRotaGraph(POS_X, POS_Y[(int)nowSelect_], MABO_DRAW_SCALE, 0, maboImg_[animeCounter_], true);
}

void GamePauseScene::Release(void)
{
	for (auto& id : maboImg_) { DeleteGraph(id); }
	DeleteGraph(img_);
}

void GamePauseScene::Input(void)
{
	int input = GetJoypadInputState(DX_INPUT_PAD1);
	XINPUT_STATE state = {};
	if (GetJoypadXInputState(DX_INPUT_PAD1, &state) != 0) { state = {}; }

	pauseKey_.prev = pauseKey_.now;
	pauseKey_.now = (
		(CheckHitKey(KEY_INPUT_ESCAPE) == 0) &&
		(state.Buttons[XINPUT_BUTTON_START] == 0)
		) ? false : true;
	pauseKey_.down = (!pauseKey_.prev && pauseKey_.now) ? true : false;
	pauseKey_.up = (pauseKey_.prev && !pauseKey_.now) ? true : false;


	upKey_.prev = upKey_.now;
	upKey_.now = (
		(CheckHitKey(KEY_INPUT_UP) == 0) &&
		(CheckHitKey(KEY_INPUT_W) == 0) &&
		((input & PAD_INPUT_UP) == 0)
		) ? false : true;
	upKey_.down = (!upKey_.prev && upKey_.now) ? true : false;
	upKey_.up = (upKey_.prev && !upKey_.now) ? true : false;


	downKey_.prev = downKey_.now;
	downKey_.now = (
		(CheckHitKey(KEY_INPUT_DOWN) == 0) &&
		(CheckHitKey(KEY_INPUT_S) == 0) &&
		((input & PAD_INPUT_DOWN) == 0)
		) ? false : true;
	downKey_.down = (!downKey_.prev && downKey_.now) ? true : false;
	downKey_.up = (downKey_.prev && !downKey_.now) ? true : false;


	deciKey_.prev = deciKey_.now;
	deciKey_.now = (
		(CheckHitKey(KEY_INPUT_SPACE) == 0) &&
		(CheckHitKey(KEY_INPUT_RETURN) == 0) &&
		((input & PAD_INPUT_B) == 0) &&
		((input & PAD_INPUT_A) == 0)
		) ? false : true;
	deciKey_.down = (!deciKey_.prev && deciKey_.now) ? true : false;
	deciKey_.up = (deciKey_.prev && !deciKey_.now) ? true : false;

}
