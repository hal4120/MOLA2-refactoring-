#include"TitleScene.h"

#include<DxLib.h>

#include"../../Application/Application.h"
#include"../SceneManager/SceneManager.h"
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
	prevSelectKey_(false),
	nowSelectKey_(false),
	downSelectKey_(false),
	upSelectKey_(false),
	prevDeciKey_(false),
	nowDeciKey_(false),
	downDeciKey_(false),
	upDeciKey_(false)
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
}
void TitleScene::Init(void)
{
	stage_->Init();
	fish_->Init();
	shark_->Init();
	player_->Init();

	nowSelect_ = SELECT::START;
}
void TitleScene::Update(void)
{
	Input();

	stage_->Update();
	fish_->Update();
	shark_->Update();
	player_->Update();

	if (downSelectKey_) { nowSelect_ = (SELECT)(1 - (int)nowSelect_); }

	if (downDeciKey_) {
		switch (nowSelect_)
		{
		case TitleScene::SELECT::START:
			SceneManager::GetInstance().ChangeScene(SCENE_ID::SELECT);
			break;
		case TitleScene::SELECT::END:
			SceneManager::GetInstance().PushScene(std::make_shared< GameEndScene>());
			break;
		}
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
	prevSelectKey_ = nowSelectKey_;
	nowSelectKey_ = (
		(CheckHitKey(KEY_INPUT_LEFT) == 0) &&
		(CheckHitKey(KEY_INPUT_RIGHT) == 0))
		? false : true;
	downSelectKey_ = (!prevSelectKey_ && nowSelectKey_);
	upSelectKey_ = (prevSelectKey_ && !nowSelectKey_);


	prevDeciKey_ = nowDeciKey_;
	nowDeciKey_ = (
		(CheckHitKey(KEY_INPUT_SPACE) == 0) &&
		(CheckHitKey(KEY_INPUT_RETURN) == 0)
		) ? false : true;
	downDeciKey_ = (!prevDeciKey_ && nowDeciKey_);
	upDeciKey_ = (prevDeciKey_ && !nowDeciKey_);
}