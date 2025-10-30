#include"TitleScene.h"

#include<DxLib.h>

#include"../../Application/Application.h"
#include"../SceneManager/SceneManager.h"
#include"../../Manager/Sound/SoundManager.h"
#include"../../Utility/Utility.h"

#include"GameEndScene/GameEndScene.h"

#include"../../Object/Stage/Purple/PurpleStage.h"
#include"Object/TitleShark.h"
#include"Object/TitleMonkfish.h"
#include"Object/TitlePlayer.h"

TitleScene::TitleScene():
	stage_(nullptr),
	fish_(nullptr),
	shark_(nullptr),
	player_(nullptr),
	rogoImg_(-1),
	arrowImg_(-1),
	selectImg_(),
	nowSelect_(SELECT::START),
	selectKey_(),
	deciKey_()
{
}

TitleScene::~TitleScene()
{
}

void TitleScene::Load(void)
{
	stage_ = new PurpleStage();
	stage_->Load();

	Utility::LoadImg(rogoImg_, "Data/Image/Title/ƒƒS•¶Žš.png");

	fish_ = new TitleMonkfish();
	fish_->Load();

	shark_ = new TitleShark();
	shark_->Load();
	
	player_ = new TitlePlayer();
	player_->Load();

	Utility::LoadImg(selectImg_[(int)SELECT::START], "Data/Image/Title/PushToStart.png");
	Utility::LoadImg(selectImg_[(int)SELECT::END], "Data/Image/Title/PushToEnd.png");
	Utility::LoadImg(arrowImg_, "Data/Image/Effect/Arrow.png");

	Smng::GetIns().Load(SOUND::BGM_TITLE);
}
void TitleScene::Init(void)
{
	stage_->Init();
	fish_->Init();
	shark_->Init();
	player_->Init();

	nowSelect_ = SELECT::START;

	Smng::GetIns().Play(SOUND::BGM_TITLE, true, 150, true);
}
void TitleScene::Update(void)
{
	Input();

	stage_->Update();
	fish_->Update();
	shark_->Update();
	player_->Update();

	if (selectKey_.down) { nowSelect_ = (SELECT)(1 - (int)nowSelect_); Smng::GetIns().Play(SOUND::SELECT, true, 100); }

	if (deciKey_.down) {
		switch (nowSelect_)
		{
		case TitleScene::SELECT::START:
			SceneManager::GetInstance().ChangeScene(SCENE_ID::SELECT);
			break;
		case TitleScene::SELECT::END:
			Smng::GetIns().AllStop();
			SceneManager::GetInstance().PushScene(std::make_shared< GameEndScene>());
			break;
		}
		Smng::GetIns().Play(SOUND::BUTTON, true, 100);
		return;
	}
}
void TitleScene::Draw(void)
{
	using app = Application;
	int xx = app::SCREEN_SIZE_X;
	int yy = app::SCREEN_SIZE_Y;
	int x = xx / 2;
	int y = yy / 2;

	stage_->Draw();
	fish_->Draw();
	shark_->Draw();
	player_->Draw();

	int selectPosX = TitlePlayer::POS_X + (TitlePlayer::SIZE_X / 2 + (TitlePlayer::HUKIDASI_SIZE_X / 2 + 20));
	int selectPosY = TitlePlayer::POS_Y;
	DrawRotaGraph(selectPosX, selectPosY, 0.75, 0, selectImg_[(int)nowSelect_], true);
	DrawRotaGraph(selectPosX + 320 / 2, selectPosY, 1, 0, arrowImg_, true, false);
	DrawRotaGraph(selectPosX - 320 / 2, selectPosY, 1, 0, arrowImg_, true, true);

	DrawRotaGraph(xx - 400, yy - 150, 1, 0, rogoImg_, true);
}

void TitleScene::Release(void)
{
	Smng::GetIns().Delete(SOUND::BGM_TITLE);

	DeleteGraph(arrowImg_);
	for (auto& id : selectImg_) { DeleteGraph(id); }

	if (player_) {
		player_->Release();
		delete player_;
		player_ = nullptr;
	}
	if (shark_) {
		shark_->Release();
		delete shark_;
		shark_ = nullptr;
	}
	if (fish_) {
		fish_->Release();
		delete fish_;
		fish_ = nullptr;
	}
	if (stage_) {
		stage_->Release();
		delete stage_;
		stage_ = nullptr;
	}
}


void TitleScene::Input(void)
{
	int input = GetJoypadInputState(DX_INPUT_PAD1);

	selectKey_.prev = selectKey_.now;
	selectKey_.now = (

		(CheckHitKey(KEY_INPUT_LEFT) == 0) &&
		(CheckHitKey(KEY_INPUT_A) == 0) &&
		((input & PAD_INPUT_LEFT) == 0) &&

		(CheckHitKey(KEY_INPUT_RIGHT) == 0) &&
		(CheckHitKey(KEY_INPUT_D) == 0 &&
		((input & PAD_INPUT_RIGHT) == 0))

		) ? false : true;
	selectKey_.down = (!selectKey_.prev && selectKey_.now);
	selectKey_.up = (selectKey_.prev && !selectKey_.now);


	deciKey_.prev = deciKey_.now;
	deciKey_.now = (
		(CheckHitKey(KEY_INPUT_SPACE) == 0) &&
		(CheckHitKey(KEY_INPUT_RETURN) == 0) &&
		((input & PAD_INPUT_B) == 0) &&
		((input & PAD_INPUT_A) == 0)
		) ? false : true;
	deciKey_.down = (!deciKey_.prev && deciKey_.now);
	deciKey_.up = (deciKey_.prev && !deciKey_.now);
}