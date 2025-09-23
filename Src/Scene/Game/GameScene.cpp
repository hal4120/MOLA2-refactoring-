#include"GameScene.h"

#include<DxLib.h>
#include<cmath>

#include"../../Application/Application.h"
#include"../../scene/SceneManager/SceneManager.h"
#include"../../Manager/Sound/SoundManager.h"
#include"../../Manager/BlastEffect/BlastEffectManager.h"
#include"../../Manager/Score/Score.h"

#include"Pause/GamePauseScene.h"

#include"../StageSelect/SelectScene.h"

#include"../../Object/Player/Player.h"
#include"../../Object/Enemy/EnemyManager.h"
#include"../../Object/Stage/Blue/BlueStage.h"
#include"../../Object/Stage/Orange/OrangeStage.h"

#include"../../Object/Boss/Shark/Shark.h"
#include"../../Object/Boss/SharkHard/SharkHard.h"
#include"../../Object/Boss/Kraken/Kraken.h"

int GameScene::hitStop_ = 0;

int GameScene::slow_ = 0;
int GameScene::slowInter_ = 0;

int GameScene::shake_ = 0;
ShakeKinds GameScene::shakeKinds_ = ShakeKinds::DIAG;
ShakeSize GameScene::shakeSize_ = ShakeSize::MEDIUM;

GameScene::GameScene():
	mainScreen_(-1),
	collision_(nullptr),
	blast_(nullptr),
	player_(nullptr),
	stage_(nullptr),
	eMng_(nullptr),
	boss_(nullptr),
	pauseKey_(),
	time_(0.0f),
	enCounter_(0.0f)
{
}

GameScene::~GameScene()
{
}

void GameScene::Load(void)
{
	this->Release();

	mainScreen_ = MakeScreen(Application::SCREEN_SIZE_X, Application::SCREEN_SIZE_Y);

	collision_ = new Collision();

	blast_ = new BlastEffectManager();
	blast_->Load();

	auto kinds = SelectScene::GetNowBoss();
	
	
	player_ = new Player();
	player_->Load();
	collision_->Add(player_);
	collision_->Add(player_->ParryIns());
	collision_->Add(player_->LaserIns());


	switch (kinds)
	{
	case SelectScene::BOSS_KINDS::SHARK:

		stage_ = new BlueStage();

		boss_ = new Shark(player_->GetUnit().pos_);

		break;
	case SelectScene::BOSS_KINDS::SHARK_HARD:

		stage_ = new OrangeStage();

		boss_ = new SharkHard(player_->GetUnit().pos_);

		break;
	case SelectScene::BOSS_KINDS::KRAKEN:

		stage_ = new BlueStage();

		boss_ = new Kraken(player_->GetUnit().pos_);

		break;
	}

	stage_->Load();

	boss_->Load();
	collision_->Add(boss_);
	collision_->Add(boss_->AttackIns());

	eMng_ = new EnemyManager(kinds);
	eMng_->Load();
	collision_->Add(eMng_->GetEnemys());


	Smng::GetIns().Load(SOUND::BGM_BOSS);
	Smng::GetIns().Load(SOUND::BLAST);
	Smng::GetIns().Load(SOUND::GAME_END);
	Smng::GetIns().Load(SOUND::WARNING);
}

void GameScene::Init(void)
{
	stage_->Init();
	player_->Init();
	eMng_->Init();
	boss_->Init();

	time_ = 0.0f;

	enCounter_ = 0.0f;

	// ヒットストップカウンターの初期化
	hitStop_ = 0;

	// スローカウンターの初期化
	slow_ = 0;
	slowInter_ = 5;

	// 画面揺れ関係の初期化-----------------------------------------------------------
	shake_ = 0;
	shakeKinds_ = ShakeKinds::DIAG;
	shakeSize_ = ShakeSize::MEDIUM;
	//--------------------------------------------------------------------------------
}

void GameScene::Update(void)
{
	Input();

	if (pauseKey_.down) {
		SceneManager::GetInstance().PushScene(std::make_shared<GamePauseScene>());
		Smng::GetIns().Play(SOUND::SELECT, true);
		return;
	}


	if (hitStop_ > 0) { hitStop_--; return; }
	if (shake_ > 0) { shake_--; }
	if (slow_ > 0) {
		slow_--;
		if (slow_ % slowInter_ != 0) { return; }
	}


	stage_->Update();
	player_->Update();
	eMng_->Update();

	boss_->Update();

	collision_->Check();
	blast_->Update();


	if (boss_->GetEnCount()) {
		enCounter_ += 0.06f;
		if (enCounter_ >= 1000.0f) { enCounter_ = 0.0f; }
	}

	if (boss_->Timer()) { time_ += 1 / 60.0f; }

	if (player_->GameOver()) {
		SceneManager::GetInstance().ChangeScene(SCENE_ID::OVER);
		return;
	}

	if (boss_->End()) {
		Score::GetIns().SetScore(time_);
		SceneManager::GetInstance().ChangeScene(SCENE_ID::CLEAR);
		return;
	}
}

void GameScene::Draw(void)
{
	SetDrawScreen(mainScreen_);
	ClearDrawScreen();

	//描画処理-----------------------------------------
	using app = Application;
	int xx = app::SCREEN_SIZE_X;
	int yy = app::SCREEN_SIZE_Y;
	int x = xx / 2;
	int y = yy / 2;

	stage_->Draw();
	player_->Draw();
	eMng_->Draw();
	boss_->Draw();
	blast_->Draw();

	player_->UIDraw();
	boss_->DrawHp(0x00ff00, 0x000000, 0xffffff);

	int fontSize = 50;
	SetFontSize(fontSize);
	DrawFormatString(0, 0, 0xffffff, "TIME:%.2fs", time_);
	SetFontSize(16);


	if (boss_->GetEnCount()) {
		int al = (int)(abs(sinf(enCounter_) * 100) + 30);

		SetDrawBlendMode(DX_BLENDMODE_ALPHA, al);
		DrawBox(0, 0, xx, yy, 0xff0000, true); 
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
	//-------------------------------------------------

	SetDrawScreen(DX_SCREEN_BACK);

	Vector2I s = ShakePoint();
	DrawGraph(s.x, s.y, mainScreen_, true);
}

void GameScene::Release(void)
{
	Smng::GetIns().Delete(SOUND::BGM_BOSS);
	Smng::GetIns().Delete(SOUND::BLAST);
	Smng::GetIns().Delete(SOUND::GAME_END);
	Smng::GetIns().Delete(SOUND::WARNING);

	if (stage_) {
		stage_->Release();
		delete stage_;
		stage_ = nullptr;
	}
	if (player_) {
		player_->Release();
		delete player_;
		player_ = nullptr;
	}
	if (eMng_) {
		eMng_->Release();
		delete eMng_;
		eMng_ = nullptr;
	}
	if (boss_) {
		boss_->Release();
		delete boss_;
		boss_ = nullptr;
	}

	if (blast_) {
		blast_->Release();
		delete blast_;
		blast_ = nullptr;
	}

	if (collision_) {
		collision_->Clear();
		delete collision_;
		collision_ = nullptr;
	}

	DeleteGraph(mainScreen_);
}


void GameScene::Input(void)
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


}

void GameScene::Shake(ShakeKinds kinds, ShakeSize size, int time)
{
	if ((abs(shake_ - time) > 10) || shake_ <= 0)shake_ = time;
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