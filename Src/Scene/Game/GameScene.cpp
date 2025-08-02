#include"GameScene.h"

#include<DxLib.h>
#include<cmath>

#include"../../Application/Application.h"

#include"../../Object/Player/Player.h"

int GameScene::hitStop_ = 0;

int GameScene::shake_ = 0;
ShakeKinds GameScene::shakeKinds_ = ShakeKinds::DIAG;
ShakeSize GameScene::shakeSize_ = ShakeSize::MEDIUM;

GameScene::GameScene():
	mainScreen_(-1)
{
}

GameScene::~GameScene()
{
}

void GameScene::Load(void)
{
	mainScreen_ = MakeScreen(Application::SCREEN_SIZE_X, Application::SCREEN_SIZE_Y);

	player_ = new Player();
	player_->Load();

}
void GameScene::Init(void)
{
	player_->Init();

	// ヒットストップカウンターの初期化
	hitStop_ = 0;

	// 画面揺れ関係の初期化-----------------------------------------------------------
	shake_ = 0;
	shakeKinds_ = ShakeKinds::DIAG;
	shakeSize_ = ShakeSize::MEDIUM;;
	//--------------------------------------------------------------------------------
}
void GameScene::Update(void)
{
	if (hitStop_ > 0) { hitStop_--; return; }
	if (shake_ > 0) { shake_--; }

	player_->Update();

}
void GameScene::Draw(void)
{
	SetDrawScreen(mainScreen_);
	ClearDrawScreen();

	//描画処理-----------------------------------------
	using app = Application;
	int x = app::SCREEN_SIZE_X / 2;
	int y = app::SCREEN_SIZE_Y / 2;

	player_->Draw();


	//-------------------------------------------------

	SetDrawScreen(DX_SCREEN_BACK);

	Vector2I s = ShakePoint();
	DrawGraph(s.x, s.y, mainScreen_, true);
}
void GameScene::Release(void)
{
	player_->Release();

	DeleteGraph(mainScreen_);
}

void GameScene::Shake(ShakeKinds kinds, ShakeSize size, int time)
{
	if (abs(shake_ - time) > 10)shake_ = time;
	shakeKinds_ = kinds;
	shakeSize_ = size;
}

Vector2I GameScene::ShakePoint(void)
{
	Vector2I ret = {};

	if (shake_ > 0) {
		int size = shake_ / 5 % 2;
		size *= 2;
		size -= 1;
		switch (shakeKinds_)
		{
		case GameScene::WID:ret.x = size;
			break;
		case GameScene::HIG:ret.y = size;
			break;
		case GameScene::DIAG:ret = size;
			break;
		case GameScene::ROUND:
			size = shake_ / 3 % 12; size++;
			ret = { (int)((shakeSize_ * 1.5f) * cos(size * 30.0f)),(int)((shakeSize_ * 1.5f) * sin(size * 30.0f)) };
			break;
		}

		if (shakeKinds_ != ShakeKinds::ROUND) { ret *= shakeSize_; }

		DrawGraph(0, 0, mainScreen_, true);
	}

	return ret;
}
